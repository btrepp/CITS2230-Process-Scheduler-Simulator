#include "stdlib.h"
#include "jobScheduler.h"
#include "jobList.h"
#include "sort.h"
#include <string.h>

#define DEBUG
#include "debug.h"


void addJob(JobListContainer* list, JobElement* job){
  JobElement* copy= malloc(sizeof(*copy));
  memcpy(copy,job,sizeof(*copy));
  copy->next=NULL;

  if(list->head==NULL)
        list->head=copy;
  else
        list->tail->next=copy;
  list->tail=copy;

  debug_print("Added Job:%s[%d,%d]\n",copy->jobname,copy->arrival_time,copy->length_time);
  printOrder(list);
}

bool empty(JobListContainer* list){
  if(list->head==NULL){
    return true;
  }
  return false;
}

JobElement* nextJobToSchedule(JobListContainer* list){
        printOrder(list);
        if(list->head==NULL)
                return NULL;

        JobElement* returnelem = list->head;
        list->head = list->head->next;

        if(list->head==NULL)
                list->tail=NULL;

        return returnelem;
}

void printOrder(JobListContainer* list){
        JobElement* current =list->head;
        char string[200];
        memset(string,0,200);
        while(current!=NULL){
                strcat(string,current->jobname);
                strcat(string,"->");
                current=current->next;
        }
        debug_print("%s\n",string);
}

void sortOnRemainingTime(JobListContainer* list){
   if(list->head!=NULL){
   //sort on shortest remaining time
       list->head = sortshortest(list->head);
       //set last correctly
       JobElement* temp=list->head;
       while(temp->next!=NULL){
             temp=temp->next;
       }
       list->tail=temp;
   }
}

void sortOnArrivalTime(JobListContainer* list){
    if(list->head!=NULL){
	list->head=sort(list->head);

	JobElement* temp=list->head;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	list->tail=temp;
    }
}	

