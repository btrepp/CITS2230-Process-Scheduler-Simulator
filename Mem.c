#include "pagetable.h"
int virmem[200]; // 200 pages of virtual mem
int physmem[50]; // 50 frames of physical mem

/**
  *  Jobs require pages in the virtual mem, which gets
  *  loaded up in the physical mem which is of size 50.
  *  As the jobs are processed the virtual mem and 
  *  physical mem get swapped out accorrdingly.
  *  Use a page table to track what is in and what is out 
  *  of the memory
  *  Each page allocated for the Job must contain a string
  *  that concatenates the job numbers together for a 
  *  total of 4digits, ie job 20 = 2020
*/

/**
 *	The physmem and virmem must reflect which algorithm 
 *	is being used in the scheduling. Pages for the processed
 *	need not be continguious  
 * 	NOTE: Each frame contains one page...ie its a page frame 
 * 	Also assume that all pages required by all the processes
 * 	area already full loaded in the 200 virtual mem space.
 */

// Should take the job and store it in the physical mem *valid for one job
void storemem(JobElement* list) 
{
  JobElement* Job = list;
  PageTable Page;
  int PageCount;
  //*Assumming that no process requires all the memory allocations
  while(list != NULL)
  {
    PageCount = Job-> numpage; // number of pages required by the job
    // Dont care that the physicalmem is full
    // physmem contains 50 frames
    for(int k = 0, k < 50, k++)
    {
      if(physmem[k] == NULL) { // if there is an empty space
	physmem[k] = Job->pages; // Place the Job page in here
	PageCount--;
      }
    }
    // after searching and filling an empty frame in the physicalmem
    // and there is still more pages to be loaded for the job.
    // Need to use the LRU algorithm to remove the pages from the mem.
    // NOTE:The LRU places the removed algorithm into the virtual mem.
    //		and if theres not enough space in the virtual mem(200).
    //		perform an LRU in the virtual mem(200) to remove the 
    //		pages from it.
    if(PageCount != 0 ){
     // LRU(physmem, PageCount); // Removes LRU pages, need PageCount just incase the first removal is not sufficient
      qsort(table, 50, sizeof(frame),LRU); // sorts the physical mem with LRU at the start of the array
      for(int k = 0, k <50, k++)
      {
	if(physmem[k] == NULL) {
	  physmem[k] = Job->pages;
	  PageCount--;
	}   
      }
    }
  }
}


