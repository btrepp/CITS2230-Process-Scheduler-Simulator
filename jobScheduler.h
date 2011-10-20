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



/*typedef int schedule_mode;
#define FCFS 1
#define RR 2
#define SPN 3
#define SRT 4
*/
//void setSchedulingMode(schedule_mode mode);
JobSchedule* getResults();

void insertScheduleElement(JobScheduleContainer* list, JobSchedule* jobsch);

#endif
