#include <stdlib.h>

#include "page.h"
#define DEBUG
#include "debug.h"


LIST(Page);

/*
void addFreePage(FreePageListContainer* list, Page* page){
  FreePageListElement* newfreepage = malloc(sizeof(*newfreepage));
  newfreepage->emptypage=page;

  if(list->head==NULL)
        list->head=newfreepage;
  else
        list->tail->next=newfreepage;
  list->tail=newfreepage;

  debug_print("Marked free page:%s [%d]\n",page->jobname, (int) (page->location_in_memory-list->firstpagelocation));
}

Page* getFirstFreePage(FreePageListContainer* list){
        if(list->head==NULL){
		debug_print_string("No free pages left\n");
                return NULL;
	}
	
        FreePageListElement* returnelem = list->head;
        list->head = list->head->next;

        if(list->head==NULL){
		debug_print_string("Returning last empty page\n");
                list->tail=NULL;
	}
	Page* clearpage = returnelem->emptypage;
	debug_print("Available empty page: %d\n", (int)clearpage->location_in_memory-list->firstpagelocation);
	free(returnelem);
        return clearpage;
}
*/
void addJobInMemory(JobInMemoryList* list, JobInMemory* newjob){
  if(list->head==NULL)
        list->head=newjob;
  else
        list->tail->next=newjob;
  list->tail=newjob;
}

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
void printJobsInMemory(JobInMemoryList* list){
	JobInMemory* current = list->head;
	fprintf(stdout,"\nJobs In Memory \n\n");
	while(current!=NULL){
		fprintf(stdout,"\t%s\n",current->jobname);
		current=current->next;
	}
	fprintf(stdout,"\n");
}

