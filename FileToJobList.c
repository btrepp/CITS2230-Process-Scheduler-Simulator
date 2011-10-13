// For the sorting algorithm
//#include <algorithm> 

#define DELIMITER " "
#define TOKEN_BUFFER_SIZE 10
#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "JobList.h"

JobElement* FileToJobList(FILE* file){
  JobElement* firstelement=NULL;// = malloc(sizeof(JobElement));
  
  //memset(firstelement,0,sizeof(JobElement));
  
  JobElement* currentelement = firstelement;
//  JobElement* firstTempelement = firstelement;
  
  // Job counter to count how many Jobs
  int jobCounter = 0;
  
    //rewind stream;
  char* line=NULL;
  size_t len = 0;
  ssize_t read;

  if (file == NULL)
      exit(EXIT_FAILURE);

  
  while ((read = getline(&line, &len, file)) != -1) {
      //printf("Retrieved line of length %zu :\n", read);
      //printf("%s", line);
      
     //read space delimited values into array
      char* results[TOKEN_BUFFER_SIZE];
      
      int i=0;
      results[i]= strtok(line,DELIMITER);
      while(results[i]!=NULL){
	i++;
	results[i]=strtok(NULL, DELIMITER);
      }
      
      //if too many values
      if(i>3){
	printf("Too many values for Job, please check data file!\n");
	for(int j=0;j<=i;j++)
		printf("%d:%s\n",j,results[j]);
	exit(EXIT_FAILURE);
      }   
     
 
      printf("Loading Job:%s into container\n",results[0]);
     
	 //put into container
      JobElement* thisOne = malloc(sizeof(JobElement));
      	
      memset(thisOne,0,sizeof(JobElement));
      
      char* jobname = malloc(sizeof(char)*strlen(results[0]));
      strcpy(jobname,results[0]);
      thisOne->jobname= jobname;
      thisOne->arrival_time= atoi(results[1]);
      thisOne->length_time= atoi(results[2]);
      if(firstelement!=NULL)
	printf("%s\n",firstelement->jobname);
     
      //assign container
	  if(jobCounter == 0){
		firstelement= thisOne;
		currentelement = thisOne;
	  }else {
	printf("%s\n%d\n",currentelement->jobname,jobCounter);
		  currentelement->next=thisOne;
		  currentelement=thisOne;
	  }
      jobCounter++;
      
  }
  if(read==-1){
    perror(NULL);
    exit(EXIT_FAILURE);
  } 

  free(line);
  //sort JobElement on arrival time!
  //Sort(firstTempelement, jobCounter); // passing the list plus the number of jobs
 
  // sorts the jobList in terms of its arrival_time
  
  // need to figure out how to get to the first element
  //firstelement = currentelement; 
  
  return firstelement;

}
