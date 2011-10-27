#include <stdlib.h>
#include "virtualCPU.h"

typedef struct Settings{
	FILE* jobinput;
	FILE* memoutput;
	FILE* htmloutput;

	bool mem_management;	
	schedule_mode mode;
	int rr_quanta;
	int mem_quanta;

} Settings;



Settings* setup(int argc, char *argv[]);
