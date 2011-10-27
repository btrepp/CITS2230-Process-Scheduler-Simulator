#include "jobScheduler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printResults(list_JobSchedule* list) {
 list_node_JobSchedule* start = list->head;
 while(start != NULL ){
      JobSchedule* data = start->data;
      printf(data->jobname);
      printf(" ");
    
      for(int i=0;i<1;i++){
	  printf("(%d,%d) ",data->start_time,data->running_time);
      }
      printf("\n");
      start=start->next;
  }
      
}

void printResultsCompressed(list_JobSchedule* list){
  list_node_JobSchedule* start = list->head;
  while(start!=NULL){
	JobSchedule* data = start->data;
	if(data->jobname!=NULL){
		printf(data->jobname);
		printf(" ");

		list_node_JobSchedule* temp=start;
		//find next job schedule
		while(temp!=NULL){
			JobSchedule* tempdata = temp->data;
			if(tempdata->jobname!=NULL){
				int strcmpresult=strcmp(data->jobname,tempdata->jobname);	
				if(strcmpresult==0){
					printf("(%d,%d) ",tempdata->start_time,tempdata->running_time);
					//remove the element we printed (simplest way is to set name to null)
					if(temp!=start)
						tempdata->jobname=NULL;
				}
			}
			temp=temp->next;
		}
		printf("\n");
	}
	start=start->next;
  }
}
