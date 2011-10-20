#include <stdio.h>
#include <stdbool.h>
//#include "JobList.c"
#include "jobList.h"
#include "jobScheduler.h"
#include "virtualCPU.h"
#include "setup.h"
#include "fileToJobList.h"
#include <string.h>

#define DEBUG
#include "debug.h"


int main(int argc, char* argv[]) {
	VirtualCPU cpu0;
	initCPU(&cpu0);

  
	FILE* pFile = setup(argc,argv,&cpu0);
	JobElement* list=FileToJobList(pFile); // list would be sorted on arrival time


	int clock=0;
	int totalclocks=0;
	int startclocks=0;
	while(list!=NULL){
		while(list!=NULL && clock+1==list->arrival_time){
			if(totalclocks==0)
				startclocks=clock;
			totalclocks+=list->length_time;

			debug_print("%s: %d @ %d \n",list->jobname,list->arrival_time,clock);
			addJobToCPU(&cpu0,list);		
			list=list->next;
		}
		clock=incrementClock(&cpu0);
// 		debug_print("%s \n",list->jobname);
// 		list=list->next;
		
	}

	while(isCPUIdle(&cpu0)==false && clock<startclocks+2*totalclocks)
		clock=incrementClock(&cpu0);
	printf("Complete!\n");

	JobSchedule* results = getResults(&cpu0)->head;
	printResultsCompressed(results);

	//printf(" [%s] \n", FileToJobList);
	return 0;
}
