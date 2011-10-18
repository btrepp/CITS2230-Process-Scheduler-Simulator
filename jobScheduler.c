#include "jobScheduler.h"
#include "jobList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int current_clock=0;

JobElement* unscheduled_jobs_head=NULL;
JobElement* unscheduled_jobs_tail=NULL;
JobSchedule* schedule_results_head=NULL;
JobSchedule* schedule_results_tail=NULL;

JobElement* active_job=NULL;

int active_job_scheduled_at;


#define FCFS 1
#define RR 2
#define SPN 3
#define SRT 4
typedef int schedule_mode;

schedule_mode mode=0;

int k=0;

void firstComeFirstServe();
void roundrobin();
void shortprocessnext();
void shortremainingtime();

void setSchedulingMode(schedule_mode stuff){
  mode=stuff;
}

void addJob(JobElement* job){
  if(current_clock!=job->arrival_time){
     fprintf(stderr,"Incorrect Arrival Time!");
      exit(EXIT_FAILURE);
  }

  if(unscheduled_jobs_tail==NULL)
	unscheduled_jobs_head=job;
  else
	unscheduled_jobs_tail->next=job;
  unscheduled_jobs_tail=job;

}

void sort_time_length(JobElement* joblist) {
	//sort
}

int incrementClock(){
  if(active_job_scheduled_at+active_job->length_time > current_clock){
      active_job=NULL;
  //    free(active_job);
  }
  
  switch(mode){
    case FCFS:
	firstComeFirstServe();
	break;
	
    case RR:
      roundrobin();
      break;
      
    case SPN:
      shortprocessnext();
      break;
      
    case SRT:
      shortremainingtime();
      break;
     } 
  return current_clock++;
}

bool no_more_jobs(){
  if(unscheduled_jobs_head==NULL && active_job!=NULL){
    return true;
  }
  return false;
}

void insertScheduleElement(JobSchedule* jobsch){
	if(schedule_results_tail==NULL)
 	       schedule_results_head=jobsch;
 	 else
        	schedule_results_tail->next=jobsch;
	 schedule_results_tail=jobsch;
}



void firstComeFirstServe(){
    if(active_job!=NULL)
      return;
 
    //sort(unscheduled_jobs); // it should be sorted already due to FCFS!.
      
    active_job=unscheduled_jobs_head;
    unscheduled_jobs_head = unscheduled_jobs_head->next; 
    active_job_scheduled_at=current_clock;

    //create result
    JobSchedule* scheduledjob = malloc(sizeof(*scheduledjob));
    scheduledjob->jobname = active_job->jobname;
    scheduledjob->start_time = current_clock;
    scheduledjob->running_time = active_job->length_time; 



}

void roundrobin(){
  /*  if(k<1){
	perror("Quanta can't be less than 1");
	exit(EXIT_FAILURE);
    }
  
    if(active_job!=NULL)
      return;
    
    JobElement* temp==dequeue(unscheduled_jobs);
    JobElement* remainingquantjob==NULL;
    active_job==malloc(sizeof(JobListElement));
    
    memcpy(temp,active_job,i cant remember args);
    active_job->length_time=k;
    
    if(temp->length_time>k){
      memcpy(temp,remainingquantjob,sizeof(JobListElement));
      remainingquantjob->length_time= temp->length_time-k;
      unscheduled_jobs->add(remainingquantjob);
    }
      
    schedule_results->next(active_job);
    */
}

void shortprocessnext(){
  /* if(active_job!=NULL)
      return;
   
   sort_time_length(JobList);
   firstComeFirstServe();
*/}

void shortremainingtime(){
  /* if(active_job!=NULL){
      perror("Active Job should always be NULL in SRT!");
      exit(EXIT_FAILURE);
   }
   
   sort_time_length(JobList);
   
    Job* temp==dequeue(unscheduled_jobs);
    Job* remainingquantjob==NULL;
    active_job==malloc(sizeof(JobListElement));
    memcpy(temp,active_job,sizeof(JobListElement));
    active_job->length_time=1;
    
    
    if(temp->length_time>1){
      memcpy(temp,remainingquantjob,sizeof(JobListElement));
      remainingquantjob->length_time= temp->length_time-1;
      unscheduled_jobs->add(remainingquantjob);
    }
   
   schedule_results->next(active_job);
 */
	return;
}
   
