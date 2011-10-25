#include <stdlib.h>

#include "page.h"
#include "debug.h"

void addFreePage(FreePageListContainer* list, Page* page){
  FreePageListElement* newfreepage = malloc(sizeof(*newfreepage));
  newfreepage->emptypage=page;

  if(list->head==NULL)
        list->head=newfreepage;
  else
        list->tail->next=newfreepage;
  list->tail=newfreepage;

  debug_print("Marked page:%s[%d]\n",page->jobname, (int) page->location_in_memory);
}

Page* getFirstFreePage(FreePageListContainer* list){
        if(list->head==NULL)
                return NULL;

        FreePageListElement* returnelem = list->head;
        list->head = list->head->next;

        if(list->head==NULL)
                list->tail=NULL;

	Page* clearpage = returnelem->emptypage;
	free(returnelem);
        return clearpage;
}

void addJobInMemory(JobInMemoryList* list, JobInMemory* newjob){
  if(list->head==NULL)
        list->head=newjob;
  else
        list->tail->next=newjob;
  list->tail=newjob;
}

