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
extern View *gameScreenPane;

void    initViews( void );
void    UpdateFrame( void );
void    UpdateDisplayList( void );
void    DrawDisplayList( void );
void	paintScreen( void);
void    DestroyGame( void );

#define DEF_SHOW_DELAY     (2000)

#define MAX_MAP_X  2000
#define MAX_MAP_Y  2000
#define     MAX_DONUT_X     MAX_MAP_X - 64
#define     MAX_DONUT_Y     MAX_MAP_Y - 64

extern BOOL                    bShowFrameCount;
extern BOOL                    bSoundEnabled;
extern BOOL                    bIsActive;
extern BOOL                    bMouseVisible;
extern DWORD                   dwFrameCount;
extern DWORD                   dwFrameTime;
extern DWORD                   dwFrames;
extern DWORD                   dwFramesLast;
extern DWORD                   lastTickCount;
extern int                     ProgramState;
extern int                     restCount;

extern BOOL                    bWantSound;  //global hack to turn off sound

extern DWORD                   ScreenX;
extern DWORD                   ScreenY;
extern DWORD                   ScreenBpp;

#endif /* MAIN_H */
