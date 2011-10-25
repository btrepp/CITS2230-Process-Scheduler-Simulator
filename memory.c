#include "memory.h"
#include <stdlib.h>

void initMemory(Memory* mem, int numpages, int pagesize){
	mem->number_of_pages = numpages;
	mem->memspace = malloc(sizeof(*(mem->memspace))*numpages*pagesize);
	
	mem->pages = malloc(sizeof(*(mem->pages))*numpages);	
	mem->freepages = malloc(sizeof(*(mem->freepages)));
	for(int i=0;i<numpages;i++){
		mem->pages[i].location_in_memory = &(mem->memspace[pagesize*i]);
		addFreePage(mem->freepages, &(mem->pages[i]));	
	}

}

