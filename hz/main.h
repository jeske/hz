// HZ Engine Source
// Copyright (C) 1998 by David W. Jeske

// Main.h
//
// The main header, includes global stuff which is important...

#ifndef MAIN_H
#define MAIN_H

#include "view.h"
#include "vconsole.h"

extern MultiView *mainTabView; 
extern ConsoleView *consoleView; 
extern View *realScreenView;

void initViews(void);

// {076C1FC9-B287-11d0-A8E3-00AA00A747E5}
// DEFINE_GUID(HZ_GUID, 0x76c1fc9, 0xb287, 0x11d0, 0xa8, 0xe3, 0x0, 0xaa, 0x0, 0xa7, 0x47, 0xe5);


#endif /* MAIN_H */
