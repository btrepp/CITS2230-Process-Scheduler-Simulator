#include "memory.h"
#include <stdlib.h>
#include <string.h>

#define DEBUG
#include "debug.h"

void initMemory(Memory* mem, int numpages, int pagesize){
	mem->number_of_pages = numpages;
	mem->memspace = malloc(sizeof(*(mem->memspace))*numpages*pagesize);
	
	mem->pages = malloc(sizeof(*(mem->pages))*numpages);	
	mem->freepages = malloc(sizeof(*(mem->freepages)));
	memset(mem->pages,0,sizeof(*(mem->pages)));
	memset(mem->freepages,0,sizeof(*(mem->freepages)));

	//sets the address of the first page in memory (for printing readability only);
	mem->freepages->firstpagelocation=(int) &(mem->memspace[0]);
	
	for(int i=0;i<numpages;i++){
		mem->pages[i] = malloc(sizeof(Page));

		mem->pages[i]->location_in_memory = &(mem->memspace[pagesize*i]);
		addFreePage(mem->freepages, mem->pages[i]);	
	}

	mem->jobs= malloc(sizeof(*(mem->jobs)));	
	memset(mem->jobs,0,sizeof(*(mem->jobs)));
}

void loadJob(Memory* mem, JobElement* job, int clock){
	if(job->pages==-1){
		fprintf(stderr,"Memory management enabled without setting pages \n"
			"Please check the Job file\n"
			"Aborting...\n");
		exit(EXIT_FAILURE);
	}

	//search for existing job in mem->jobs	
	
	//else create new job
	JobInMemory* newjobinmemory = malloc(sizeof(*newjobinmemory));
	memset(newjobinmemory, 0, sizeof(*newjobinmemory));

	newjobinmemory->jobname = job->jobname;
	newjobinmemory->pages_for_job = job->pages;
	newjobinmemory->pages = malloc(sizeof(*newjobinmemory->pages)*job->pages);
	
	for(int i=0;i<job->pages;i++){
		Page* thispage = getFirstFreePage(mem->freepages);
		if(thispage==NULL) {
			debug_print("Memory full, will perform LRU to get %d pages\n",job->pages-i);
			break;
		}
		
		thispage->jobname = job->jobname;
		thispage->last_accessed_at = clock;
		
		(newjobinmemory->pages)[i]=thispage;
	}

	//LRU stuff


	//add newjobinmemory to activejob queue

	addJobInMemory(mem->jobs,newjobinmemory);
}

void freeJob(Memory* mem, JobElement* job){
	debug_print("Freeing Job:%s from memory\n",job->jobname);
	JobInMemory* jobmem = mem->jobs->head;	
	JobInMemory* prev = NULL;
	while(jobmem!=NULL){
		//If we found the job we are looking for
		if(strcmp(jobmem->jobname,job->jobname)==0){
			//Mark all pages in this container as free
			for(int i=0;i<jobmem->pages_for_job;i++){
				Page* pagetofree = (jobmem->pages)[i];
				if(pagetofree==NULL){
					debug_print("Page %d used by job: %s is not in memory\n",
							i,jobmem->jobname);
				}
				else
					addFreePage(mem->freepages,(jobmem->pages)[i]);
			}		

			//Remove this page from the active job list	
			if(prev!=NULL)
				prev->next=jobmem->next;
			else
				mem->jobs->head=jobmem->next;	

			//Break out of the loop as the job can't be in the list twice
			break;
		}
		//move to next job in list
		prev=jobmem;
		jobmem=jobmem->next;
	}

}
