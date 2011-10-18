#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG
#include "debug.h"
#include "jobList.h"

void printOrder(JobElement* start);

// Takes in the Joblist and sort its from its arrival time
JobElement* sort(JobElement* Job, int jobCounter)
{
	JobElement* firstJob; // container for the first job in the linked list
	printOrder(Job);
	JobElement* temp1; // temp container
	JobElement* previous; // container to store the job behind the current job we are looking at
	//JobElement* window; // a "window" iterator
	//window = Job;
	JobElement* startList; // marker to mark the start of the list, note should always be in at the start of the list!
			      // So that we can return to the list and sort it from the start again
	debug_print("Job1 = %s \n", Job->jobname);
	debug_print("Job2 = %s \n", Job->next->jobname);
	debug_print("Job3 = %s \n", Job->next->next->jobname);
	debug_print("Job4 = %s \n", Job->next->next->next->jobname);
	if( Job->next->next->next->next ==  NULL) debug_print_string("Job5 is null\n");
	firstJob = Job;
	previous = Job;
	startList = Job;
	debug_print_string("Starting the sorting \n");
	debug_print("Jobcounter = %d \n", jobCounter);
	//debug_print("window = %s \n", window->jobname);
	int i = 0;
	int j;

	/*consider using 
 * 		currentjob->next!=NULL
 * 		we shouldn't need to pass in how long the linked list is
 * 		it's a linked list, that's unknown by definition :P
 * 		*/
	/*
	 *  Lol i was only using it because the counter was there 
	 *  But yes ur right about not needing to know how long it is
	 *  Slight problem once we've gone through the list once its going to stop 
	 *  sorting... because of currendjob->next != null
	 * 
	 * 	Note: window container might be useless
	 */

	// Implement the first job contaner to keep track of the first job
	while( i < jobCounter) // Will still need to check for several times if the list has been sorted
	//while(Job->next != NULL)
	{
	  //debug_print("i = %d \n", i);
	  Job = startList; // Soo that the search can start in the front again
	  previous = startList;
		for(j = 0; j < jobCounter-1; j++)
		{
		  debug_print("i = %d || j = %d \n", i, j);
		  debug_print_string("begin sorting \n");
		  if(Job->next != NULL )
		  {
		    debug_print("current Job = %s \n", Job->jobname); 
		    debug_print("Next Job = %s \n", Job->next->jobname); 
		    debug_print("Previous = %s \n", previous->jobname); 
		    debug_print(" Job arival time: %d  || Job next time: %d \n", Job->arrival_time, Job->next->arrival_time);
			if( Job->arrival_time > Job->next->arrival_time) // current job is older than the next job, must swap
			{ 
			  // This partially working rite until the  2nd loop finishes
				temp1 = Job;
// 				debug_print("Temp1 = %s \n", temp1->jobname);
// 				debug_print("Job->next->jobname = %s \n", Job->next->jobname); 
// 				debug_print("temp1->next->jobname = %s \n", temp1->next->jobname);
				Job = Job->next;
// 				debug_print("Job->jobname = %s \n", Job->jobname); 
// 				debug_print("Job->next->jobname = %s \n", Job->next->jobname); 
				temp1->next = Job->next;
// 				debug_print("temp1->jobname = %s \n", temp1->jobname);
// 				debug_print("temp1->next->jobname = %s \n", temp1->next->jobname);
				Job->next = temp1;
// 				debug_print("Job->next->jobname = %s \n", Job->next->jobname); 
				previous->next = Job;
// 				debug_print("previous->jobname = %s \n", previous->jobname); 
// 				debug_print("previous->next->jobname = %s \n", previous->next->jobname);
				Job = Job->next;
				Job->next = temp1->next;
// 				debug_print("Job->jobname = %s \n", Job->jobname); 
// 				debug_print("Job->next->jobname = %s \n", Job->next->jobname); 
				previous = previous->next;
				debug_print("current Job = %s \n", Job->jobname); 
				debug_print("Next Job = %s \n", Job->next->jobname); 
				debug_print("Previous = %s \n", previous->jobname); 
				
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
				debug_print("Previous Job = %s \n", previous->jobname); 
				Job = Job->next;
				debug_print("Job->jobname = %s \n", Job->jobname); 
			}
			//window = window->next;
			//debug_print("current window = %s \n", window->jobname);
			debug_print_string("End of Job->next != NULL \n");
		  }
		  
		}
		if(Job-> jobname == Job-> next->jobname) 
		{
		  debug_print("Jobname = %s \n Next Jobname = %s \n i = %d || j = %d \n", Job-> jobname, Job-> next->jobname, i , j);
		  // perror prints out the last error code from a syscall, it will be undefined here!
		  //perror(NULL); 
		  printOrder(Job);
		  exit(EXIT_FAILURE);

		}
// 		if(Job-> jobname == Job-> next->jobname) // the condition when theres no other next job. 
// 		{
// 		  debug_print("Jobname = %s \n Next Jobname = %s \n i = %d || j = %d \n", Job-> jobname, Job-> next->jobname, i , j);
// 		  // perror prints out the last error code from a syscall, it will be undefined here!
// 		  //perror(NULL);
// 		  break;
// 		  //exit(EXIT_FAILURE);
// 
// 		}
		i++;
	}
	debug_print_string("Finished sorting \n");
	debug_print("First Job is... %s \n", firstJob->jobname);
	//exit(EXIT_FAILURE);
	return firstJob;
}

void printOrder(JobElement* start){
	JobElement* current =start;
	while(current!=NULL){
		debug_print("%s->",current->jobname);
		current=current->next;
	}
}


