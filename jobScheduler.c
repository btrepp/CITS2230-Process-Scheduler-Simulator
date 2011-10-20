#include "jobScheduler.h"
#include "jobList.h"
#include "sort.h"

#define DEBUG
#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//int current_clock=0;

//JobElement* unscheduled_jobs_head=NULL;
//JobElement* unscheduled_jobs_tail=NULL;
//JobSchedule* schedule_results_head=NULL;
//JobSchedule* schedule_results_tail=NULL;

//JobElement* active_job=NULL;



/*int incrementClock(C){
   if(active_job!=NULL)
        debug_print("Clock at:%d, Job Finishes at: %d\n",
		current_clock,active_job_scheduled_at+active_job->length_time);
   else
        debug_print("Clock at:%d, System Idling\n",current_clock);


   //check if active job should still be running
   if(active_job!=NULL && (active_job_scheduled_at+active_job->length_time-1 < current_clock)){
     	debug_print("Active Job completed @ %d\n",current_clock);
	 active_job=NULL;
  //    free(active_job);
  }

  if(active_job!=NULL) return current_clock++;
  
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
*/

void insertScheduleElement(JobScheduleContainer* list, JobSchedule* jobsch){
	if(list->tail==NULL)
 	       list->head=jobsch;
 	 else
        	list->tail->next=jobsch;
	 list->tail=jobsch;
}
/*
bool no_more_jobs(virtualcpu* cpu){
  if(cpu-> && active_job!=NULL){
    return true;
  }
  return false;
}
*/
/*
JobElement* nextJobToSchedule(){
	printOrder(unscheduled_jobs_head);
	if(unscheduled_jobs_head==NULL)
		return NULL;

	JobElement* returnelem = unscheduled_jobs_head;
	unscheduled_jobs_head = unscheduled_jobs_head->next;

	if(unscheduled_jobs_head==NULL)
		unscheduled_jobs_tail=NULL;

	return returnelem;
}
*/
/*
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
*/
/*JobElement* roundrobinqueue=NULL;

void roundrobin(){

    if(k<1){
	perror("Quanta can't be less than 1");
	exit(EXIT_FAILURE);
    }
  
    if(active_job!=NULL)
      return;
    
    if(roundrobinqueue!=NULL){
	addJob(roundrobinqueue);
	roundrobinqueue=NULL;
    }
    
    JobElement* temp=nextJobToSchedule();

    if(temp==NULL) return;

    JobElement* remainingquantjob=NULL;
    active_job=malloc(sizeof(*active_job));
    active_job_scheduled_at=current_clock;
    
    memcpy(active_job,temp,sizeof(*active_job));
    //active_job->length_time=k;
    
    if(temp->length_time>k){
      remainingquantjob = malloc(sizeof(*remainingquantjob));
      memcpy(remainingquantjob,temp,sizeof(*remainingquantjob));
      remainingquantjob->length_time= temp->length_time-k;
      active_job->length_time=k;
      roundrobinqueue=remainingquantjob;
      //addJob(remainingquantjob); 
    }


    JobSchedule* jobsch = malloc(sizeof(*jobsch));
    jobsch->jobname= temp->jobname;
    jobsch->start_time = current_clock;
    jobsch->running_time = active_job->length_time; 

     
    insertScheduleElement(jobsch);
}
*/
void sortCPUListRemainingTime(JobListContainer* list){
   if(list->head!=NULL){
	//sort on shortest remaining time

   	list->head = sortshortest(list->head);
	   //set last correctly
  	 JobElement* temp=list->head;
  	 while(temp->next!=NULL){
		temp=temp->next;
	 }
   	 list->tail=temp;
   }
}

/*
void shortprocessnext(){
   firstComeFirstServe();
}

void shortremainingtime(){

    sortCPUListRemainingTime(); 
    k=1;
    roundrobin();  
    if(roundrobinqueue!=NULL){
        addJob(roundrobinqueue);
        roundrobinqueue=NULL;
    }
 
    return;
}*/
   
