#include "htmloutput.h"

void header(FILE* out){
	fprintf(out, "function memElement( jobname){\n"
		"   return { \n"
		"      jobname:jobname\n"
		"   }\n"
		"}\n");
	fprintf(out,"var all = [];\n");
}

void footer(FILE* outstream){

}

void memToJavascriptArray(FILE* out, Memory* mem){
	fprintf(out,"var memspace = [];\n");
	for(int i=0;i<mem->number_of_pages; i++){
		fprintf(out, "memspace.push(memElement(%s));\n", mem->pages[i]->jobname);
	}
	fprintf(out, "all.push(memspace);\n");
}

