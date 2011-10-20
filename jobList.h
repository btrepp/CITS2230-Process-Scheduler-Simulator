#ifndef JOB_LIST
#define JOB_LIST

#include <stdio.h>
#include <stdbool.h>

typedef struct JobElement{
  char* jobname;
  int arrival_time;
  int length_time;
  struct JobElement *next;
} JobElement;

typedef struct JobListContainer{
	JobElement* head;
	JobElement* tail;
} JobListContainer;
 
void addJob(JobListContainer* list,JobElement* job);
JobElement* nextJobToSchedule(JobListContainer* list);
bool empty(JobListContainer* list);
void printOrder(JobListContainer* list);

void sortOnRemainingTime(JobListContainer* list);
void sortOnArrivalTime(JobListContainer* list);

#endif
