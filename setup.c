
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>

#include "setup.h"
#include "virtualCPU.h"
// Printout of how to use the program properly
void printUsage(int argc, char*argv[]){
  printf("usage:\n %s [sv] Scheduler {Quantum} Input File {Memory Quantum} \n"
	" [-f] memoryoutputfile [-h] htmloutputfile", argv[0]);
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
  printf("\t -f filename : File to print the memory usage to (defaults to vout.file) \n");
  printf("\n\t [BONUS] -h filename : Writes a HTML memory visualization out to filename \n");
  printf("\n");
}

Settings* setup(int argc, char *argv[]){
 
  if(argc<3){
    printUsage(argc,argv);
    exit(EXIT_FAILURE);
  }

  int c;
  char* memfilename="vout.file";
  char* htmlfilename = "";
  bool mem_management=false; 
while ((c = getopt (argc, argv, "svfh:")) != -1)
         switch (c){
           case 's':
             mem_management=false;
             break;
           case 'v':
	     mem_management=true;
             break;
	   case 'f':
		memfilename=optarg;
		break;
	   case 'h':
		htmlfilename=optarg;
		break;
           case '?':
             if (optopt == 'f')
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
#define MEM_QUANTA 2+optind
  
  char* filename = "";
  char* scheduler = argv[SCHEDULER_POS];
  int quantum=0;
  int mem_quanta=-1;

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
  else{
    filename=argv[FILENAME_POS];
  }

  if(mem_management==true){
	if(strcmp(scheduler,"RR")==0 && argc==RR_ARGS_VALUE+1)
    		mem_quanta= strtol(argv[MEM_QUANTA+1], (char **) NULL, 10);
  	else if(argc == RR_ARGS_VALUE)
    		mem_quanta= strtol(argv[MEM_QUANTA], (char **) NULL, 10);
	else{
	     printUsage(argc,argv);
	     exit(EXIT_FAILURE);  
	}
  }
  errno=0;
  FILE* fp = fopen(filename,"r"); 

 
  if(fp==NULL){
    perror(NULL);
    exit(EXIT_FAILURE);
  }
  
   FILE* memout =NULL;
   FILE* htmlout = NULL;
  if(mem_management){
	memout = fopen(memfilename,"w");

	if(strlen(htmlfilename)>0){
		htmlout = fopen(htmlfilename,"w");
	}
  }

  Settings* returnpair = malloc(sizeof(*returnpair));
  returnpair->jobinput = fp;
  returnpair->memoutput = memout;
  returnpair->htmloutput = htmlout;
  returnpair->mem_management = mem_management;
  returnpair->mem_quanta = mem_quanta;


   if(strcmp(scheduler,"RR")==0){
	returnpair->mode=RR;
	returnpair->rr_quanta = quantum;
  }
  if(strcmp(scheduler,"FCFS")==0)returnpair->mode=FCFS;
  if(strcmp(scheduler,"SPN")==0) returnpair->mode=SPN;
  if(strcmp(scheduler,"SRT")==0) returnpair->mode=SRT;
 
  

  return returnpair;
}
