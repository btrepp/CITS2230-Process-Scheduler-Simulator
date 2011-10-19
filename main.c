#include <stdio.h>
#include <stdbool.h>
//#include "JobList.c"
#include "jobList.h"
#include "jobScheduler.h"
#include "printResults.h"
#include "setup.h"


#define DEBUG
#include "debug.h"
//#include "runschedules.c"
//#include "Pscheduler.c"
//#include "printResults.c"
//#include "JobScheduler.c"
//#include "FileToJobList.c"

int main(int argc, char* argv[]) {

	FILE* pFile = setup(argc,argv);
	JobElement* list= FileToJobList(pFile);
	
	int clock=0;
	while(list!=NULL){
		while(list!=NULL && clock+1==list->arrival_time){
			debug_print("%s: %d @ %d \n",list->jobname,list->arrival_time,clock);
			addJob(list);		
			list=list->next;
		}
		clock=incrementClock();
		
	}

	while(no_more_jobs()==false /*&& clock<20*/)
		clock=incrementClock();
	printf("Complete!\n");

	JobSchedule* results = getResults();
	printResultsCompressed(results);

	//printf(" [%s] \n", FileToJobList);
	return 0;
}
