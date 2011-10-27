#include <stdio.h>
#include <stdbool.h>
//#include "JobList.c"
#include "job.h"
#include "jobScheduler.h"
#include "virtualCPU.h"
#include "setup.h"
#include "fileToJobList.h"
#include <string.h>
#include "htmloutput.h"

#define DEBUG
#include "debug.h"



void dumpMemory(int clock, Settings* set, Memory* mem){
    memToJavascriptArray(set->htmloutput, mem);  

    if(set->mem_management && clock-1==set->mem_quanta){
	fprintf(set->memoutput,"\nJobs held in physical memory frames at t=%d\n\n",clock-1);
	printPages(mem, set->memoutput);
	fprintf(set->memoutput,"\nContent of physical memory at t=%d\n\n",clock-1);
	printMemory(mem,set->memoutput);	
   }
}

int main(int argc, char* argv[]) {
	VirtualCPU cpu0;
	initCPU(&cpu0);

  
	Settings* set = setup(argc,argv);
	header(set->htmloutput);
	list_Job* list=FileToJobList(set->jobinput); // list would be sorted on arrival time

	setSchedulingMode(&cpu0,set->mode);
	setRoundRobinCPUQuanta(&cpu0,set->rr_quanta);
	setMemoryManagement(&cpu0,set->mem_management);

	int clock=cpu0.current_clock;
	int totalclocks=0;
	int startclocks=clock;

	list_iterator_Job* it = malloc(sizeof(*it));
	list_Job_iterator_init(it, list);

	Job* current = list_Job_examine(it);
	while(current!=NULL){
		while(current!=NULL && clock==current->arrival_time){
			if(totalclocks==0)
				startclocks=clock;
			totalclocks+=current->length_time;

			debug_print("%s: %d @ %d \n",current->jobname,current->arrival_time,clock);
			addJobToCPU(&cpu0,current);		
			current= list_Job_next(it);
		}
		clock=incrementClock(&cpu0);
		dumpMemory(clock,set,cpu0.physical_memory);

// 		debug_print("%s \n",list->jobname);
// 		list=list->next;
		
	}
	free(list);
	while(isCPUIdle(&cpu0)==false /*&& clock<startclocks+2*totalclocks*/){
		debug_print("Incrementing clock %d\n",clock);
		clock=incrementClock(&cpu0);
		dumpMemory(clock,set,cpu0.physical_memory);
	}
	debug_print_string("Complete!\n");

	list_JobScheduleResult* results = getResults(&cpu0);
	//printResults(results);
	printResultsCompressed(results);

	footer(set->htmloutput);
	//printf(" [%s] \n", FileToJobList);
	return 0;
}
