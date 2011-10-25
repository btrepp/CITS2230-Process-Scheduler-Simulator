
// LRU algorithm
// mode: swaping the blocks or removal of the pages from a blocks
// memoryblock: define which mem to remove or swap from(physical(50) or virtual(200)
// pagecounter: Checks if the removed pages is sufficient for the process that requires the space

// void LRU(mode, memoryblock, pagecounter)
// {
//   // Perform the LRU algorithm
// }

/*
 *  Used for Qsort, compares the time stamped when the 
 *  job was sent to the frame. Least recently use must
 *  appear first in the frame.
 */

#define FRAME_SIZE 50

int sortbyLRU(const void *a, const void *b)
{
  a = (frame *)a;
  b = (frame *)b;
  return (a->time - b->time);
}

// need the structures inplace to implement it properly
void LRU(somequeue* queue, int frames)
{
 
 qsort(queue, FRAME_SIZE, sizeof(frame), sortbyLRU);
 // now in tempQueue the least recently used will be in the front
 int i;
 // removing the least recently used frames from the memory
 for(i = 0; i<frames; i++)
 {
   queue[i]->finished = true; // boolean value to state that the frame is free to use
   
 }
// ....? is this it? it cant be it...can it?
}