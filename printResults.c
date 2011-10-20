#include "jobScheduler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printResults(JobSchedule* start) {
 while(start != NULL ){
      printf(start->jobname);
      printf(" ");
    
      for(int i=0;i<1;i++){
	  printf("(%d,%d) ",start->start_time,start->running_time);
      }
      printf("\n");
      start=start->next;
  }
      
}

void printResultsCompressed(JobSchedule* start){
  while(start!=NULL){
	if(start->jobname!=NULL){
		printf(start->jobname);
		printf(" ");

		JobSchedule* temp=start;
		//find next job schedule
		while(temp!=NULL){
			if(temp->jobname!=NULL){
				int strcmpresult=strcmp(start->jobname,temp->jobname);	
				if(strcmpresult==0){
					printf("(%d,%d) ",temp->start_time,temp->running_time);
					//remove the element we printed (simplest way is to set name to null)
					if(temp!=start)
						temp->jobname=NULL;
				}
			}
			temp=temp->next;
		}
		printf("\n");
	}
	start=start->next;
  }
}
