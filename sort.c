#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define DEBUG
#include "debug.h"
#include "jobList.h"

void printOrder(JobElement* start);

int listLength(JobElement* Job){
	int count=0;
	while(Job!=NULL){
		Job=Job->next;
		count++;
	}
	return count;
}



// Takes in the Joblist and sort its from its arrival time
JobElement* sort(JobElement* Job)
{
	int jobCounter=listLength(Job);

	JobElement* firstJob; // container for the first job in the linked list
	printOrder(Job);
	JobElement* temp1; // temp container
	JobElement* previous; // container to store the job behind the current job we are looking at
	//JobElement* window; // a "window" iterator
	//window = Job;
	JobElement* startList; // marker to mark the start of the list, note should always be in at the start of the list!
			      // So that we can return to the list and sort it from the start again
	if( Job->next->next->next->next ==  NULL) debug_print_string("Job5 is null\n");
	firstJob = Job;
	previous = Job;
	startList = Job;
	debug_print_string("Starting the sorting \n");
	debug_print("Jobcounter = %d \n", jobCounter);
	//debug_print("window = %s \n", window->jobname);
	int i = 0;
	int j;
	
      JobElement* before = malloc(sizeof(JobElement));
      //memset(before,0,sizeof(JobElement));
      before->jobname= startList->jobname;
      before->arrival_time= startList->arrival_time;
      before->length_time= startList->length_time;
      before->next = startList;

	// Implement the first job contaner to keep track of the first job
	while( i < jobCounter) // Will still need to check for several times if the list has been sorted
	//while(Job->next != NULL)
	{
	  //debug_print("i = %d \n", i);
	  Job = startList; // Soo that the search can start in the front again
	  previous = before; // This gives the problem..ideally it should be some pointer to
				// the startList ie previous->next = startList;
		for(j = 0; j < jobCounter-1; j++)
		{
		  if(Job->next != NULL )
		  {
			if( Job->arrival_time > Job->next->arrival_time) // current job is older than the next job, must swap
			{ 
			  // This partially working rite until the  2nd loop finishes
				temp1 = Job;
				Job = Job->next;
				temp1->next = Job->next;
				Job->next = temp1;
				previous->next = Job;
				Job = Job->next;
				Job->next = temp1->next;
				previous = previous->next;
				// neeed to compare the currentjob with first job to see which is the newest jobCounter
				if(Job->arrival_time < firstJob->arrival_time)
				{
				  firstJob = Job; // Now first Job is set
				  if(startList->next == firstJob) // when start list is next to first job
				  {
				    startList->next = firstJob->next;
				    firstJob->next = startList;
				    startList = firstJob;
				  }
				}
				if(previous->next == startList) startList = previous;
				if(previous->arrival_time < firstJob->arrival_time) firstJob = previous;
				
				//window = temp1;
			} else {
				// neeed to compare the currentjob with first job to see which is the newest jobCounter
				if(Job->arrival_time < firstJob->arrival_time)
				{
				  firstJob = Job; // Now first Job is set
				  if(startList->next == firstJob) // when start list is next to first job
				  {
				    startList->next = firstJob->next;
				    firstJob->next = startList;
				    startList = firstJob;
				  }
				}
				if(Job != previous) previous = previous->next; // for the at the start case where job and previous are the same
				Job = Job->next;
			}
			//window = window->next;
			//debug_print("current window = %s \n", window->jobname);
			//if(Job->next == NULL) debug_print_string("Job next is null \n"); 
		  }
		  debug_print_string("Finished iteration \n");
		}
		printOrder(firstJob);
		i++;
	}
	debug_print_string("Finished sorting \n");
	debug_print("First Job is... %s \n", firstJob->jobname);
	//debug_print("Job5 = %s \n", firstJob->next->next->next->next->jobname);
	//exit(EXIT_FAILURE);
	
	return firstJob;
}

// Sort for sorting length_time
// Takes in the Joblist and sort its from its length_time
JobElement* sortshortest(JobElement* Job)
{
    int jobCounter=listLength(Job);
	JobElement* firstJob; // container for the first job in the linked list
	//printOrder(Job);
	JobElement* temp1; // temp container
	JobElement* previous; // container to store the job behind the current job we are looking at
	//JobElement* window; // a "window" iterator
	//window = Job;
	JobElement* startList; // marker to mark the start of the list, note should always be in at the start of the list!
			      // So that we can return to the list and sort it from the start again
	//if( Job->next->next->next->next ==  NULL) debug_print_string("Job5 is null\n");
	firstJob = Job;
	previous = Job;
	startList = Job;
	debug_print_string("Starting the sorting \n");
	debug_print("Jobcounter = %d \n", jobCounter);
	//debug_print("window = %s \n", window->jobname);
	int i = 0;
	int j;
	
      JobElement* before = malloc(sizeof(JobElement));
      //memset(before,0,sizeof(JobElement));
      before->jobname= startList->jobname;
      before->length_time= startList->length_time;
      before->length_time= startList->length_time;
      before->next = startList;
      
	// Implement the first job contaner to keep track of the first job
	while( i < jobCounter) // Will still need to check for several times if the list has been sorted
	//while(Job->next != NULL)
	{
	  //debug_print("i = %d \n", i);
	  Job = startList; // Soo that the search can start in the front again
	  previous = before; 
		for(j = 0; j < jobCounter-1; j++)
		{
		  if(Job->next != NULL )
		  {
			if( Job->length_time > Job->next->length_time) // current job is older than the next job, must swap
			{ 
				temp1 = Job;
				Job = Job->next;
				temp1->next = Job->next;
				Job->next = temp1;
				previous->next = Job;
				Job = Job->next;
				Job->next = temp1->next;
				previous = previous->next;
				// neeed to compare the currentjob with first job to see which is the newest job
				if(Job->length_time < firstJob->length_time)
				{
				  firstJob = Job; // Now first Job is set
				  if(startList->next == firstJob) // when start list is next to first job
				  {
				    startList->next = firstJob->next;
				    firstJob->next = startList;
				    startList = firstJob;
				  }
				}
				if(previous->next == startList) startList = previous;
				if(previous->length_time < firstJob->length_time) firstJob = previous;
				
				//window = temp1;
			} else {
				// neeed to compare the currentjob with first job to see which is the newest jobCounter
				if(Job->length_time < firstJob->length_time)
				{
				  firstJob = Job; // Now first Job is set
				  if(startList->next == firstJob) // when start list is next to first job
				  {
				    startList->next = firstJob->next;
				    firstJob->next = startList;
				    startList = firstJob;
				  }
				}
				if(Job != previous) previous = previous->next; // for the at the start case where job and previous are the same
				Job = Job->next;
			}
			
			//debug_print("current window = %s \n", window->jobname);
			//if(Job->next == NULL) debug_print_string("Job next is null \n"); 
		  }
		  debug_print_string("Finished iteration \n");
		}
		printOrder(firstJob);
		i++;
	}
	debug_print_string("Finished sorting \n");
	debug_print("First Job is... %s \n", firstJob->jobname);
	//debug_print("Job5 = %s \n", firstJob->next->next->next->next->jobname);
	//exit(EXIT_FAILURE);
	
	return firstJob;
}

void printOrder(JobElement* start){
	JobElement* current =start;
	char string[200];
	memset(string,0,200);
	while(current!=NULL){
		strcat(string,current->jobname);
		strcat(string,"->");
		//debug_print("%s->",current->jobname);
		current=current->next;
	}
	debug_print("%s\n",string);
}


