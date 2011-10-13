#ifndef JOB_LIST
#define JOB_LIST

#include <stdio.h>


typedef struct JobElement{
  char* jobname;
  int arrival_time;
  int length_time;
  struct JobElement *next;
} JobElement;
 
typedef struct JobSchedule{
  char* jobname;
  int amount;
  int start_time;
  int running_time;
  struct JobSchedule *next;
} JobSchedule;

JobElement* FileToJobList(FILE* file);


#endif
