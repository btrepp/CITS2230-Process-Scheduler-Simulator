#ifndef JOB_LIST
#define JOB_LIST

#include <stdio.h>
#include <stdbool.h>
#include "list.h"

typedef struct Job{
  char* jobname;
  int arrival_time;
  int length_time;
  int pages; // number of pages required
  bool completed;
//  struct JobElement *next;
} Job;

LIST_PROTOTYPE(Job);

/*
typedef struct JobListContainer{
	JobElement* head;
	JobElement* tail;
} JobListContainer;
 */
/*
void addJob(JobListContainer* list,JobElement* job);
JobElement* nextJobToSchedule(JobListContainer* list);
bool empty(JobListContainer* list);
void printOrder(JobListContainer* list);
*/
/*
void sortOnRemainingTime(JobListContainer* list);
void sortOnArrivalTime(JobListContainer* list);*/
void markJobAsComplete(Job* job, bool complete);
#endif
