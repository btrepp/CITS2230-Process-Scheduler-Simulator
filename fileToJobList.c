// For the sorting algorithm
//#include <algorithm> 

#define DELIMITER " "
#define TOKEN_BUFFER_SIZE 10
#define _GNU_SOURCE

#define DEBUG


#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "job.h"
#include "sort.h"
#include "debug.h"

#include "fileToJobList.h"


list_Job* FileToJobList(FILE* file){
 
  list_Job* list = malloc(sizeof(*list));

  // Job counter to count how many Jobs
  int jobCounter = 0;
  
    //rewind stream;
  char* line=NULL;
  size_t len = 0;
  ssize_t read;

  if (file == NULL)
      exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, file)) != -1) {
      debug_print("Retrieved line of length %zu :\n", read);
      debug_print("Value of line :%s\n", strtok(line, "\n"));
      
     //read space delimited values into array
      char* results[TOKEN_BUFFER_SIZE];
      
      int i=0;
      results[i]= strtok(line,DELIMITER);
      while(results[i]!=NULL){
	i++;
	results[i]=strtok(NULL, DELIMITER);
      }
      
      //if too many values or too few
      if(i>4 || i<3){
	fprintf(stderr,"Too %s values for Job, please check data file!\n",(i>4 ? "Many":"Few"));
	for(int j=0;j<=i;j++)
		debug_print("%d:%s\n",j,results[j]);
	exit(EXIT_FAILURE);
      }
   
      debug_print("Loading Job:%s into container...\n",results[0]);
     
      //put into container
      Job* newJob = malloc(sizeof(*newJob));
      memset(newJob,0,sizeof(*newJob));
      
      char* jobname = malloc(sizeof(char)*strlen(results[0]));
      strcpy(jobname,results[0]);
      newJob->jobname= jobname;
      newJob->arrival_time= atoi(results[1]);
      newJob->length_time= atoi(results[2]);
	
       if(i==4)
		newJob->pages = atoi(results[3]);
       else
		newJob->pages =-1; 

      list_Job_append(list,newJob);
      jobCounter++;
      
  }

  return list; //firstelement;

}
