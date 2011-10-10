//struct JobElement;

typedef struct{
  char* jobname;
  int arrival_time;
  int length_time;
  JobElement *next;
} JobElement;
 

//struct JobSchedule;

typedef struct{
  char* jobname;
  int amount;
  int start_time;
  int running_time;
  JobSchedule *next;
} JobSchedule;

typedef JobElement JobList;