struct JobElement;

struct{
  char* jobname;
  int arrival_time;
  int length_time;
  JobElement *next;
} JobElement;
 

struct JobSchedule;

struct{
  char* jobname;
  int amount;
  int[] start_time;
  int[] running_time;
  JobSchedule *next;
} JobSchedule;