#include JobList.h

typedef struct{
  string jobname;
  int arrival_time;
  int length_time;
  JobElement *next;
} JobElement;
 