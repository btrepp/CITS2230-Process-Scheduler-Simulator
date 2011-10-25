#include "virtualCPU.h"
#include "sort.h"
#include <stdlib.h>
#include <string.h>

#define DEBUG
#include "debug.h"

#define PAGES_PHYSICAL 50
#define PAGES_SIZE	4

JobSchedule* firstComeFirstServe(VirtualCPU* cpu);
JobSchedule* roundrobin(VirtualCPU* cpu);
JobSchedule* shortprocessnext(VirtualCPU* cpu);
JobSchedule* shortremainingtime(VirtualCPU* cpu);

void initCPU(VirtualCPU* cpu){
	memset(cpu,0,sizeof(*cpu));
	cpu->unscheduled_jobs = malloc(sizeof(*(cpu->unscheduled_jobs)));
	cpu->scheduled = malloc(sizeof(*(cpu->scheduled)));

	cpu->physical_memory = malloc(sizeof(*(cpu->physical_memory)));
	initMemory(cpu->physical_memory,PAGES_PHYSICAL,PAGES_SIZE);
}

int incrementClock(VirtualCPU* cpu){
   if(cpu->active_job!=NULL)
        debug_print("Clock at:%d, Job Finishes at: %d\n",
		cpu->current_clock,cpu->active_job_scheduled_at+cpu->active_job->length_time);
   else
        debug_print("Clock at:%d, System Idling\n",cpu->current_clock);

   if(cpu->active_job!=NULL && (cpu->active_job_scheduled_at+cpu->active_job->length_time-1 < cpu->current_clock)){
   	debug_print("Active Job completed @ %d\n",cpu->current_clock);

	//if this was the last schedule for this job
	if(cpu->memory_management && cpu->active_job!=NULL &&
				 cpu->active_job->completed==true){
		debug_print("Job %s, memory reclaimed!\n",cpu->active_job->jobname);
		//free(active_job)
	}
	cpu->active_job=NULL;
   }

   if(cpu->active_job!=NULL) return cpu->current_clock++;
 
   JobSchedule* job=NULL; 
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
     insertScheduleElement(cpu->scheduled,job);
		
    // memory stuff
   if(cpu->memory_management){
	
   }


 
   return cpu->current_clock++;
}


JobSchedule* firstComeFirstServe(VirtualCPU* cpu){
    if(cpu->active_job!=NULL)
      return NULL;

    //sort(cpu->unscheduled_jobs->head); // it should be sorted already due to FCFS!.
    
    cpu->active_job=nextJobToSchedule(cpu->unscheduled_jobs);
    cpu->active_job_scheduled_at=cpu->current_clock;
    markJobAsComplete(cpu->active_job,true); 
    
    //if we have no jobs to schedule, idle
    if(cpu->active_job==NULL) return NULL;
    //create result
    JobSchedule* scheduledjob = malloc(sizeof(*scheduledjob));
    scheduledjob->jobname = cpu->active_job->jobname;
    scheduledjob->start_time = cpu->current_clock;
    scheduledjob->running_time = cpu->active_job->length_time;
    
    return scheduledjob;

    //insertScheduleElement(cpu->scheduled,scheduledjob);
}

JobSchedule* roundrobin(VirtualCPU* cpu){

    if(cpu->roundRobinQuanta<1){
        perror("Quanta can't be less than 1");
        exit(EXIT_FAILURE);
    }

    if(cpu->active_job!=NULL)
      return NULL;

    if(cpu->remaining_active_job!=NULL){
        addJob(cpu->unscheduled_jobs, cpu->remaining_active_job);
        cpu->remaining_active_job=NULL;
    }

    JobElement* temp=nextJobToSchedule(cpu->unscheduled_jobs);

    if(temp==NULL) return NULL;

    JobElement* remainingquantjob=NULL;
    cpu->active_job=malloc(sizeof(*(cpu->active_job)));
    cpu->active_job_scheduled_at=cpu->current_clock;

    memcpy(cpu->active_job,temp,sizeof(*(cpu->active_job)));
   
    if(temp->length_time>cpu->roundRobinQuanta){
	remainingquantjob = malloc(sizeof(*remainingquantjob));
        memcpy(remainingquantjob,temp,sizeof(*remainingquantjob));
        remainingquantjob->length_time= temp->length_time-cpu->roundRobinQuanta;
        cpu->active_job->length_time=cpu->roundRobinQuanta;
        cpu->remaining_active_job=remainingquantjob;
    }
    else{
	markJobAsComplete(cpu->active_job,true);  
    }
    
    JobSchedule* jobsch = malloc(sizeof(*jobsch));
    jobsch->jobname= temp->jobname;
    jobsch->start_time = cpu->current_clock;
    jobsch->running_time = cpu->active_job->length_time; 
                  
    return jobsch; 
    //insertScheduleElement(cpu->scheduled,jobsch);
}

JobSchedule* shortprocessnext(VirtualCPU* cpu){
   sortOnRemainingTime(cpu->unscheduled_jobs);
   return firstComeFirstServe(cpu);
}

JobSchedule* shortremainingtime(VirtualCPU* cpu){
    sortOnRemainingTime(cpu->unscheduled_jobs);
    setRoundRobinCPUQuanta(cpu,1);
    JobSchedule* jobsch = roundrobin(cpu);

    //put the job back on the queued list, so it can be scheduled straight away if it needs to
    if(cpu->remaining_active_job!=NULL){
        addJob(cpu->unscheduled_jobs, cpu->remaining_active_job);
        cpu->remaining_active_job=NULL;
    }

    //if the previous recorded job is this job just increment that value
    if(jobsch!=NULL && cpu->scheduled->tail!=NULL && 
	strcmp(jobsch->jobname,cpu->scheduled->tail->jobname)==0){ 
	cpu->scheduled->tail->running_time+= jobsch->running_time;
	return NULL;
    }	
   return jobsch;
}

void addJobToCPU(VirtualCPU* cpu, JobElement* job){
	markJobAsComplete(job,false);  
	addJob(cpu->unscheduled_jobs,job);
}

bool isCPUIdle(VirtualCPU* cpu){
     if(empty(cpu->unscheduled_jobs) && cpu->active_job!=NULL)
	return true;
     return false;
}

void setRoundRobinCPUQuanta(VirtualCPU* cpu, int quanta){
	cpu->roundRobinQuanta=quanta;
}

void setSchedulingMode(VirtualCPU* cpu,schedule_mode stuff){
  cpu->mode=stuff;
}

JobScheduleContainer* getResults(VirtualCPU* cpu){
	return cpu->scheduled;
}

void setMemoryManagement(VirtualCPU* cpu, bool value){
	cpu->memory_management=value;
}

