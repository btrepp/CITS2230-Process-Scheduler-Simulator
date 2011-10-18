#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG
#include "debug.h"
#include "jobList.h"

void printOrder(JobElement* start);

// Takes in the Joblist and sort its from its arrival time
JobElement* altSort(JobElement* start){
	JobElement* previous = NULL;
	JobElement* head =start;
	bool sorted=true;
	
	if(head->next==NULL){
		if(head->next->arrival_time < head->arrival_time){
			debug_print("swapping %s:%d with %s:%d\n",head->jobname,head->arrival_time,
						head->next->jobname, head->next->arrival_time);
			//swap head!
			JobElement* curtemp=head->next;
			head->next=curtemp->next;	
			curtemp->next=head;
			head=curtemp;
			sorted=false;
		}
		previous=head;	
	
		JobElement* current= previous->next;
		while(current!=NULL){
			if(current->next->arrival_time < current->arrival_time){
				debug_print("swapping %s:%d with %s:%d\n",current->jobname,current->arrival_time,
						current->next->jobname, current->next->arrival_time);
				//swap
				JobElement* temp=current;
				current->next = temp->next;
				temp->next = current;
				previous->next= current->next;
				sorted=false;
			}
			previous=current;
			current=current->next;		
		}
	}
	if(sorted==false)
		return altSort(head);
	return head;
}

JobElement* sort(JobElement* Job, int jobCounter){
	printOrder(Job);

	JobElement* temp1; // temp container
	JobElement* window; // a "window" iterator
	window = Job;
	debug_print_string("Starting the sorting \n");
	debug_print("Jobcounter = %d \n", jobCounter);
	debug_print("window = %s \n", window->jobname);
	int i = 0;
	int j;

	/*consider using 
 * 		currentjob->next!=NULL
 * 		we shouldn't need to pass in how long the linked list is
 * 		it's a linked list, that's unknown by definition :P
 * 		*/

	while( window->next!=NULL)
	{
	  //debug_print("i = %d \n", i);
		for(j = 0; j < jobCounter-1; j++)
		{
		  debug_print("i = %d || j = %d \n", i, j);
		  debug_print_string("begin sorting \n");
		  debug_print("current Job = %s \n", Job->jobname); // wth? current job is still the first job
		  if(Job != NULL )
		  {
		    debug_print(" Job arival time: %d  || Job next time: %d \n", Job->arrival_time, Job->next->arrival_time);
			if( Job->arrival_time > Job->next->arrival_time) 
			{
				temp1 = Job;
				temp1->next = Job->next->next;
				Job = Job->next;
				Job->next = temp1;
				window = temp1;
			}
			
			Job = Job->next;
			window = window->next;
			debug_print("current window = %s \n", window->jobname);
			
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
		i++;
	}
	debug_print_string("Finished sorting \n");
	return Job;
}

void printOrder(JobElement* start){
	JobElement* current =start;
	while(current!=NULL){
		debug_print("%s->",current->jobname);
		current=current->next;
	}
}


