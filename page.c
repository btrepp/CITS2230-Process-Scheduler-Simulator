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

