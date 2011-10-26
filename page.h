#ifndef MEM_PAGE
#define MEM_PAGE

#define PAGELOC(page,list) ((int) ((page)->location_in_memory - (list)->firstpagelocation))


typedef struct Page{
	char* jobname;
	char* location_in_memory;
	int last_accessed_at;
} Page;

typedef struct FreePageListElement{
	Page* emptypage;
	struct FreePageListElement* next;
}FreePageListElement;	

typedef struct FreePageListContainer{
	int firstpagelocation;
	FreePageListElement * head;
	FreePageListElement * tail;
}FreePageListContainer;

typedef struct JobInMemory{
	char* jobname;
	int pages_for_job;
	Page** pages;
	struct JobInMemory* next;
} JobInMemory;

typedef struct JobInMemoryList{
	JobInMemory* head;
	JobInMemory* tail;
} JobInMemoryList; 


void addFreePage(FreePageListContainer* cont, Page* pagetoadd);
Page* getFirstFreePage(FreePageListContainer* cont);

void addJobInMemory(JobInMemoryList* cont, JobInMemory* memjob);
void printJobsInMemory(JobInMemoryList* cont);

#endif

