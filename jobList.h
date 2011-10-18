#ifndef JOB_LIST
#define JOB_LIST

#include <stdio.h>

typedef struct JobElement{
  char* jobname;
  int arrival_time;
  int length_time;
  struct JobElement *next;
} JobElement;
 
JobElement* FileToJobList(FILE* file);


#endif
