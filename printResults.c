#include "printResults.h"
#include <stdio.h>

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
