// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

//
// i_console.h
// unix specific console code
//

#ifndef _I_CONSOLE_H_
#define _I_CONSOLE_H_ 1

#include <stdio.h>
#include <stdarg.h>

int I_Error (char *fmt, ...);
int I_Perror (char *fmt, ...);
int I_Message (char *fmt, ...);

#endif /* _I_CONSOLE_H_ */
