#include "jobScheduler.h"
#include "jobList.h"
#include "sort.h"

#include "debug.h"
#define DEBUG

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

schedule_mode mode=0;

int k=0;

void firstComeFirstServe();
void roundrobin();
void shortprocessnext();
void shortremainingtime();

void setSchedulingMode(schedule_mode stuff){
  mode=stuff;
}

void setRoundRobinQuanta(int quanta){
	debug_print("Quant set to:%d\n",quanta);
	k=quanta;
}


void addJob(JobElement* job){
/*  if(current_clock!=job->arrival_time){
     fprintf(stderr,"Incorrect Arrival Time!");
      exit(EXIT_FAILURE);
  }
*/

  if(unscheduled_jobs_tail==NULL)
	unscheduled_jobs_head=job;
  else
	unscheduled_jobs_tail->next=job;
  unscheduled_jobs_tail=job;

  printOrder(unscheduled_jobs_head);
  debug_print("Job:%s[%d,%d] @ %d\n",job->jobname,job->arrival_time,job->length_time,current_clock);
}


void sort_time_length(JobElement* joblist) {
	//sort
}

int incrementClock(){
  if(active_job!=NULL && (active_job_scheduled_at+active_job->length_time < current_clock)){
     	debug_print("Active Job completed @ %d\n",current_clock);
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

JobSchedule* getResults(){
	return schedule_results_head;
}


void insertScheduleElement(JobSchedule* jobsch){
	if(schedule_results_tail==NULL)
 	       schedule_results_head=jobsch;
 	 else
        	schedule_results_tail->next=jobsch;
	 schedule_results_tail=jobsch;
}

JobElement* nextJobToSchedule(){
	if(unscheduled_jobs_head==NULL)
		return NULL;

	JobElement* returnelem = unscheduled_jobs_head;
	unscheduled_jobs_head = unscheduled_jobs_head->next;
	return returnelem;
}


void firstComeFirstServe(){
    if(active_job!=NULL)
      return;
 
    //sort(unscheduled_jobs); // it should be sorted already due to FCFS!.
    
    active_job=nextJobToSchedule();
    active_job_scheduled_at=current_clock;

    //if we have no jobs to schedule, idle
    if(active_job==NULL) return;

    //create result
    JobSchedule* scheduledjob = malloc(sizeof(*scheduledjob));
    scheduledjob->jobname = active_job->jobname;
    scheduledjob->start_time = current_clock;
    scheduledjob->running_time = active_job->length_time; 

    insertScheduleElement(scheduledjob);

}

void roundrobin(){
    if(k<1){
	perror("Quanta can't be less than 1");
	exit(EXIT_FAILURE);
    }
  
    if(active_job!=NULL)
      return;
    
    JobElement* temp=nextJobToSchedule();

    if(temp==NULL) return;

    JobElement* remainingquantjob=NULL;
    active_job=malloc(sizeof(*active_job));
    
    memcpy(active_job,temp,sizeof(*active_job));
    active_job->length_time=k;
    
    if(temp->length_time>k){
      remainingquantjob = malloc(sizeof(*remainingquantjob));
      memcpy(remainingquantjob,temp,sizeof(*remainingquantjob));
      remainingquantjob->length_time= temp->length_time-k;

      addJob(remainingquantjob); 
     
    }

    JobSchedule* jobsch = malloc(sizeof(*jobsch));
    jobsch->jobname= temp->jobname;
    jobsch->start_time = current_clock;
    jobsch->running_time = k; 

     
    insertScheduleElement(jobsch);
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
   
