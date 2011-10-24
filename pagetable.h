// Page table for each process
typedef struct frame{ // frame
    int jobNumber; // jobnumber in the frame
    int time; // timer when the job was sent to the memory 
    int index;
} frame;

