#include <stdio.h>
//#include "JobList.c"
#include "jobList.h"
//#include "runschedules.c"
//#include "Pscheduler.c"
//#include "printResults.c"
//#include "JobScheduler.c"
//#include "FileToJobList.c"

int main(int argc, char* argv[]) {
  int i = 0;
	FILE* pFile;
	pFile = fopen("Jobs.txt", "r");
	JobElement* list= FileToJobList(pFile);

	//while(list!=NULL){
	  while(i < 4) {
		printf("%s\n",list->jobname);
		list=list->next;
		i++;
	}
	printf("Complete!\n");

	//printf(" [%s] \n", FileToJobList);
	return 0;


}
