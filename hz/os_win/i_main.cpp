// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske


//
// i_main.cpp
//
// This is the main entry point for the program, it should handle parsing command
// line args, setting up a primary display, initializing the game, and then doing
// the high-level input message handling for the OS.
//



#include "i_video.h" // for initAppWindow()
#include "i_system.h" // for timer..
#include "hndlmgr.h" // handle manager
#include "..\donuts.h" // for the boolean flags
#include "..\net.h" // for init_server();
#include "..\main.h" // for initViews();


int getint(char**p, int def)
{
    int i=0;                                 


    while (IS_SPACE(**p))
        (*p)++;

    if (!IS_NUM(**p))
        return def;

    while (IS_NUM(**p))
        i = i*10 + *(*p)++ - '0';

    while (IS_SPACE(**p))
        (*p)++;

    return i;
}



/*
 * WinMain
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
                        int nCmdShow )
{
    MSG     msg;
	hndlMgr = new HandleManager(); // declare a handle manager for GDI handles

	/* first we need to process command line arguments */

    while( lpCmdLine[0] == '-' )
    {
        lpCmdLine++;

        switch (*lpCmdLine++)
        {
        case 'e':
            bUseEmulation = TRUE;
			printf("UseEmulation\n");
            break;
        case 't':
            bTest = TRUE;
            break;
        case 'S':
            bWantSound = FALSE;
            break;
        case 'x':
            bStress= TRUE;
            bTest = TRUE;
            break;
        }
        while( IS_SPACE(*lpCmdLine) )
        {
            lpCmdLine++;
        }
    }

/*
	HRESULT cores = CoInitialize(NULL);

	switch (cores) {
	case S_OK: //	The library was initialized successfully.
		break;
	case S_FALSE: //	Already initialized; didn’t use pMalloc, if given.
		break;
	case E_OUTOFMEMORY: // 	Out of memory.
		exit(1);
		break;
	case E_INVALIDARG : // 	pMalloc is invalid.
		exit(1);
		break;
	default:
	case E_UNEXPECTED : 
		exit(1);
		break;
	}
	*/

    ScreenX = getint(&lpCmdLine, 640);
    ScreenY = getint(&lpCmdLine, 480);
    ScreenBpp = getint(&lpCmdLine, 16);

    if( !initAppWindow(hInstance, nCmdShow) )
    {
        return FALSE;
    }

    if( !I_InitVideo() )
    {
        DestroyWindow( hWndMain );
        return FALSE;
    }
    lastTickCount = i_time_ms();

//    InitializeSound();

    ProgramState = PS_SPLASH;


    init_server();
    initViews();

    dwFrameTime = i_time_ms();

    while( 1 )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
        {
            if( !GetMessage( &msg, NULL, 0, 0 ) )
            {
                return msg.wParam;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else if ( bIsActive )
        {
            UpdateFrame();
			// we should do some kind of speed independent "doTick" here 
        }
        else
        {
            WaitMessage();
        }
    }
} /* WinMain */
