// HZ Engine Source
// Copyright (C) 1998 by David W. Jeske


#ifndef DONUTS_H
#define DONUTS_H

#include "sprite.h"

#define DEF_SHOW_DELAY     (2000)

#define MAX_MAP_X  2000
#define MAX_MAP_Y  2000
#define     MAX_DONUT_X     MAX_MAP_X - 64
#define     MAX_DONUT_Y     MAX_MAP_Y - 64


// extern LPDIRECTDRAWPALETTE     lpSplashPalette;
extern BOOL                    bPlayIdle;
extern BOOL                    bPlayBuzz;
extern BOOL                    bPlayRev;
extern DWORD                   lastInput;
extern BOOL                    lastThrust;
extern BOOL                    lastShield;
extern int                     showDelay;
extern BOOL                    bShowFrameCount;
extern BOOL                    bUseEmulation;
extern BOOL                    bTest;
extern BOOL                    bStress;
extern RGBQUAD                 SPalette[256];
extern int                     score;
extern int                     level;

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



#endif /* DONUTS_H */
