// HZ Engine Source
// Copyright (C) 1998 by David W. Jeske


#ifndef DONUTS_H
#define DONUTS_H

#include "sprite.h"

#define DEF_SHOW_DELAY     (2000)

#define IS_NUM(c)     ((c) >= '0' && (c) <= '9')
#define IS_SPACE(c)   ((c) == ' ' || (c) == '\r' || (c) == '\n' || (c) == '\t' || (c) == 'x')




// program states
enum
{
    PS_SPLASH,
    PS_ACTIVE,
    PS_BEGINREST,
    PS_REST
};

#define MAX_MAP_X  2000
#define MAX_MAP_Y  2000

#define     MAX_SCREEN_X    (ScreenX-1)
#define     MAX_SCREEN_Y    (ScreenY-1)
#define     MAX_DONUT_X     MAX_MAP_X - 64
#define     MAX_DONUT_Y     MAX_MAP_Y - 64
#define     MAX_DONUT_FRAME 30
#define     MAX_PYRAMID_X     MAX_MAP_X - 32
#define     MAX_PYRAMID_Y     MAX_MAP_Y - 32
#define     MAX_PYRAMID_FRAME 40
#define     MAX_SPHERE_X     MAX_MAP_X - 16
#define     MAX_SPHERE_Y     MAX_MAP_Y - 16
#define     MAX_SPHERE_FRAME 40
#define     MAX_CUBE_X     MAX_MAP_X - 16
#define     MAX_CUBE_Y     MAX_MAP_Y - 16
#define     MAX_CUBE_FRAME 40
#define     MAX_SHIP_X     MAX_MAP_X - 32
#define     MAX_SHIP_Y     MAX_MAP_Y - 32
#define     MAX_SHIP_FRAME 40
#define     MAX_BULLET_X    MAX_MAP_X - 3;
#define     MAX_BULLET_Y    MAX_MAP_Y - 3;
#define     MAX_BULLET_FRAME 400


// Offsets for the bullet bitmap
#define     BULLET_X    304
#define     BULLET_Y    0

/*
 * fn prototypes
 */

void    UpdateFrame( void );
void    UpdateDisplayList( void );
void    DrawDisplayList( void );
void	paintScreen(void);
void    DestroyGame( void );


// extern LPDIRECTDRAWPALETTE     lpSplashPalette;

extern BOOL                    bSoundEnabled;
extern BOOL                    bPlayIdle;
extern BOOL                    bPlayBuzz;
extern BOOL                    bPlayRev;
extern DWORD                   lastInput;
extern BOOL                    lastThrust;
extern BOOL                    lastShield;
extern int                     showDelay;
extern HWND                    hWndMain;
extern BOOL                    bShowFrameCount;
extern BOOL                    bIsActive;
extern BOOL                    bMouseVisible;
extern DWORD                   dwFrameCount;
extern DWORD                   dwFrameTime;
extern DWORD                   dwFrames;
extern DWORD                   dwFramesLast;
extern BOOL                    bUseEmulation;
extern BOOL                    bTest;
extern BOOL                    bStress;
extern RGBQUAD                 SPalette[256];
extern DWORD                   lastTickCount;
extern int                     score;
extern int                     ProgramState;
extern int                     level;
extern int                     restCount;
extern DWORD                   dwFillColor;
extern BOOL                    bSpecialEffects;
extern DWORD                   ShowLevelCount;
extern DWORD                   ScreenX;
extern DWORD                   ScreenY;
extern DWORD                   ScreenBpp;
extern BOOL                    bWantSound;  //global hack to turn off sound


#endif /* DONUTS_H */
