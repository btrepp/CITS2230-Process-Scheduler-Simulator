#include "virtualCPU.h"
#include "sort.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define DEBUG
#include "debug.h"

#define PAGES_PHYSICAL 50
#define PAGES_SIZE	4

LIST(UnprocessedJob);

JobScheduleResult* firstComeFirstServe(VirtualCPU* cpu);
JobScheduleResult* roundrobin(VirtualCPU* cpu);
JobScheduleResult* shortprocessnext(VirtualCPU* cpu);
JobScheduleResult* shortremainingtime(VirtualCPU* cpu);

void initCPU(VirtualCPU* cpu){
	memset(cpu,0,sizeof(*cpu));
	cpu->unscheduled_jobs = malloc(sizeof(*(cpu->unscheduled_jobs)));
	cpu->scheduled = malloc(sizeof(*(cpu->scheduled)));

	cpu->physical_memory = malloc(sizeof(*(cpu->physical_memory)));
}

int incrementClock(VirtualCPU* cpu){
   
   if(cpu->active_job!=NULL)
        debug_print("Clock at:%d, Job  %s Finishes at: %d\n",
		cpu->current_clock,
		cpu->active_job->job->jobname,
		cpu->active_job->start_time+cpu->active_job->running_time);
   else
        debug_print("Clock at:%d, System Idling\n",cpu->current_clock);

   if(cpu->active_job!=NULL && 
	(cpu->active_job->start_time+cpu->active_job->running_time-1 < cpu->current_clock)){
   	debug_print("Scheduled %s completed @ %d\n",cpu->active_job->job->jobname, 
						    cpu->current_clock);

	if(cpu->remaining_active_job->time_remaining==0){
		debug_print("Job %s completed\n",cpu->active_job->job->jobname);
		
		if(cpu->memory_management){
			//mark this job as complete in the memory
			freeJob(cpu->physical_memory, cpu->active_job->job);
			debug_print("Job %s, memory reclaimed!\n",cpu->active_job->job->jobname);
		}
	}
	cpu->active_job=NULL;

   }

   //print out memory status
   //
//   fprintf(stdout,"Jobs held in physical memory at %d\n",cpu->current_clock);
   //printMemory(cpu->physical_memory);

   if(cpu->active_job!=NULL) return ++cpu->current_clock;
 
   JobScheduleResult* job=NULL; 
   switch(cpu->mode){
    case FCFS:
	job=firstComeFirstServe(cpu);
	break;
	
    case RR:
        job=roundrobin(cpu);
        break;
      
    case SPN:
        job=shortprocessnext(cpu);
        break;
      
    case SRT:
        job=shortremainingtime(cpu);
        break;
    }


   if(job!=NULL)
       list_JobScheduleResult_append(cpu->scheduled, job);
	//insertScheduleElement(cpu->scheduled,job);
		
    // memory stuff
   if(cpu->active_job!=NULL && cpu->memory_management){
	debug_print("Loading: %s, into memory\n",cpu->active_job->job->jobname);
	JobInMemory* allocpages=loadJob(cpu->physical_memory,cpu->active_job->job,cpu->current_clock);	
	//fill pages with data
	int jobnamelength = strlen(cpu->active_job->job->jobname);
	for(int i=0;i<allocpages->pages_for_job;i++){
		Page* thispage = allocpages->pages[i];
		for(int i=0;i<cpu->physical_memory->pagesize;i++){
			int indexinname = jobnamelength-1-((i+1)%2);
			char bytetostore = cpu->active_job->job->jobname[indexinname];
			if(!isdigit(bytetostore)) bytetostore= '0';
			*(thispage->location_in_memory+i)= bytetostore;
		}
	}	 
   }

   return ++cpu->current_clock;
}


JobScheduleResult* firstComeFirstServe(VirtualCPU* cpu){
    if(cpu->active_job!=NULL)
      return NULL;

    //sort(cpu->unscheduled_jobs->head); // it should be sorted already due to FCFS!.
   
    UnprocessedJob* toSchedule = list_UnprocessedJob_pop(cpu->unscheduled_jobs);
    if(toSchedule==NULL) return NULL;

    JobScheduleResult* scheduledjob = malloc(sizeof(*scheduledjob));
    scheduledjob->job=toSchedule->job;
    scheduledjob->start_time = cpu->current_clock;
    scheduledjob->running_time = toSchedule->job->length_time;
    //markJobAsComplete(cpu->active_job->job,true); 
    
    //if we have no jobs to schedule, idle
    //create result
	
    toSchedule->time_remaining =0;  
    cpu->remaining_active_job = toSchedule;  
    cpu->active_job = scheduledjob;
    return scheduledjob;

    //insertScheduleElement(cpu->scheduled,scheduledjob);
}

JobScheduleResult* roundrobin(VirtualCPU* cpu){

    if(cpu->roundRobinQuanta<1){
        perror("Quanta can't be less than 1");
        exit(EXIT_FAILURE);
    }

    if(cpu->active_job!=NULL)
      return NULL;

    if(cpu->remaining_active_job!=NULL && cpu->remaining_active_job->time_remaining >0){
        list_UnprocessedJob_append(cpu->unscheduled_jobs, cpu->remaining_active_job);
        cpu->remaining_active_job=NULL;
    }

    UnprocessedJob* temp=list_UnprocessedJob_pop(cpu->unscheduled_jobs);

    if(temp==NULL) return NULL;
    
    JobScheduleResult* jobsch = malloc(sizeof(*jobsch));
    jobsch->job = temp->job;
    jobsch->start_time = cpu->current_clock;
    jobsch->running_time = (cpu->roundRobinQuanta>temp->time_remaining ? 
				temp->time_remaining : cpu->roundRobinQuanta);

    temp->time_remaining-=cpu->roundRobinQuanta; 
    if(temp->time_remaining < 1) temp->time_remaining = 0; 
    
	
    cpu->remaining_active_job = temp;

    cpu->active_job = jobsch;
    return jobsch; 
}

JobScheduleResult* shortprocessnext(VirtualCPU* cpu){
   //sortOnRemainingTime(cpu->unscheduled_jobs);
   return firstComeFirstServe(cpu);
}

JobScheduleResult* shortremainingtime(VirtualCPU* cpu){
    //sortOnRemainingTime(cpu->unscheduled_jobs);
    setRoundRobinCPUQuanta(cpu,1);
    JobScheduleResult* jobsch = roundrobin(cpu);

    //put the job back on the queued list, so it can be scheduled straight away if it needs to
    if(cpu->remaining_active_job!=NULL){
        list_UnprocessedJob_append(cpu->unscheduled_jobs, cpu->remaining_active_job);
        cpu->remaining_active_job=NULL;
    }

    //if the previous recorded job is this job just increment that value
    if(jobsch!=NULL && cpu->scheduled->tail!=NULL && 
	jobsch->job == cpu->scheduled->tail->data->job){
	cpu->scheduled->tail->data->running_time+= jobsch->running_time;
	free(jobsch);
	return NULL;
    }	
   return jobsch;
}

void addJobToCPU(VirtualCPU* cpu, Job* job){
	UnprocessedJob * newjob = malloc(sizeof(*newjob));
	newjob->job = job;
	newjob->time_remaining = job->length_time;

	list_UnprocessedJob_append(cpu->unscheduled_jobs,newjob);
}

bool isCPUIdle(VirtualCPU* cpu){
     if(list_UnprocessedJob_empty(cpu->unscheduled_jobs) && cpu->active_job==NULL)
	return true;
     return false;
}

void setRoundRobinCPUQuanta(VirtualCPU* cpu, int quanta){
	cpu->roundRobinQuanta=quanta;
}

void setSchedulingMode(VirtualCPU* cpu,schedule_mode stuff){
  cpu->mode=stuff;
}

list_JobScheduleResult* getResults(VirtualCPU* cpu){
	return cpu->scheduled;
}

void setMemoryManagement(VirtualCPU* cpu, bool value){
	cpu->memory_management=value;
	if(value==true)
		initMemory(cpu->physical_memory,PAGES_PHYSICAL,PAGES_SIZE);
}
