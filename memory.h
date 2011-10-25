#include "jobList.h"
#include "page.h"

typedef struct Memory{
	char* memspace;
	Page** pages;
	FreePageListContainer * freepages;
	JobInMemoryList* jobs;
	int number_of_pages;

} Memory;

void initMemory(Memory* mem, int numpages,int pagesize);
void loadJob(Memory* mem, JobElement* job, int clock);
