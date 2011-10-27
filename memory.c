#include "memory.h"
#include <stdlib.h>
#include <string.h>

#define DEBUG
#include "debug.h"

#define PAGELOC(page,list) ((int) ((page)->location_in_memory-list->location_in_memory))

void markPageAsFree(Memory* mem, Page* page){
	list_Page_append(mem->freepages, page);
	debug_print("Marked as free: %d\n",PAGELOC(page,mem->pages[0]));
}

void initMemory(Memory* mem, int numpages, int pagesize){
	mem->number_of_pages = numpages;
	mem->pagesize= pagesize;
	mem->memspace = malloc(sizeof(*(mem->memspace))*numpages*pagesize);
	
	mem->pages = malloc(sizeof(*(mem->pages))*numpages);	
	mem->freepages = malloc(sizeof(*(mem->freepages)));
	mem->LRU_list = malloc(sizeof(*(mem->LRU_list)));
	memset(mem->pages,0,sizeof(*(mem->pages)));
	memset(mem->freepages,0,sizeof(*(mem->freepages)));
	memset(mem->LRU_list,0,sizeof(*(mem->LRU_list)));

	//sets the address of the first page in memory (for printing readability only);
	
	for(int i=0;i<numpages;i++){
		mem->pages[i] = malloc(sizeof(Page));

		mem->pages[i]->location_in_memory = &(mem->memspace[pagesize*i]);
		markPageAsFree(mem,mem->pages[i]);
	}
	mem->jobs= malloc(sizeof(*(mem->jobs)));	
	memset(mem->jobs,0,sizeof(*(mem->jobs)));
}

bool assignPage(Memory* mem,JobInMemory* job,int index,int clock){
	Page* thispage = list_Page_pop(mem->freepages);
        if(thispage==NULL) {
        	debug_print("Memory full, will perform LRU to get %d pages\n",job->pages_for_job-index);
                return false;
        }
        debug_print("Available empty page: %d\n",PAGELOC(thispage,mem->pages[0]));
        thispage->jobname = job->jobname;
        thispage->last_accessed_at = clock;

        (job->pages)[index]=thispage;
	
	list_Page_append(mem->LRU_list, thispage);
	return true;
}

void LRU(Memory* mem, int frames){
	debug_print("Removing %d oldest pages from RAM\n", frames);
	for(int i=0;i<frames;i++){
		Page* freedpage = list_Page_pop(mem->LRU_list);
		markPageAsFree(mem, freedpage);
	}
}

JobInMemory* findJob(list_JobInMemory* jobs, JobElement* job){
	list_iterator_JobInMemory* it = malloc(sizeof(*it));
	list_JobInMemory_iterator_init(it,jobs);
	//search for existing job in mem->jobs	
	JobInMemory* curjob = NULL;
	while((curjob=list_JobInMemory_examine(it))!=NULL){
		if(strcmp(curjob->jobname,job->jobname)==0){
			debug_print("Found job: %s already in memory \n", curjob->jobname);
			break;
		}	
		list_JobInMemory_next(it);
	}
	free(it);
	return curjob;
}
	
JobInMemory* loadJob(Memory* mem, JobElement* job, int clock){
	if(job->pages==-1){
		fprintf(stderr,"Memory management enabled without setting pages \n"
			"Please check the Job file\n"
			"Aborting...\n");
		exit(EXIT_FAILURE);
	}

	JobInMemory* curjob = findJob(mem->jobs, job);
	int pages=0;
	if(curjob!=NULL){
		//verify jobs
		for(int j=0;j<curjob->pages_for_job;j++){
                        Page* thispage = (curjob->pages)[j];
                        
			if(thispage!=NULL && 
				strcmp(thispage->jobname, curjob->jobname)==0) {
				debug_print("Found page: %d for job %s \n", 
					PAGELOC(thispage,mem->pages[0]), curjob->jobname);
                        	thispage->last_accessed_at = clock;
				pages++;

				list_iterator_Page* it= malloc(sizeof(*it));
			        list_Page_iterator_init(it,mem->LRU_list);
				Page* curpage = NULL;
				while((curpage= list_Page_examine(it))!=NULL){
					if(curpage == thispage){
						list_Page_remove(it);
						
						break;
					}				
					list_Page_next(it);
				}
				list_Page_append(mem->LRU_list, thispage);
				free(it);
			}
			// else assign new page
			//thispage NULL assignPage
		}
	}
	else{
		//else create new job
		JobInMemory* newjobinmemory = malloc(sizeof(*newjobinmemory));
		memset(newjobinmemory, 0, sizeof(*newjobinmemory));
		newjobinmemory->jobname = job->jobname;
		newjobinmemory->pages_for_job = job->pages;
		newjobinmemory->pages = malloc(sizeof(*newjobinmemory->pages)*job->pages);

		for(int i=0;i<job->pages;i++){
			//Page* thispage = getFirstFreePage(mem->freepages);
			if(assignPage(mem,newjobinmemory,i,clock)){
				pages++;
			}
			else{
				break;
			}
		}
		list_JobInMemory_append(mem->jobs,newjobinmemory);
		curjob=newjobinmemory;
	}
	debug_print("Job:%s has %d pages in memory\n",curjob->jobname,pages);

	//LRU stuff
	
	LRU(mem, curjob->pages_for_job-pages);
	
	for(int i=pages;i<curjob->pages_for_job;i++){
		if(assignPage(mem,curjob,i,clock)){
			pages++;
		}
		else{
			fprintf(stderr, "Was unable to free enough pages!\n");
			exit(EXIT_FAILURE);
		}
	}

	return curjob;
}

void freeJob(Memory* mem, JobElement* job){
	debug_print("Freeing Job:%s from memory\n",job->jobname);

	list_node_JobInMemory* jobmem = mem->jobs->head;	
	list_node_JobInMemory* prev = NULL;
	while(jobmem!=NULL){
		//If we found the job we are looking for
		if(strcmp(jobmem->data->jobname,job->jobname)==0){
			JobInMemory* found = jobmem->data;
			//Mark all pages in this container as free
			for(int i=0;i<found->pages_for_job;i++){
				Page* pagetofree = found->pages[i];
				if(pagetofree==NULL){
					debug_print("Page %d used by job: %s is not in memory\n",
							i,found->jobname);
				}
				else{
					markPageAsFree(mem,pagetofree);
				}
			}		

			//Remove this page from the active job list	
			if(prev!=NULL)
				prev->next=jobmem->next;
			else
				mem->jobs->head=jobmem->next;	

			if(mem->jobs->head==NULL) mem->jobs->tail=NULL;
			free(found);
			free(jobmem);

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

