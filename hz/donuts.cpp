// Donuts.cpp
//
// Originally part of SpaceDonuts demo, but I've hacked it over and it's almost
// gone... :)
//



#include <stdio.h>
#include <stdlib.h>
#include "osdep.h"
#ifdef OS_WIN
#include <io.h>
#include "resource.h"
#include "DrawHndl.h"
#endif
#include "i_draw.h"
#include "i_video.h"
#include "i_system.h" // for i_time_ms()

#include "main.h"
#include "donuts.h"
#include "view.h"
#include "sprite.h"
#include "spritet.h"
#include "misc.h"
#include "game.h"
#include "map.h"
#include "net.h"

// START ORIGINAL DONUTS STUFF!!!


void UpdateFrame( void )
{
//  I_Message ("UpdateFrame\n");
    switch( ProgramState )
    {
        case PS_SPLASH:
            // display the splash screen
			dbgMsg(c_excessive,"UpdateFrame: PS_SPLASH\n");
            bltSplash();
            return;
        case PS_ACTIVE:
			dbgMsg(c_excessive,"UpdateFrame: PS_ACTIVE\n");
			UpdateDisplayList();
            DrawDisplayList();
            return;
        case PS_BEGINREST:
			dbgMsg(c_excessive,"UpdateFrame: PS_BEGINREST\n");
#ifdef USE_DSOUND
            if(bWantSound)
            {
                SndObjPlay(hsoBeginLevel, 0);
            }
#endif
            ProgramState = PS_REST;
            //
            // FALLTHRU
            //
        case PS_REST:
			dbgMsg(c_excessive,"UpdateFrame: PS_REST\n");
			
            if( ( i_time_ms() - restCount ) > ShowLevelCount )
            {
#ifdef USE_DSOUND
                if(bWantSound)
                {
                    SndObjPlay(hsoEngineIdle, DSBPLAY_LOOPING);
                }
#endif
                bPlayIdle = TRUE;
                lastTickCount = i_time_ms();
                ProgramState = PS_ACTIVE;
		I_SetWindowText("HZ -- [running]");
            }
            return;
    }
}


LPDIRECTDRAWPALETTE     lpSplashPalette;
BOOL                    bSoundEnabled = FALSE;
BOOL                    bPlayIdle = FALSE;
BOOL                    bPlayBuzz = FALSE;
BOOL                    bPlayRev = FALSE;
DWORD                   lastInput = 0;
BOOL                    lastThrust = FALSE;
BOOL                    lastShield = FALSE;
int                     showDelay = 0;
HWND                    hWndMain;
BOOL                    bShowFrameCount=TRUE;
BOOL                    bIsActive;
BOOL                    bMouseVisible = TRUE;
DWORD                   dwFrameCount;
DWORD                   dwFrameTime;
DWORD                   dwFrames;
DWORD                   dwFramesLast;
BOOL                    bUseEmulation;
BOOL                    bTest=FALSE;
BOOL                    bStress=FALSE;
RGBQUAD                 SPalette[256];
DWORD                   lastTickCount = 0;
int                     score;
int                     ProgramState;
int                     level;
int                     restCount;
DWORD                   dwFillColor;
BOOL                    bSpecialEffects = FALSE;
DWORD                   ShowLevelCount = 100;
DWORD                   ScreenX;
DWORD                   ScreenY;
DWORD                   ScreenBpp;
BOOL                    bWantSound = TRUE;  //global hack to turn off sound



#ifdef DEBUG
char                    DebugBuf[256];
BOOL                    bHELBlt = FALSE;
#endif

void DrawDisplayList( void )
{   
	static int already_drawing = 0;

	if (already_drawing) {
		return;
	}

	already_drawing = 1;

	EraseScreen();
	paintScreen(); // C passthrough to C++ View classes in main.cpp
	// we should sleep here to lock the framerate
	FlipScreen();

	already_drawing = 0;
}




int g_num_donuts = 0;
int button_down = 0;

void UpdateDisplayList( void )
{
    unsigned long int       thisTickCount = i_time_ms();
    unsigned long int       tickDiff;

	if (lastTickCount == 0) {
		lastTickCount = thisTickCount - 10;
	}

    if (thisTickCount >= lastTickCount) {
       tickDiff = thisTickCount - lastTickCount;
    } else {
		printf("WRAPOVER! lastTick(%lu), thisTick(%lu), delta(%lu)\n",
				lastTickCount,	thisTickCount, tickDiff);
		
		tickDiff = lastTickCount - thisTickCount;
    }


//    I_Message("lastTick(%lu), thisTick(%lu), delta(%lu)\n",lastTickCount,
//	  thisTickCount, tickDiff);

	lastTickCount = thisTickCount;

	// do Object motion

	tick_server(tickDiff);
    defaultSpriteList->doAITick(tickDiff);
	mainViewPort->doFollowTick(tickDiff); // so it can follow the "main sprite"
   
}


