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

void markJobAsComplete(Job* job, bool complete);
#endif
