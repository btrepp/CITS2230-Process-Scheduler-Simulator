#ifndef JOB_SCHEDULER
#define JOB_SCHEDULER

#include "job.h"
#include <stdbool.h>

#include "list.h"
#include <stdlib.h>

typedef struct JobScheduleResult{
  Job* job;
  int start_time;
  int running_time;
} JobScheduleResult;

LIST_PROTOTYPE(JobScheduleResult);

//these are in printResults.c to save space
void printResults(list_JobScheduleResult* start);
void printResultsCompressed(list_JobScheduleResult* start);



#endif
