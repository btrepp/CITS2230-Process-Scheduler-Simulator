#include "htmloutput.h"

void scriptJSHeader(FILE* out);

void header(FILE* out){
	if(out==NULL) return ;
	fprintf(out, "<html><head><title>Memory Output</title>\n");
	fprintf(out, "<script type=\"text/javascript\" \n "
		     "src=\"http://ajax.googleapis.com/ajax/libs/jquery/1.3/jquery.min.js\">\n"
		     "</script>\n");
	fprintf(out, "<style type=\"text/css\">\n"
		     "    #buttons {float:right; margin-right:200px;}\n"
		     "    #info {float:left;}\n"
		     "    .stat {float:left; margin:10px;}\n"
		     "    #content {clear:both;}\n"
		     "</style>\n");

	fprintf(out, "<script type=\"text/javascript\">\n");
	scriptJSHeader(out);
}

void scriptJSHeader(FILE* out){
	fprintf(out, "function memElement( jobname){\n"
	"   if($(\"style:contains('.\" + jobname + \"')\").length < 1){ \n"
   		"       $(\"<style type='text/css'>.\"+jobname+\"{\" +  \n"
        	"       \"background-color:\"+Math.round(0xffffff * Math.random()).toString(16)+\";\"+ \n"
        	"       \"float:left;\"+ \n"
        	"       \"width:60px; } </style>\").appendTo(\"head\"); \n"
   		"   }\n"
	"   return { \n"
		"      jobname:jobname\n"
		"   }\n"
		"}\n");

	fprintf(out, "function job (name, time){\n"
		"     return {\n"
  		"               jobname:name,\n"
		"               finishes_at:time\n"
		"	}\n"
		"}\n");

	fprintf(out,"var all = [];\n");
	fprintf(out,"var process= [];\n");
	fprintf(out,"var clock =0;\n");
	
}


void scriptJSFooter(FILE* out){
	if(out==NULL) return ;
	fprintf(out, "<script type=\"text/javascript\"> \n ");
	fprintf(out, "$('#increment').click(function (e) { \n"
       		     "      e.preventDefault(); \n"
        	     "      clock++; \n"
    		     "      if(clock > all.length -1){ clock = all.length-1}; \n"
		     "      printClock(); \n"
		     "}); \n");
	fprintf(out, "$('#decrement').click(function (e) { \n"
       		     "      e.preventDefault(); \n"
        	     "      clock--; \n"
    		     "      if(clock < 0){ clock = 0}; \n"
    		     "      printClock(); \n"
		     "}); \n");

	fprintf(out, "function printClock(){\n"
		"   $('#content').empty();\n "
		"   $('#clockcount').html(clock); \n"
		"   $('#jobname').html(process[clock].jobname);\n"
		"   $('#timerem').html(process[clock].finishes_at);\n"
		"   jQuery.each(all[clock], function(i, val) {\n"
		"         $('#content').append(\"<div>\");\n"
		"         $('#content').append(\"<div class=\"+val.jobname+\">\" +val.jobname+\"</div>\");\n"
		"         $('#content').append(\"</div>\");\n"
		"   });\n"
		"}\n");


	fprintf(out, " printClock(); \n");
	fprintf(out, "</script> \n ");
	
}

void footer(FILE* out){
	if(out==NULL) return ;
	fprintf(out, "</script>\n");
	fprintf(out, "<body>\n");
	fprintf(out, "<div id=\"buttons\">\n");
	fprintf(out, "<input type=\"button\" value=\"Previous\" id=\"decrement\"/>\n");	
	fprintf(out, "<input type=\"button\" value=\"Next\" id=\"increment\"/>\n");
	fprintf(out, "</div>\n");
	fprintf(out, "<div class=\"stat\">Clock</div><div class=\"stat\" id=\"clockcount\"></div>\n");
	fprintf(out, "<div class=\"stat\">Process</div><div class=\"stat\" id=\"jobname\"></div>\n");
	fprintf(out, "<div class=\"stat\">Schedule Finish</div><div class=\"stat\" id=\"timerem\"></div>\n");
	fprintf(out, "</div>\n");
	fprintf(out, "<div id=\"content\"></div>\n");
	scriptJSFooter(out);
	fprintf(out,"</body></html>\n");
}

void memToJavascriptArray(FILE* out, VirtualCPU* cpu){
	Memory* mem = cpu->physical_memory;
	//return;
	if(out==NULL) return ;
	fprintf(out,"var memspace = [];\n");
	
	if(cpu->active_job!=NULL)
		fprintf(out,"process.push(job(\"%s\",\"%d\"));\n",
			cpu->active_job->job->jobname, 
			cpu->active_job->start_time+cpu->active_job->running_time-1);
	else 
		fprintf(out,"process.push(job(\"idle\",\"-1\"));");

	for(int i=0;i<mem->number_of_pages; i++){
		if(mem->pages[i]->job!=NULL)
			fprintf(out, "memspace.push(memElement(\"%s\"));\n", mem->pages[i]->job->jobname);
		else
			fprintf(out, "memspace.push(memElement(null));\n");
	}
	fprintf(out, "all.push(memspace);\n");
}

