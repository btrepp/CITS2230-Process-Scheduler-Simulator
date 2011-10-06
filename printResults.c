#include "jobList.h"

void printResults(JobSchedule* start) {
 while(start != null ){
      printf(start->jobname);
      printf(" ");
    
      for(int i=0;i<start->amount;i++){
	  printf("(%d,%d) ",start->arrival_time[i],start->running_time[i]);
      }
      println();
      start=start->next();
  }
      
}