// HZ Engine Source
// Copyright (C) 1998 David W. Jeske


/*
 * main.cpp
 *
 * Soon this should require no more windows stuff, and eventually I hope
 * this file will disappear altogether, see "os_win\main.cpp" for the real
 * WinMain() function.
 */

#include <stdio.h>
#include <stdlib.h>


#if defined(OS_WIN)
#include <io.h>
#include "resource.h"
#include "DrawHndl.h"
#include "hndlmgr.h" // manages GDI handles to make sure they get destroyed
#endif

#ifdef OS_UNIX
#include "i_console.h"
#endif

#include "i_system.h" // for i_time_ms()
#include "i_video.h"
#include "i_draw.h" 
#include "donuts.h"
#include "view.h"
#include "vconsole.h"
#include "map.h"
#include "concmd.h"
#include "main.h"
#include "game.h"  // setup_game()
#include "net.h"   // tick_server()


View *gameScreenPane = NULL;
View *realScreenView = NULL;
View *productionPane = NULL;
View *consolePane = NULL;
View *startupView = NULL;
MultiView *mainTabView = NULL;
MultiView *multiView = NULL;
int testinc = 0;
int testflash = 0;
int testbarinc = 0;

HorizStatusBar *status_bar;
HorizStatusBar *status_bar2;
HorizStatusBar *loadingBar;

ConsoleView *consoleView;
int barvector = -1;

void paintScreen() {
	if (realScreenView) {
		if (testbarinc++ >= 3) {
			testbarinc = 0;
			if (status_bar && status_bar2) {
				if (status_bar2->getValue() == 0) {
					barvector = 1;
				} else {
					if (status_bar2->getValue() >= status_bar2->getMaxValue()) {
						barvector = -1;
					} 
				}
			
			
				status_bar2->setValue(status_bar2->getValue()+barvector);
				status_bar->setValue(status_bar->getValue()+barvector);	
			}
			
		}
		if (loadingBar) {
			loadingBar->setValue(g_images_loaded);
		}


		if (testinc++ >= 20 && multiView) {
			// switch the multiview
			multiView->nextView();
			testinc = 0;
			
			if (testflash++ >= 30) {
				multiView->setState(!multiView->curState()); // disable
				if (multiView->curState()) {
					testflash = 0;
				} else {
					testflash = 10;
				}
			}

		}
		

		realScreenView->draw();
	}
}




// ********************************
// class FPSView
//

class FPSView : public View { // C++ to C callthrough to paint the FPS
protected:
	virtual void drawSelf() {
		if( bShowFrameCount ) {
		    DWORD               time2;
			char                buff[256];

			dwFrameCount++;
		    time2 = i_time_ms() - dwFrameTime;
		    if( time2 > 1000 ) {
				dwFrames = (unsigned int)(((double)dwFrameCount*(double)1000.0)/(double)time2);
				dwFrameTime = i_time_ms();
		        dwFrameCount = 0;
		    }

			if (dwFrames != dwFramesLast) {
				dwFramesLast = dwFrames;
			}

			if( dwFrames > 99 ) {
				dwFrames = 99;
			}
			buff[0] = (char)((dwFrames / 10) + '0');
		    buff[1] = (char)((dwFrames % 10) + '0');
		    buff[2] = '\0';
		    bltText(buff, ScreenX - 80, 10);
			dbgMsg(c_excessive,"dwFrames: %f  dwFrameCount:%X time2:%X\n",dwFrames, dwFrameTime, time2);
		}
	}
public:
	FPSView(int x,int y, int w, int h) : View (x,y,w,h) {}
};

// ********************************
// class TestView
//

class TestView : public View { // test view to checkout the draw heirarchy
	int imagenum;
public:
	TestView(int x,int y,int w, int h,int opt) : View(x,y,w,h) {
		imagenum = opt;
		
	}

	virtual void drawSelf() {
			// put drawing code here!!!
	}
};


int handleMVInput(IN_EVENT *ev) {
	int retval = 0; // did we handle the event?

	switch(ev->dev_type) {
		case DT_KEYBOARD:
			if(ev->dev.keyboard.mask & KM_ASCII_KEY) {
				switch (ev->dev.keyboard.ascii_code) {
					case '`': // tilde -> rotate multiview...
						mainTabView->nextView();
						retval = 1;
						break;
					default:
						break;
				}
			}
			break;
		case DT_JOYSTICK: 
			break;
		case DT_MOUSE:  // software mouse pointer??
			break;
		default:
			break;

	}
	return retval;
}



void initViews() {
	View *temp_view;
	MultiView *a_tabview;
	int viewPortWidth = ScreenX - 177;
	int viewPortHeight = ScreenY - 50;

	realScreenView = new View(0,0,ScreenX, ScreenY); // real screen (TOP)
	
	// main multview

	realScreenView->addSubview(a_tabview = new MultiView(0,0,ScreenX,ScreenY));

	// major tabbed views
	a_tabview->addView(gameScreenPane = new View(0,0,ScreenX,ScreenY),"GameView Pane");
	//a_tabview->addView(productionPane = new View(0,0,ScreenX,ScreenY),"Production Pane");
	a_tabview->addView(consolePane    = new View(0,0,ScreenX,ScreenY),"Console Pane");

	// add splash startup pane
	// a_tabview->addView(new ImageView(0,0,ScreenX,ScreenY,"splash.bmp"),"Console Pane");

	a_tabview->switchTo(1);
	// add FPS view...
	FPSView *fps_view = new FPSView(0,0,0,0);
	fps_view->setDepth(7);
	realScreenView->addSubview(fps_view);

	// tell everyone else what the mainTabview is...
	mainTabView = a_tabview;

	// PRODUCTION PANE

		// we need something in the other tabview so here:
		productionPane->addSubview(status_bar);


    // CONSOLE PANE
		
		consoleView = new ConsoleView(40,40,ScreenX-50,ScreenY-50);
		consoleView->setDepth(7);
		consoleView->addText("Console Startup...");
		{
			char s[120];
			sprintf(s,"ScreenMode: %dx%dx%dbpp",ScreenX, ScreenY, ScreenBpp);
			consoleView->addText(s);
			if (bUseEmulation) {
				consoleView->addText("HAL Emulation only...");
			}
		}
		consoleView->setConsoleHandler(handleConsoleInput); // setup our handler fn
	

		consolePane->addSubview(new TextureView(0,0,ScreenX,ScreenY));
		consolePane->addSubview(consoleView);


		// test an imageview behind the console..
		temp_view = new ImageView(0,0,ScreenX,ScreenY,"splash.bmp");

//		temp_view = new ImageView(0,0,40,ScreenY,i_fix_path("std/conbkg.bmp"));
//		temp_view->setDepth(2);
//		consolePane->addSubview(temp_view);
//		temp_view = new ImageView(0,0,ScreenX, 40, i_fix_path("std/conbkg.bmp"));

		temp_view->setDepth(3);
		consolePane->addSubview(temp_view);
	
	// TESTING JUNK, making a tab overlay
		
		
		/*
		a_tabview = new MultiView(0,0,ScreenX, ScreenY);
		a_tabview->addView(new View(0,0,ScreenX,ScreenY),"empty view");
		a_tabview->addView(consoleView,"Console overlay");
		a_tabview->setDepth(20); // front!
		gameScreenPane->addSubview(a_tabview);
		mainTabView = a_tabview;

		ConsoleView *consoleView = new ConsoleView(30,30,200,70);
		consoleView->setDepth(20);
		consoleView->addText("Testing...");
		gameScreenPane->addSubview(consoleView);
		*/
	// MAIN GAME SCREEN 

		multiView = new MultiView(600,0,50,50);
		multiView->setDepth(10);
		gameScreenPane->addSubview(multiView);
		
		
		// main map display
		temp_view = mainViewPort = new ViewPort(0,0,viewPortWidth,viewPortHeight);
		temp_view->setDepth(-1);
		gameScreenPane->addSubview(temp_view); 

		char player_view_filename[] = "std/con_player_view.bmp";
		char status_view_filename[] = "std/con_status.bmp";
		char hzdoors_view_filename[] = "std/con_hz_doors.bmp";

		int player_view_width = 177, player_view_height = 145;
		int status_view_width = 177, status_view_height = 143;
		int hzdoors_view_width = 177, hzdoors_view_height = 128;
		int cur_y = 0;

		View *player_view = new ImageView(ScreenX - player_view_width,cur_y,
				player_view_width,player_view_height,
				player_view_filename);	
		player_view->setDepth(5);
		cur_y += player_view_height;

		View *status_view = new ImageView(ScreenX - status_view_width,cur_y,
				status_view_width,status_view_height,
				status_view_filename);
		status_view->setDepth(5);
		cur_y += status_view_height;

		View *hzdoors_view = new ImageView(ScreenX - hzdoors_view_width,cur_y,
				hzdoors_view_width,hzdoors_view_height,
				hzdoors_view_filename);
		hzdoors_view->setDepth(5);
		cur_y += hzdoors_view_height;


		gameScreenPane->addSubview(player_view);
		gameScreenPane->addSubview(status_view);
		gameScreenPane->addSubview(hzdoors_view);


		// main map display - clouds
		// temp_view = new MainView(0,0,0,0,1);
		// temp_view->setDepth(7);
		// gameScreenView->addSubview(temp_view); 


		// HUD for ship...
		// temp_view = new HUDView(300,220,40,40);
		// temp_view->setDepth(7);
		// gameScreenPane->addSubview(temp_view);

		// health bar
		status_bar = new HorizStatusBar(25,10,150,12,20);
		status_bar->setValue(5);
		status_bar->setDepth(7);
		gameScreenPane->addSubview(status_bar);


		status_bar2 = new HorizStatusBar(viewPortWidth - (150 + 25),10,150,12,50);
		status_bar2->setValue(5);
		status_bar2->setDepth(7);
		gameScreenPane->addSubview(status_bar2);

		loadingBar = new HorizStatusBar(50,12,200,15,20);
		loadingBar->setMaxValue(35);
		loadingBar->setDepth(15);
		consolePane->addSubview(loadingBar);


//		multiView->addView(new TestView(350,20,50,50,0),"view1");
//		multiView->addView(new TestView(350,20,50,50,1),"view2");
//		multiView->addView(new TestView(350,20,50,50,2),"view2");
//		multiView->addView(new TestView(350,20,50,50,3),"view2");
//		multiView->addView(new TestView(350,20,50,50,4),"view2");
//		multiView->addView(new TestView(350,20,50,50,5),"view2");
//		multiView->addView(new TestView(350,20,50,50,6),"view2");
//		multiView->addView(new TestView(350,20,50,50,7),"view2");
//		multiView->addView(new TestView(350,20,50,50,8),"view2");
//		multiView->addView(new TestView(350,20,50,50,9),"view2");

	
		// x,y,w,h mean nothing to MainView right now...

		// tell the main view it has input focus.
		realScreenView->setInputFocus(TRUE); // ALWAYS has focus !
		// setup the main callback...
		realScreenView->setEventCallback(handleMVInput);
}


void DestroyGame( void )
{
	CleanupAndExit("Clean exit.");
}

extern int should_die; // to tell threads to die


//--------------------------------------------------------------------
// from donuts.cpp


void UpdateFrame( void )
{
  //  I_Message ("UpdateFrame\n");
  switch( ProgramState ) {
  case PS_SPLASH:
    // display the splash screen
    dbgMsg(c_excessive,"UpdateFrame: PS_SPLASH\n");
    bltSplash();
    ProgramState = PS_BEGINREST;
    return;
  case PS_ACTIVE:
    dbgMsg(c_excessive,"UpdateFrame: PS_ACTIVE\n");
    UpdateDisplayList();
    DrawDisplayList();
    return;
  case PS_BEGINREST:
    DrawDisplayList();  // prime drawing
    setup_game();		// setup the game for the first time
    
    dbgMsg(c_excessive,"UpdateFrame: PS_BEGINREST\n");
#ifdef USE_DSOUND
    if(bWantSound) {
      SndObjPlay(hsoBeginLevel, 0);
    }
#endif
    ProgramState = PS_REST;
    //
    // FALLTHRU
    //
  case PS_REST:
    dbgMsg(c_excessive,"UpdateFrame: PS_REST\n");
    
    if( ( i_time_ms() - restCount ) > ShowLevelCount ) {
#ifdef USE_DSOUND
      if(bWantSound) {
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


// LPDIRECTDRAWPALETTE     lpSplashPalette;
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

	I_EraseScreen();
	paintScreen(); // C passthrough to C++ View classes in main.cpp
	// we should sleep here to lock the framerate
	I_FlipScreen();

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


