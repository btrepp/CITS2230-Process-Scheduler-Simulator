#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//#define DEBUG
#include "debug.h"
#include "job.h"
#include "list.h"

// comparing based on arrival time
int compare_Job(const void * job1, const void* job2){
	return ((Job*)job1)->arrival_time-((Job*)job2)->arrival_time;
}

// Sorting algorithm used 
void qsort_Job(list_Job* container){
	//pop everything off into array
	int length = list_Job_length(container);

	Job** data = malloc(sizeof(*data)*length);	
	
	Job* current = NULL;
	int i=0;
	while((current=list_Job_pop(container))!=NULL){
		data[i++] = current;	
	}

	//qsort array
	qsort (data, length, sizeof(*data), compare_Job);	
	//push back on list

	for(int i=0;i<length;i++)
		list_Job_append(container, data[i]);

}

