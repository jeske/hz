// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

//
// i_system.h
//
#ifndef HZ_I_SYSTEM_H
#define HZ_I_SYSTEM_H


// i_time_ms(void)
// this should return the system time in milliseconds, in other words, it
// should be an incrementing counter which increments one every millisecond.
// 
unsigned long int i_time_ms(void); 
const char *i_fix_path(const char *path);

int CleanupAndExit( char *err);

// {076C1FC9-B287-11d0-A8E3-00AA00A747E5}
// DEFINE_GUID(HZ_GUID, 0x76c1fc9, 0xb287, 0x11d0, 0xa8, 0xe3, 0x0, 0xaa, 0x0, 0xa7, 0x47, 0xe5);


#endif
