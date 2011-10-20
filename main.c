#include <stdio.h>
#include <stdbool.h>
//#include "JobList.c"
#include "jobList.h"
#include "jobScheduler.h"
#include "printResults.h"
#include "virtualCPU.h"
#include "setup.h"
#include "fileToJobList.h"
#include <string.h>

#define DEBUG
#include "debug.h"


int main(int argc, char* argv[]) {

  
	FILE* pFile = setup(argc,argv);
	//pFile = fopen("Jobs.txt","r");
	JobElement* list=FileToJobList(pFile); // list would be sorted on arrival time

	VirtualCPU cpu0;
	memset(&cpu0,0,sizeof(cpu0));

	int clock=0;
	while(list!=NULL){
		while(list!=NULL && clock+1==list->arrival_time){
			debug_print("%s: %d @ %d \n",list->jobname,list->arrival_time,clock);
			addJobToCPU(&cpu0,list);		
			list=list->next;
		}
		clock=incrementClock(&cpu0);
// 		debug_print("%s \n",list->jobname);
// 		list=list->next;
		
	}

	while(isCPUIdle(&cpu0)==false /*&& clock<20*/)
		clock=incrementClock(&cpu0);
	printf("Complete!\n");

	JobSchedule* results = getResults();
	printResultsCompressed(results);

	//printf(" [%s] \n", FileToJobList);
	return 0;
}
