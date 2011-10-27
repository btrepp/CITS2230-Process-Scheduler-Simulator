#include "jobScheduler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printResults(list_JobScheduleResult* list) {
 list_node_JobScheduleResult* start = list->head;
 while(start != NULL ){
      JobScheduleResult* data = start->data;
      printf(data->job->jobname);
      printf(" ");
    
      for(int i=0;i<1;i++){
	  printf("(%d,%d) ",data->start_time,data->running_time);
      }
      printf("\n");
      start=start->next;
  }
      
}

void printResultsCompressed(list_JobScheduleResult* list){
  list_node_JobScheduleResult* start = list->head;
  while(start!=NULL){
	JobScheduleResult* data = start->data;
	if(data->job!=NULL){
		printf(data->job->jobname);
		printf(" ");

		list_node_JobScheduleResult* temp=start;
		//find next job schedule
		while(temp!=NULL){
			JobScheduleResult* tempdata = temp->data;
			if(tempdata->job!=NULL){
				if(tempdata->job == data->job){
					printf("(%d,%d) ",tempdata->start_time,tempdata->running_time);
					//remove the element we printed (simplest way is to set name to null)
					if(temp!=start)
						tempdata->job=NULL;
				}
			}
			temp=temp->next;
		}
		printf("\n");
	}
	start=start->next;
  }
}
