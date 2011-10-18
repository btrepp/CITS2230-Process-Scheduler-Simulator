typedef struct JobSchedule{
  char* jobname;
  int amount;
  int start_time;
  int running_time;
  struct JobSchedule *next;
} JobSchedule;

