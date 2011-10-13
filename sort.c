#include <stdio.h>
#include <stdlib.h>

#define DEBUG
#include "debug.h"
#include "jobList.h"

// Takes in the Joblist and sort its from its arrival time
JobElement* sort(JobElement* Job, int jobCounter)
{
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

	while( i < jobCounter)
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
		  exit(EXIT_FAILURE);

		}
		i++;
	}
	debug_print_string("Finished sorting \n");
	return Job;
}
