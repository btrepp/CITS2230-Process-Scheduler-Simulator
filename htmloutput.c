#include "htmloutput.h"

void scriptJS(FILE* out);

void header(FILE* out){
	fprintf(out, "<html><head><title>Memory Output</title>\n");
	fprintf(out, "<script \"text/javascript\">\n");
	scriptJS(out);
}

void scriptJS(FILE* out){
	fprintf(out, "function memElement( jobname){\n"
		"   return { \n"
		"      jobname:jobname\n"
		"   }\n"
		"}\n");
	fprintf(out,"var all = [];\n");

	fprintf(out, "function printClock(clock){\n"
//		"   document.getElementsByTagName('BODY')[0].innerHTML = '';\n"
		"   document.write(\"<p>\" + clock + \"</p>\");\n"
		"   document.write(\"<form>\"); \n"
		"   alert('<input type=\"button\" value=\"Next Clock!\" onclick=\" printClock(0);\" />');\n"
		"   document.write('<input type=\"button\" value=\"Next Clock!\" onclick=\" printClock('+clock+1')\" />');\n"
		"   document.write(\" </form>\");\n"
		"   for( elem in all[clock]) { \n"
		"   document.write(\"<p>\" + elem.jobname + \"</p>\");"
		"   }\n"
		"}\n");
	
}

void footer(FILE* out){
	fprintf(out, "document.write(\"<p>\" + Date() + \"</p>\");");

	fprintf(out, "printClock(0);");


	fprintf(out, "</script>\n");
	fprintf(out, "<body>\n");
	fprintf(out,"</body></html>\n");
}

void memToJavascriptArray(FILE* out, Memory* mem){
	fprintf(out,"var memspace = [];\n");
	for(int i=0;i<mem->number_of_pages; i++){
		if(mem->pages[i]->job!=NULL)
			fprintf(out, "memspace.push(memElement(\"%s\"));\n", mem->pages[i]->job->jobname);
		else
			fprintf(out, "memspace.push(memElement(null));\n");
	}
	fprintf(out, "all.push(memspace);\n");
}

