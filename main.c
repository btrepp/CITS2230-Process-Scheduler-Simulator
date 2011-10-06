#include <stdio.h>
//#include "JobList.c"
#include "JobList.h"
//#include "runschedules.c"
//#include "Pscheduler.c"
//#include "printResults.c"
//#include "JobScheduler.c"
//#include "FileToJobList.c"

int main(int argc, char* argv[]) {
	FILE* pFile;
	pFile = fopen("Jobs.txt", "r");
	JobList* FileToJobList(FILE* pFile);
	printf(" [%s] \n", FileToJobList.jobname);
}
