#include "JobList.h"
#include <stdio.h>
#include <stdlib.h>

// Takes in the Joblist and sort its from its arrival time
void Sort(JobElement* Job, int jobCounter)
{
	JobElement* temp1; // temp container
	JobElement* window; // a "window" iterator
	window = Job;
	printf("Starting the sorting \n");
	printf("Jobcounter = %d \n", jobCounter);
	printf("window = %s \n", window->jobname);
	int i = 0;
	int j;
	while( i < jobCounter)
	{
	  //printf("i = %d \n", i);
		for(j = 0; j < jobCounter-1; j++)
		{
		  printf("i = %d || j = %d \n", i, j);
		  printf("begin sorting \n");
		  printf("current Job = %s \n", Job->jobname); // wth? current job is still the first job
		  if(Job != NULL )
		  {
		    printf(" Job arival time: %d  || Job next time: %d \n", Job->arrival_time, Job->next->arrival_time);
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
			printf("current window = %s \n", window->jobname);
			
		  }
		  
		}
		if(Job-> jobname == Job-> next->jobname) 
		{
		  printf("Jobname = %s \n Next Jobname = %s \n i = %d || j = %d \n", Job-> jobname, Job-> next->jobname, i , j);
		  perror(NULL); exit(EXIT_FAILURE);
		}
		i++;
	}
	printf("Finished sorting \n");
}