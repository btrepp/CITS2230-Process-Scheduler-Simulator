#include JobList.h

struct{
  string jobname;
  int arrival_time;
  int length_time;
  JobElement *next;
} JobElement;
 