#ifndef JOB_SCHEDULER
#define JOB_SCHEDULER

#include "job.h"
#include <stdbool.h>

#include "list.h"
#include <stdlib.h>
typedef struct JobSchedule{
  char* jobname;
  int amount;
  int start_time;
  int running_time;
//  struct JobSchedule *next;
} JobSchedule;

LIST_PROTOTYPE(JobSchedule);
/*
typedef struct JobScheduleContainer{
        JobSchedule* head;
        JobSchedule* tail;
} JobScheduleContainer;
*/
//void insertScheduleElement(JobScheduleContainer* list, JobSchedule* jobsch);


//these are in printResults.c to save space
void printResults(list_JobSchedule* start);
void printResultsCompressed(list_JobSchedule* start);



#endif
