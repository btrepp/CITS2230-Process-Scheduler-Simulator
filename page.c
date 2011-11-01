#include <stdlib.h>

#include "page.h"
//#define DEBUG
#include "debug.h"

LIST(Page);
LIST(JobInMemory);

void printFreePages(list_Page* list, FILE* out){
	list_node_Page* current = list->head;
	while(current!=NULL){
		fprintf(out,"Free page: %d\n", (int) current->data->location_in_memory);
		current=current->next;
	}
}


void printPagesInMemory(Page** firstpage, int numpages){
	return;
}
void printJobsInMemory(list_JobInMemory* list){
	list_node_JobInMemory* current = list->head;
	fprintf(stdout,"\nJobs In Memory \n\n");
	while(current!=NULL){
		fprintf(stdout,"\t%s\n",current->data->job->jobname);
		current=current->next;
	}
	fprintf(stdout,"\n");
}

