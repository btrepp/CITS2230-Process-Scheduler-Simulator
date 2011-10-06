// For the sorting algorithm
#include <algorithm> 

#define DELIMITER " "
#define TOKEN_BUFFER_SIZE 10

#include "JobList.h"

JobList* FileToJobList(FILE* file){
  
  JobList* firstelement = malloc(sizeof(JobList));
  memset(firstelement,0,sizeof(JobList));
  JobList* currentelement = firstelement;
  
  // Job counter to count how many Jobs
  int jobCounter = 0;
  
    //rewind stream;
  char* line=NULL;
  size_t len = 0;
  ssize_t read;

  if (file == NULL)
      exit(EXIT_FAILURE);

  
  while ((read = getline(&line, &len, file)) != -1) {
      printf("Retrieved line of length %zu :\n", read);
      printf("%s", line);
      
     //read space delimited values into array
      char* results = malloc(sizeof(char*)*TOKEN_BUFFER_SIZE);
      
      int i=0;
      results[i]= strtok(line,DELIMITER);
      while(results[i]!=NULL){
	i++;
	results[i]=strtok(NULL, DELIMITER);
      }
      
      //if too many values
      if(i>2){
	printf("Too many values for Job, please check data file!\n");
	exit(EXIT_FAILURE);
      }   
      
      //put into container
      JobList* thisOne = malloc(sizeof(JobList));
      memset(thisOne,0,sizeof(JobList));
      thisOne->jobName = results[0];
      thisOne->arrival_time= results[1];
      thisOne->length_time= results[2];
      
      //assign container
      currentelement->next = thisOne;
      currentelement = thisOne;
      
      jobCounter++;
      
  }
  if(read==-1)
    perror(errno);
    exit(EXIT_FAILURE);
  } 

  free(line);
  //sort JobList on arrival time!
  //TODO:
  
  currentelement->arrival_time.sort(); // sorts the jobList in terms of its arrival_time
  
  firstelement = currentelement;
  
  return firstelement;

}