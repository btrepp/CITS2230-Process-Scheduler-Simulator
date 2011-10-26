#include "jobScheduler.h"
#include "jobList.h"
#include "sort.h"

#define DEBUG
#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

LIST(JobSchedule);


void insertScheduleElement(JobScheduleContainer* list, JobSchedule* jobsch){
	if(list->tail==NULL)
 	       list->head=jobsch;
 	 else
        	list->tail->next=jobsch;
	 list->tail=jobsch;
}

