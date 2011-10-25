#ifndef MEM_PAGE
#define MEM_PAGE


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
	FreePageListElement * head;
	FreePageListElement * tail;
}FreePageListContainer;


void initFreePageList(FreePageListContainer* cont);

void addFreePage(FreePageListContainer* cont, Page* pagetoadd);


#endif

