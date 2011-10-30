#include "stdlib.h"
#include "job.h"

//#define DEBUG
#include "debug.h"

LIST(Job);


int compare_Job_Arrival(const Job * job1, const Job* job2){
	return (((*((Job**)job1))->arrival_time)-((*((Job**)job2))->arrival_time));
}

int compare_Job_Remaining(const Job *job1, const Job* job2){
	return (((*((Job**)job1))->length_time)-((*((Job**)job2))->length_time));
}
/*
void qsort_Job(list_Job* container, int ( * comparator ) ( const Job *, const Job * )){
        //pop everything off into array
        int length = list_Job_length(container);
        
        Job** data = malloc(sizeof(*data)*length);
        Job* current = NULL;
        {
		int i=0;
    		while((current=list_Job_pop(container))!=NULL){
        	         data[i++] = current;
        	}
        }
        
       //qsort array
       typedef int (*compfn)(const void*, const void*);
       qsort (data, length, sizeof(*data), (compfn)(comparator));
       //push back on list
       
       for(int i=0;i<length;i++)
           list_Job_append(container, data[i]);

	free(data);
}
*/




/*
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
*/
/*void markJobAsComplete(Job* job, bool complete){
	if(job!=NULL)
		job->completed=complete;	
}
*/
