/**
*	A command line interface for Epidemics
*
*	@author Pierre Thévenet
*
*	@version 2016-05-23
*/

#include "cli.h"

int main(int argc, char ** argv) {
	FILE* file;

    int Pargc;
    char * Pargv[1];

    Pargc = 1;
	Pargv[0] = "MME.py";

    Py_SetProgramName(argv[0]);
    Py_Initialize();
    PySys_SetArgv(Pargc, Pargv);
    file = fopen(Pargv[0],"r");
    PyRun_SimpleFile(file, Pargv[0]);
    Py_Finalize();

	return 0;
}
// https://docs.python.org/2/extending/embedding.html
