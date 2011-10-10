#include "JobList.h"

// Takes in the Joblist and sort its from its arrival time
void Sort(JobList* Job, int jobCounter)
{
	JobList* temp1; // temp container
	JobList* window; // a "window" iterator
	window = Job;
	for (int i = 0;  i < jobCounter; i++) 
	{
		for(int j = 0; j < jobCounter - 1; j++)
		{
			if( Job->arrival_time > Job->next->arrival_time) 
			{
				temp1 = Job;
				temp1->next = Job->next->next;
				Job = Job->next;
				Job->next = temp1;
				window = temp1;
			}
			window = window->next;
		}
	}
}