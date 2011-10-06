#include <stdio.h>
#include "JobList.h"

void printUsage(){
  printf("TODO\n");
}

int main(int argc, char *argv[]) 
{
 
  if(argc<3){
    printUsage();
    exit(EXIT_FAILURE);
  }
  
  string filename = "";
  string scheduler = argv[1];
  int quantum=0;
		    
  if(strcmp(scheduler,"RR"){
    if(argc<4){
      printUsage();
      exit(EXIT_FAILURE);
    }
    filename=argv[3];
    errno=0;
    strtol(argv[2], (char **) NULL, 10);
    if(errno==EINVAL || errno==ERANGE){
      perror(errno);
      exit(EXIT_FAILURE);
  }
  else
    filename=argv[2];
  
  errno=0;
  FILE* fp = fopen(filename);
  
  if(fp==NULL){
    perror(errno);
    exit(EXIT_FAILURE);
  }
  
  JobList* start = FileToJobList(fp);
  
  if(strcmp(scheduler,"RR")) roundrobin;
  if(strcmp(scheduler,"FCFS")) firstcome;
  if(strcmp(scheduler,"SPN")) shortprocess;
  if(strcmp(scheduler,"SRT")) shorttime;

   
}