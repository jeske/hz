// HZ Engine Source
// Copyright (C) 1998 by David W. Jeske

// Main.h
//
// The main header, includes global stuff which is important...

#ifndef MAIN_H
#define MAIN_H

#include "view.h"
#include "vconsole.h"

// program states
enum
{
    PS_SPLASH,
    PS_ACTIVE,
    PS_BEGINREST,
    PS_REST
};

#define IS_NUM(c)     ((c) >= '0' && (c) <= '9')
#define IS_SPACE(c)   ((c) == ' ' || (c) == '\r' || (c) == '\n' || (c) == '\t' || (c) == 'x')

extern MultiView *mainTabView; 
extern ConsoleView *consoleView; 
extern View *realScreenView;

void    initViews( void );
void    UpdateFrame( void );
void    UpdateDisplayList( void );
void    DrawDisplayList( void );
void	paintScreen( void);
void    DestroyGame( void );

#endif /* MAIN_H */
