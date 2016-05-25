/**
*	A command line interface for Epidemics
*
*	@author Pierre Thévenet
*
*	@version 2016-05-23
*/

#include "cli.h"
#define NBCOMMANDS 3

typedef int (*command)(int args, char** argv);

struct command_mapping {
    char const * name;
    command cmd;
};

int KMK_cmd(int args, char** argv) {
	printf("Kermack-McKendrick\n");

	size_t const NB_ARGS = 8;

	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs, *pValue;

	if (args < NB_ARGS) {
		fprintf(stderr, "Not enough arguments\n");
		return -1;
	} else if (strcmp("kmk", argv[0]) != 0) {
		fprintf(stderr, "Incorrect call\n");
		return -1;
	}

	Py_Initialize();

	PyRun_SimpleString("import sys, os");
	PyRun_SimpleString("sys.path.append('models')");

	pName = PyString_FromString("KMK");

	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule != NULL) {
		pFunc = PyObject_GetAttrString(pModule, "main");

		if (pFunc && PyCallable_Check(pFunc)) {
			pArgs = PyTuple_New(NB_ARGS - 1);

			for (int i = 1; i < NB_ARGS; ++i) {
				pValue = PyFloat_FromDouble(atof(argv[i]));
				if (!pValue) {
					Py_DECREF(pArgs);
					Py_DECREF(pModule);
					fprintf(stderr, "Error arguments\n");
					return -1;
				}
				PyTuple_SetItem(pArgs, i-1, pValue);
			}

			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL) {
				if (PyInt_AsLong(pValue) != 0) {
					printf("Call error\n");
				} else {
					printf("Call success\n");
				}
				Py_DECREF(pValue);
			}
			else {
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				PyErr_Print();
				fprintf(stderr,"Call failed\n");
				return -1;
			}
		}
		else {
			if (PyErr_Occurred())
				PyErr_Print();
			fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else {
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
		return 1;
	}

	Py_Finalize();
	return 0;
}
int RM_cmd(int args, char** argv) {
	printf("Ross-MacDonald\n");

	size_t const NB_ARGS = 12;

	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs, *pValue;

	if (args < NB_ARGS) {
		fprintf(stderr, "Not enough arguments\n");
		return -1;
	} else if (strcmp("rm", argv[0]) != 0) {
		fprintf(stderr, "Incorrect call\n");
		return -1;
	}

	Py_Initialize();

	PyRun_SimpleString("import sys, os");
	PyRun_SimpleString("sys.path.append('models')");

	pName = PyString_FromString("RM");

	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule != NULL) {
		pFunc = PyObject_GetAttrString(pModule, "main");

		if (pFunc && PyCallable_Check(pFunc)) {
			pArgs = PyTuple_New(NB_ARGS - 1);

			for (int i = 0; i < NB_ARGS; ++i) {
				pValue = PyFloat_FromDouble(atof(argv[i]));
				if (!pValue) {
					Py_DECREF(pArgs);
					Py_DECREF(pModule);
					fprintf(stderr, "Error arguments\n");
					return -1;
				}
				PyTuple_SetItem(pArgs, i-1, pValue);
			}

			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL) {
				if (PyInt_AsLong(pValue) != 0) {
					printf("Call error\n");
				} else {
					printf("Call success\n");
				}
				Py_DECREF(pValue);
			}
			else {
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				PyErr_Print();
				fprintf(stderr,"Call failed\n");
				return -1;
			}
		}
		else {
			if (PyErr_Occurred())
				PyErr_Print();
			fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}

	else {
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
		return 1;
	}

	Py_Finalize();

	return 0;
}
int help(int args, char** argv) {
    printf("epidemics [COMMAND] [ARGUMENTS]\n");
    printf("\thelp: displays this help.\n");
    printf("\tkmk <S> <I> <R> <alpha> <beta> <t> <n>: simulate model Kermack-McKendrick\n");
	printf("\t\tS,I,R : initial numbers of Susceptible, Infectious, Recovered\n");
	printf("\t\talpha, beta : Infection and Recovering rates\n");
	printf("\t\tt, n : Time, Steps\n");
	printf("\trm <Sh> <Ih> <Sv> <Iv> <a> <b1> <b2> <mu> <gamma> <t> <n>\n");
	printf("\t\tSh, Ih, Sv, Iv : initial number of healthy/infected targets (h) and non-infectious/infectious carriers (v)\n");
	printf("\t\ta : Number of infection tries per unit time per carrier (mosquito bites)\n");
	printf("\t\tb1, b2 : Ratio of bites from/to infected carriers/targets resulting in an infection for the target/carrier\n");
	printf("\t\tmu, gamma : Natural carrier mortality rate, Cure rate for targets\n");
	printf("\t\tt, n : Time duration, number of steps\n");
	return 0;
}

int main(int args, char ** argv) {

    struct command_mapping const commands[NBCOMMANDS] = {
		{"kmk",  KMK_cmd},
        {"rm", RM_cmd},
		{"help", help}
    };

	int ret = 0;

	if (args < 2) {
		ret = -1; // not enough arguments
	} else {
		args--;
		argv++;

		int flag = 0;
		for (size_t i = 0; i < NBCOMMANDS; i++) {
			if (!strcmp(argv[0], commands[i].name)) {
				flag = 1;
				ret = commands[i].cmd(args, argv);
			}
		}
		if (!flag) {
			ret = -1; // invalid command
		}
	}

	return ret;
}
// https://docs.python.org/2/extending/embedding.html
