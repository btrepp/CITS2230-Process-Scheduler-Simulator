#include "virtualCPU.h"
#include "sort.h"
#include <stdlib.h>
#include <string.h>

#define DEBUG
#include "debug.h"



void firstComeFirstServe(VirtualCPU* cpu);
void roundrobin(VirtualCPU* cpu);
void shortprocessnext(VirtualCPU* cpu);
void shortremainingtime(VirtualCPU* cpu);

void initCPU(VirtualCPU* cpu){
	memset(cpu,0,sizeof(*cpu));
	cpu->unscheduled_jobs = malloc(sizeof(*(cpu->unscheduled_jobs)));
	cpu->scheduled = malloc(sizeof(*(cpu->scheduled)));

}




int incrementClock(VirtualCPU* cpu){
   if(cpu->active_job!=NULL)
        debug_print("Clock at:%d, Job Finishes at: %d\n",
		cpu->current_clock,cpu->active_job_scheduled_at+cpu->active_job->length_time);
   else
        debug_print("Clock at:%d, System Idling\n",cpu->current_clock);

   if(cpu->active_job!=NULL && (cpu->active_job_scheduled_at+cpu->active_job->length_time-1 < cpu->current_clock)){
   	debug_print("Active Job completed @ %d\n",cpu->current_clock);
	cpu->active_job=NULL;
   }

   if(cpu->active_job!=NULL) return cpu->current_clock++;
  
   switch(cpu->mode){
    case FCFS:
	firstComeFirstServe(cpu);
	break;
	
    case RR:
      roundrobin(cpu);
      break;
      
    case SPN:
      shortprocessnext(cpu);
      break;
      
    case SRT:
      shortremainingtime(cpu);
      break;
     } 
   return cpu->current_clock++;
}

void firstComeFirstServe(VirtualCPU* cpu){
    if(cpu->active_job!=NULL)
      return;

    //sort(cpu->unscheduled_jobs->head); // it should be sorted already due to FCFS!.
    
    cpu->active_job=nextJobToSchedule(cpu->unscheduled_jobs);
    cpu->active_job_scheduled_at=cpu->current_clock;
    
    //if we have no jobs to schedule, idle
    if(cpu->active_job==NULL) return;
    //create result
    JobSchedule* scheduledjob = malloc(sizeof(*scheduledjob));
    scheduledjob->jobname = cpu->active_job->jobname;
    scheduledjob->start_time = cpu->current_clock;
    scheduledjob->running_time = cpu->active_job->length_time;
    insertScheduleElement(cpu->scheduled,scheduledjob);
}

void roundrobin(VirtualCPU* cpu){

    if(cpu->roundRobinQuanta<1){
        perror("Quanta can't be less than 1");
        exit(EXIT_FAILURE);
    }

    if(cpu->active_job!=NULL)
      return;

    if(cpu->remaining_active_job!=NULL){
        addJob(cpu->unscheduled_jobs, cpu->remaining_active_job);
        cpu->remaining_active_job=NULL;
    }

    JobElement* temp=nextJobToSchedule(cpu->unscheduled_jobs);

    if(temp==NULL) return;

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
    
    JobSchedule* jobsch = malloc(sizeof(*jobsch));
    jobsch->jobname= temp->jobname;
    jobsch->start_time = cpu->current_clock;
    jobsch->running_time = cpu->active_job->length_time; 
                   
    insertScheduleElement(cpu->scheduled,jobsch);
}

void shortprocessnext(VirtualCPU* cpu){
   sortOnRemainingTime(cpu->unscheduled_jobs);
   firstComeFirstServe(cpu);
}

void shortremainingtime(VirtualCPU* cpu){
    sortOnRemainingTime(cpu->unscheduled_jobs);
    setRoundRobinCPUQuanta(cpu,1);
    roundrobin(cpu);

    if(cpu->remaining_active_job!=NULL){
        addJob(cpu->unscheduled_jobs, cpu->remaining_active_job);
        cpu->remaining_active_job=NULL;
    }

   return;
}

void addJobToCPU(VirtualCPU* cpu, JobElement* job){
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

