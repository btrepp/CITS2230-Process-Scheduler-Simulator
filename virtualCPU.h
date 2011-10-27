#ifndef VIRTUAL_CPU
#define VIRTUAL_CPU

#include "jobList.h"
#include "jobScheduler.h"
#include "memory.h"

typedef struct VirtualCPU{
        JobListContainer* unscheduled_jobs;
        list_JobSchedule* scheduled;
	
	JobElement* active_job;
	int active_job_scheduled_at;
	JobElement* remaining_active_job;
	
	bool memory_management;
	int current_clock;
	int roundRobinQuanta;

	int mode;

	Memory* physical_memory;

} VirtualCPU;

typedef int schedule_mode;
#define FCFS 1
#define RR 2
#define SPN 3
#define SRT 4

void addJobToCPU(VirtualCPU* cpu, JobElement* job);
int incrementClock(VirtualCPU* cpu);
void setRoundRobinCPUQuanta(VirtualCPU* cpu, int quanta);
void setSchedulingMode(VirtualCPU* cpu,schedule_mode mode);
bool isCPUIdle(VirtualCPU* cpu);
void initCPU(VirtualCPU* cpu);
void setMemoryManagement(VirtualCPU* cpu, bool value);

list_JobSchedule* getResults(VirtualCPU* cpu);

#endif 
