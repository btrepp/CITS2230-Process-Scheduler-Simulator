#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "jobScheduler.h"

void printUsage(){
  printf("TODO\n");
}

FILE* setup(int argc, char *argv[]){
 
  if(argc<3){
    printUsage();
    exit(EXIT_FAILURE);
  }
  
  char* filename = "";
  char* scheduler = argv[1];
  int quantum=0;
		    
  if(strcmp(scheduler,"RR")==0){
    if(argc<4){
      printUsage();
      exit(EXIT_FAILURE);
    }
    filename=argv[3];
    errno=0;
    quantum= strtol(argv[2], (char **) NULL, 10);
    if(errno==EINVAL || errno==ERANGE){
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  }
  else
    filename=argv[2];
  
  errno=0;
  FILE* fp = fopen(filename,"r");
  
  if(fp==NULL){
    perror(NULL);
    exit(EXIT_FAILURE);
  }
  
  if(strcmp(scheduler,"RR")==0){
	setRoundRobinQuanta(quantum);
	setSchedulingMode(RR);
  }
  if(strcmp(scheduler,"FCFS")==0)	setSchedulingMode(FCFS);
  if(strcmp(scheduler,"SPN")==0) setSchedulingMode(SPN);
  if(strcmp(scheduler,"SRT")==0) setSchedulingMode(SRT);
  
  return fp;
}
