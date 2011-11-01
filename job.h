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
void qsort_Job(list_Job* container, int ( * comparator ) ( const Job *, const Job* ));
int compare_Job_Arrival(const Job ** job1, const Job** job2);
int compare_Job_Remaining(const Job ** job1, const Job** job2);

#endif
