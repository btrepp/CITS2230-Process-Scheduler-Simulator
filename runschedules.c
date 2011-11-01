void runSchedules(JobList* list){
    Job currentelement==list;
  //list must be sorted on arrival time before running in CPU
    int thisclock=0;
    while((currentelement=currentelement->next!=NULL)){
	  while(currentelement!=NULL && currentelement->arrival_time==thisclock){
	      addJob(currentelement);
	      currentelement=currentelement->next;
	      // update to next Job
	  }
	  thisclock==incrementClock();
    }
    while(!no_more_jobs)
	incrementClock();

    printResults();
}
