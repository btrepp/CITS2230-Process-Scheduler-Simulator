// For the sorting algorithm
//#include <algorithm> 

#define DELIMITER " "
#define TOKEN_BUFFER_SIZE 10
#define _GNU_SOURCE

//#define DEBUG


#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "jobList.h"
#include "sort.h"
#include "debug.h"


JobElement* FileToJobList(FILE* file){
  JobElement* firstelement=NULL;// = malloc(sizeof(JobElement));
  JobElement* currentelement = firstelement;
  JobElement* endelement = NULL;
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
      
      //if too many values
      if(i>3){
	fprintf(stderr,"Too many values for Job, please check data file!\n");
	for(int j=0;j<=i;j++)
		debug_print("%d:%s\n",j,results[j]);
	exit(EXIT_FAILURE);
      }   
      debug_print("Loading Job:%s into container...\n",results[0]);
     
      //put into container
      JobElement* thisOne = malloc(sizeof(JobElement));
      	
      memset(thisOne,0,sizeof(JobElement));
      
      char* jobname = malloc(sizeof(char)*strlen(results[0]));
      strcpy(jobname,results[0]);
      thisOne->jobname= jobname;
      thisOne->arrival_time= atoi(results[1]);
      thisOne->length_time= atoi(results[2]);
     
      //assign container
	  if(jobCounter == 0){
		firstelement= thisOne;
		currentelement = thisOne;
		currentelement->next = endelement;// soo that the next element is null
		debug_print("F element: %s current element: %s\n",firstelement->jobname, currentelement->jobname);
	  }else {
		  
		  currentelement->next = thisOne; // adding new element to the list
		  currentelement = currentelement->next; // move to the new element that was added
		  currentelement->next= endelement; // next element would be null
		  debug_print("C Element: %s JC:%d\n",currentelement->jobname,jobCounter);
	  }
      jobCounter++;
      
  }
//   if(read==-1){
//     perror(NULL);
//     exit(EXIT_FAILURE);
//  } 

 // free(&line);
  //sort JobElement on arrival time!
  debug_print_string("Going into sort\n");
  //firstelement = sort(firstelement); // passing the list plus the number of jobs
    firstelement = sortshortest(firstelement);


  // sorts the jobList in terms of its arrival_time
  
  // need to figure out how to get to the first element
  //firstelement = currentelement; 
  
  return firstelement;

}
