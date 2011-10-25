
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include "jobScheduler.h"
#include <unistd.h>
#include <ctype.h>

#include "virtualCPU.h"

void printUsage(int argc, char*argv[]){
  printf("usage:\n %s [sv] Scheduler {Quantum} Input File {Memory Quantum} \n", argv[0]);
  printf("\n \t -s : Run the scheduler without memory management (default)\n");
  printf("\t -v : Run the scheduler with memory management\n");
  printf("\t Scheduler : Scheduling algorithm to run, options are \n");
  printf("\t\t FCFS : First Come First Serve\n");
  printf("\t\t SPN : Shortest Process Next\n");
  printf("\t\t SRT : Shortest Remaining Time\n");
  printf("\t\t RR : Round Robin\n\n");
  printf("\t{Quantum} : The time quantum for Round Robin scheduling\n");
  printf("\tInput File : The file to load jobs from\n");
  printf("\t{Memory Quantum} : Print memory usage every Quantum clock ticks (only if -v is set) \n");
  printf("\n");

}

FILE* setup(int argc, char *argv[], VirtualCPU* cpu){
 
  if(argc<3){
    printUsage(argc,argv);
    exit(EXIT_FAILURE);
  }

  int c;
  
  while ((c = getopt (argc, argv, "sv")) != -1)
         switch (c){
           case 's':
             setMemoryManagement(cpu,false);
             break;
           case 'v':
             setMemoryManagement(cpu,true);
             break;
           case '?':
             if (optopt == 'c')
               fprintf (stderr, "Option -%c requires an argument.\n", optopt);
             else if (isprint (optopt))
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
             else
               fprintf (stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
           default:
             abort ();
           }

#define RR_ARGS_VALUE 3+optind
#define RR_FILENAME_POS 2+optind 
#define RR_QUANTUM 1+optind
#define FILENAME_POS 1+optind
#define SCHEDULER_POS 0+optind

  
  char* filename = "";
  char* scheduler = argv[SCHEDULER_POS];
  int quantum=0;


  if(strcmp(scheduler,"RR")==0){
    if(argc<RR_ARGS_VALUE){
      printUsage(argc,argv);
      exit(EXIT_FAILURE);
    }
    filename=argv[RR_FILENAME_POS];
    errno=0;
    quantum= strtol(argv[RR_QUANTUM], (char **) NULL, 10);
    if(errno==EINVAL || errno==ERANGE){
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  }
  else
    filename=argv[FILENAME_POS];
  
  errno=0;
  FILE* fp = fopen(filename,"r");
  
  if(fp==NULL){
    perror(NULL);
    exit(EXIT_FAILURE);
  }
  
  if(strcmp(scheduler,"RR")==0){
	setRoundRobinCPUQuanta(cpu,quantum);
	setSchedulingMode(cpu,RR);
  }
  if(strcmp(scheduler,"FCFS")==0)setSchedulingMode(cpu,FCFS);
  if(strcmp(scheduler,"SPN")==0) setSchedulingMode(cpu,SPN);
  if(strcmp(scheduler,"SRT")==0) setSchedulingMode(cpu,SRT);
  
  return fp;
}
