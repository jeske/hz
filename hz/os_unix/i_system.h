// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

//
// i_system.h
//
#ifndef HZ_I_SYSTEM_H
#define HZ_I_SYSTEM_H

#include "i_console.h"

// i_time_ms(void)
// this should return the system time in milliseconds, in other words, it
// should be an incrementing counter which increments one every millisecond.
// 
unsigned long int i_time_ms(void); 


int CleanupAndExit( char *err);
void i_convert_path (char *path);

#endif
