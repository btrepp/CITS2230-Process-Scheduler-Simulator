#include "jobList.h"
#include "jobScheduler.h"

typedef struct VirtualCPU{
        JobListContainer* unscheduled_jobs;
        JobScheduleContainer* scheduled;
	
	JobElement* active_job;
	int active_job_scheduled_at;
	JobElement* remaining_active_job;

	int current_clock;
	int roundRobinQuanta;

	int mode;

} VirtualCPU;

void addJobToCPU(VirtualCPU* cpu, JobElement* job);
int incrementClock(VirtualCPU* cpu);
void setRoundRobinCPUQuanta(VirtualCPU* cpu, int quanta);
bool isCPUIdle(VirtualCPU* cpu);
void initCPU(VirtualCPU* cpu);


typedef int schedule_mode;
#define FCFS 1
#define RR 2
#define SPN 3
#define SRT 4

