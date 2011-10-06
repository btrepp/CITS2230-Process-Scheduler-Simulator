int current_clock=0;

list unscheduled_jobs;
list schedule_results;

job active_job==null;
int active_job_scheduled_at;
schedule_mode mode=0;

int k=0;

void setSchedulingMode(enum stuff){
  mode=stuff;
}

void addJob(JobListElement* job){
  if(current_clock!=job->arrival_time){
     perror("Incorrect Arrival Time!");
      exit(EXIT_FAILURE);
  }
  unscheduled_jobs->add(job);
}

void sort_time_length(JobListElement* joblist) {
 jobList->length_time.sort(); //sorts the joblist in terms of time_length
}

int incrementClock(){
  if(active_job_scheduled_at+active_job.time_length > current_clock){
      active_job==null;
      free(active_job);
  }
  
  switch(mode){
    case: FCFS
	firstComeFirstServe();
	break;
	
    case: RR
      roundrobin();
      break;
      
    case: SPN
      shortprocessnext();
      break;
      
    case:SRT
      shortremainingtime();
      break;
      
  return current_clock++;
}

bool no_more_jobs(){
  if(unscheduled_jobs->next==null && active_job!=null){
    return true;
  }
}

void firstComeFirstServe(){
    if(active_job!=null)
      return;
 
    //sort(unscheduled_jobs); // it should be sorted already due to FCFS!.
      
    active_job==dequeue(unscheduled_jobs); 
    active_job_scheduled_at=current_clock;
    schedule_results->next(active_job);
    
}

void roundrobin(){
    if(k<1){
	perror("Quanta can't be less than 1");
	exit(EXIT_FAILURE);
    }
  
    if(active_job!=null)
      return;
    
    Job* temp==dequeue(unscheduled_jobs);
    Job* remainingquantjob==NULL;
    active_job==malloc(sizeof(JobListElement));
    
    memcpy(temp,active_job,i cant remember args);
    active_job->length_time=k;
    
    if(temp->length_time>k){
      memcpy(temp,remainingquantjob,sizeof(JobListElement));
      remainingquantjob->length_time= temp->length_time-k;
      unscheduled_jobs->add(remainingquantjob);
    }
      
    schedule_results->next(active_job);
    
}

void shortprocessnext(){
   if(active_job!=null)
      return;
   
   sort_time_length(JobList);
   firstComeFirstServe();
}

void shortremainingtime(){
   if(active_job!=null){
      perror("Active Job should always be null in SRT!");
      exit(EXIT_FAILURE);
   }
   
   sort_time_length(JobList);
   
    Job* temp==dequeue(unscheduled_jobs);
    Job* remainingquantjob==NULL;
    active_job==malloc(sizeof(JobListElement));
    memcpy(temp,active_job,sizeof(JobListElement));
    active_job->length_time=1;
    
    
    if(temp->length_time>1){
      memcpy(temp,remainingquantjob,sizeof(JobListElement));
      remainingquantjob->length_time= temp->length_time-1;
      unscheduled_jobs->add(remainingquantjob);
    }
   
   schedule_results->next(active_job);
}
   