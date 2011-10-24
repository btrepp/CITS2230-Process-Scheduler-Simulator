
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

int LRU(const void *a, const void *b)
{
  a = (frame *)a;
  b = (frame *)b;
  return (a->time - b->time);
}