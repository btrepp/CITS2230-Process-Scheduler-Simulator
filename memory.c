#include "memory.h"
#include <stdlib.h>
#include <string.h>

#define DEBUG
#include "debug.h"

void initMemory(Memory* mem, int numpages, int pagesize){
	mem->number_of_pages = numpages;
	mem->pagesize= pagesize;
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

JobInMemory* loadJob(Memory* mem, JobElement* job, int clock){
	if(job->pages==-1){
		fprintf(stderr,"Memory management enabled without setting pages \n"
			"Please check the Job file\n"
			"Aborting...\n");
		exit(EXIT_FAILURE);
	}

	JobInMemory* newjobinmemory =NULL;
	//search for existing job in mem->jobs	
	JobInMemory* curjob = mem->jobs->head;
	while(curjob!=NULL){
		if(strcmp(curjob->jobname,job->jobname)==0){
			debug_print("Found job: %s already in memory \n", curjob->jobname);
			newjobinmemory = curjob;
			break;
		}	
		curjob=curjob->next;
	}
	int pages=0;
	if(newjobinmemory!=NULL){
		//verify jobs
		for(int j=0;j<newjobinmemory->pages_for_job;j++){
                        Page* thispage = (newjobinmemory->pages)[j];
                        
			if(thispage!=NULL && 
				strcmp(thispage->jobname, newjobinmemory->jobname)==0) {
				debug_print("Found page: %d for job %s \n", 
					PAGELOC(thispage,mem->freepages), newjobinmemory->jobname);
                        	thispage->last_accessed_at = clock;
                        	pages++;
			}
		}
	}
	else{
		//else create new job
		newjobinmemory = malloc(sizeof(*newjobinmemory));
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
			pages=i;
		}
		addJobInMemory(mem->jobs,newjobinmemory);
	}
	debug_print("Job:%s has %d pages in memory\n",newjobinmemory->jobname,pages);

	//LRU stuff


	return newjobinmemory;
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
				Page* pagetofree = jobmem->pages[i];
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

void printPages(Memory* mem, FILE*output){
	for(int i=0;i<mem->number_of_pages;i++){
		fprintf(output,"frame %d -- %s\n", i, mem->pages[i]->jobname);
	}
}


void printMemory(Memory* mem,FILE* output){
//	printJobsInMemory(mem->jobs);	

	for(int i=0;i<mem->number_of_pages;i++){
		for(int j=0;j<mem->pagesize;j++){
			fprintf(output,"%c",mem->memspace[mem->pagesize*i+j]);
		}
		fprintf(output,"\n");
	}
}

