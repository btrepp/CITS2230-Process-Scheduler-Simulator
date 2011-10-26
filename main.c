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

void dumpMemory(int clock, Settings* set, Memory* mem){
   if(set->mem_management && clock==set->mem_quanta){
	fprintf(set->memoutput,"Jobs held in physical memory frames at t=%d\n",clock);
	printPages(mem, set->memoutput);
	fprintf(set->memoutput,"Content of physical memory at t=%d\n\n",clock);
	printMemory(mem,set->memoutput);	
   }
}

int main(int argc, char* argv[]) {
	VirtualCPU cpu0;
	initCPU(&cpu0);

  
	Settings* set = setup(argc,argv);
	JobElement* list=FileToJobList(set->jobinput); // list would be sorted on arrival time

	setSchedulingMode(&cpu0,set->mode);
	setRoundRobinCPUQuanta(&cpu0,set->rr_quanta);
	setMemoryManagement(&cpu0,set->mem_management);

	int clock=cpu0.current_clock;
	int totalclocks=0;
	int startclocks=clock;
	while(list!=NULL){
		while(list!=NULL && clock==list->arrival_time){
			if(totalclocks==0)
				startclocks=clock;
			totalclocks+=list->length_time;

			debug_print("%s: %d @ %d \n",list->jobname,list->arrival_time,clock);
			addJobToCPU(&cpu0,list);		
			list=list->next;
		}
		clock=incrementClock(&cpu0);
		dumpMemory(clock,set,cpu0.physical_memory);

// 		debug_print("%s \n",list->jobname);
// 		list=list->next;
		
	}

	while(isCPUIdle(&cpu0)==false /*&& clock<startclocks+2*totalclocks*/){
		debug_print("Incrementing clock %d\n",clock);
		clock=incrementClock(&cpu0);
		dumpMemory(clock,set,cpu0.physical_memory);
	}
	debug_print_string("Complete!\n");

	JobSchedule* results = getResults(&cpu0)->head;
	printResultsCompressed(results);

	//printf(" [%s] \n", FileToJobList);
	return 0;
}
