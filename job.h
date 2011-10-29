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
} Job;

LIST_PROTOTYPE(Job);
void qsort_Job(list_Job* container, int ( * comparator ) ( const void *, const void * ));
int compare_Job_Arrival(const void * job1, const void* job2);
int compare_Job_Remaining(const void * job1, const void* job2);

//void markJobAsComplete(Job* job, bool complete);
#endif
