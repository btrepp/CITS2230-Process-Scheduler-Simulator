#ifndef JOB_SCHEDULER
#define JOB_SCHEDULER

#include "jobList.h"
#include <stdbool.h>

typedef struct JobSchedule{
  char* jobname;
  int amount;
  int start_time;
  int running_time;
  struct JobSchedule *next;
} JobSchedule;

typedef struct JobScheduleContainer{
        JobSchedule* head;
        JobSchedule* tail;
} JobScheduleContainer;

void insertScheduleElement(JobScheduleContainer* list, JobSchedule* jobsch);

#endif
