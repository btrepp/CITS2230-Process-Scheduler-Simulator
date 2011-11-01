#include "stdlib.h"
#include "job.h"

//#define DEBUG
#include "debug.h"

LIST(Job);


int compare_Job_Arrival(const Job** job1, const Job** job2){
	return ((*job1)->arrival_time)-((*job2)->arrival_time);
}

int compare_Job_Remaining(const Job **job1, const Job** job2){
	return ((*job1)->length_time)-((*job2)->length_time);
}

