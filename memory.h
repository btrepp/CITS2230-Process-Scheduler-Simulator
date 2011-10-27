#pragma once



#include "job.h"
#include "page.h"

typedef struct Memory{
	char* memspace;
	Page** pages;
//	FreePageListContainer * freepages;
	list_Page* freepages;	
	list_Page* LRU_list;
	list_JobInMemory* jobs;
	//JobInMemoryList* jobs;
	int number_of_pages;
	int pagesize; 
} Memory;

void initMemory(Memory* mem, int numpages,int pagesize);
JobInMemory* loadJob(Memory* mem, Job* job, int clock);
void freeJob(Memory* mem, Job* job);

void printMemory(Memory* mem,FILE* stream);
void printPages(Memory* mem, FILE* stream);
