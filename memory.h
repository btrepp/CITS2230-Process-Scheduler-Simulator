#include "jobList.h"
#include "page.h"

typedef struct Memory{
	char* memspace;
	Page* pages;
	FreePageListContainer * freepages;
	int number_of_pages;

} Memory;

void initMemory(Memory* mem, int numpages,int pagesize);
