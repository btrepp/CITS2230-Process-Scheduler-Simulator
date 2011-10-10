void runSchedules(JobList* list){
    Job currentelement==list;

  //list must be sorted on arrival time

    //setupscheduler RR, FCFS etc
    int thisclock=0;
    while((currentelement=currentelement->next!=NULL)){
	  while(currentelement!=NULL && currentelement->arrival_time==thisclock){
	      addJob(currentelement);
	      currentelement=currentelement->next;
	      //free the old one here
	  }
	  thisclock==incrementClock();
    }
    while(!no_more_jobs)
	incrementClock();

    printResults();
}