#ifndef VIRTUAL_CPU
#define VIRTUAL_CPU

#include "job.h"
#include "jobScheduler.h"
#include "memory.h"

typedef struct UnprocessedJob{
	Job* job;
	int time_remaining;
} UnprocessedJob;	

LIST_PROTOTYPE(UnprocessedJob);


typedef struct VirtualCPU{
        //JobListContainer* unscheduled_jobs;
        list_UnprocessedJob* unscheduled_jobs;
	list_JobScheduleResult* scheduled;
	
	JobScheduleResult* active_job;
	UnprocessedJob* remaining_active_job;
	
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

void addJobToCPU(VirtualCPU* cpu, Job* job);
int incrementClock(VirtualCPU* cpu);
void setRoundRobinCPUQuanta(VirtualCPU* cpu, int quanta);
void setSchedulingMode(VirtualCPU* cpu,schedule_mode mode);
bool isCPUIdle(VirtualCPU* cpu);
void initCPU(VirtualCPU* cpu);
void setMemoryManagement(VirtualCPU* cpu, bool value);

list_JobScheduleResult* getResults(VirtualCPU* cpu);

#endif 
