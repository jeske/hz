// HZ Engine Source
// Copyright (C) 1998 David W. Jeske


// Misc.cpp
//

#ifdef OS_WIN
#include <io.h>
#endif

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#include "view.h"
#include "main.h" // consoleView

#include "misc.h"


int randInt( int low, int high )
{
    int range = high - low;
    int num = rand() % range;
    return( num + low );
}

double randDouble( double low, double high )
{
    double range = high - low;
    double num = range * (double)rand()/(double)RAND_MAX;
    return( num + low );
}


// to pipe stdio back into us...
int real_stdio = 1;
int real_stderr = 2;
int input_pipe_fd = -1;
int should_die = 0;
#ifdef OS_WIN
HANDLE input_pipe = NULL;
#endif



extern "C" {

	void dolua_print(char *str) {
		printf("(LUA) %s\n",str);
	}

	void dolua_erprint(char *erstring) {
		printf("(LuaERR) %s\n",erstring);
	}

}




