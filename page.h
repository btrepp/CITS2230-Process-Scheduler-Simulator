#ifndef MEM_PAGE
#define MEM_PAGE
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "job.h"

// Page structure
typedef struct Page{
	Job* job;
	char* location_in_memory;
	int last_accessed_at;
} Page;

LIST_PROTOTYPE(Page);

// Job processs structure in memory
typedef struct JobInMemory{
	Job* job;
	int pages_for_job;
	Page** pages;
} JobInMemory;

LIST_PROTOTYPE(JobInMemory);

void printFreePages(list_Page* list, FILE* out);


#endif

