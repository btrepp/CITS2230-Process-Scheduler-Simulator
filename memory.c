#include "memory.h"
#include <stdlib.h>
#include <string.h>

void initMemory(Memory* mem, int numpages, int pagesize){
	mem->number_of_pages = numpages;
	mem->memspace = malloc(sizeof(*(mem->memspace))*numpages*pagesize);
	
	mem->pages = malloc(sizeof(*(mem->pages))*numpages);	
	mem->freepages = malloc(sizeof(*(mem->freepages)));
	memset(mem->pages,0,sizeof(*(mem->pages)));
	memset(mem->freepages,0,sizeof(*(mem->freepages)));
	for(int i=0;i<numpages;i++){
		mem->pages[i]->location_in_memory = &(mem->memspace[pagesize*i]);
		addFreePage(mem->freepages, mem->pages[i]);	
	}

	mem->jobs= malloc(sizeof(*(mem->jobs)));	
	memset(mem->jobs,0,sizeof(*(mem->jobs)));
}

void loadJob(Memory* mem, JobElement* job, int clock){
	//search for existing job in mem->jobs	

	//else create new job
	
	JobInMemory* newjobinmemory = malloc(sizeof(*newjobinmemory));
	memset(newjobinmemory, 0, sizeof(*newjobinmemory));

	newjobinmemory->jobname = job->jobname;
	newjobinmemory->pages_for_job = job->pages;
	newjobinmemory->pages = malloc(sizeof(*newjobinmemory->pages)*job->pages);
	
	for(int i=0;i<job->pages;i++){
		Page* thispage = getFirstFreePage(mem->freepages);
		if(thispage==NULL) break;
		
		thispage->jobname = job->jobname;
		thispage->last_accessed_at = clock;
		
		(newjobinmemory->pages)[i]=thispage;
	}



}
