/*
 * initApplication
 *
 * Do that Windows initialization stuff...
 */

#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <ddraw.h>
#ifdef USE_DSOUND
#include <dsound.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include "resource.h"
#include "ddutil.h"
#ifdef USE_DSOUND
#include "dsutil.h"
#endif

#include "donuts.h"



static BOOL initApplication( HANDLE hInstance, int nCmdShow )
{
    WNDCLASS    wc;
    BOOL        rc;

    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = MainWndproc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( hInstance, "DONUTS_ICON");
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = GetStockObject( BLACK_BRUSH );
    wc.lpszMenuName =  NULL;
    wc.lpszClassName = "DonutsClass";
    rc = RegisterClass( &wc );
    if( !rc )
    {
        return FALSE;
    }

    hWndMain = CreateWindowEx(0,  // WS_EX_TOPMOST,
        "DonutsClass",
        "Donuts",
        WS_VISIBLE | // so we don't have to call ShowWindow
        WS_POPUP |   // non-app window
        WS_SYSMENU,  // so we get an icon in the tray
        0,
        0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL,
        NULL,
        hInstance,
        NULL );

    if( !hWndMain )
    {
        return FALSE;
    }

    UpdateWindow( hWndMain );

    return TRUE;

} /* initApplication */

/*
 * WinMain
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
                        int nCmdShow )
{
    MSG     msg;

    while( lpCmdLine[0] == '-' )
    {
        lpCmdLine++;

        switch (*lpCmdLine++)
        {
        case 'e':
            bUseEmulation = TRUE;
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

    ScreenX = getint(&lpCmdLine, 640);
    ScreenY = getint(&lpCmdLine, 480);
    ScreenBpp = getint(&lpCmdLine, 8);

    if( !initApplication(hInstance, nCmdShow) )
    {
        return FALSE;
    }

    if( !InitializeGame() )
    {
        DestroyWindow( hWndMain );
        return FALSE;
    }

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
        }
        else
        {
            WaitMessage();
        }
    }
} /* WinMain */

void DestroyGame( void )
{
}



BOOL CleanupAndExit( char *err)
{
#ifdef DEBUG
    wsprintf(DebugBuf, "___CleanupAndExit  err = %s\n", err );
    OutputDebugString( DebugBuf );
#endif

    // make the cursor visible
    SetCursor(LoadCursor( NULL, IDC_ARROW ));
    bMouseVisible = TRUE;


    if( lpSplashPalette != NULL )
        lpSplashPalette->Release();

	if( lpTile00 != NULL )
		lpTile00->Release();
	if( lpTile01 != NULL )
		lpTile01->Release();
	if( lpTile02 != NULL )
		lpTile02->Release();
    

	if( lpFrontBuffer != NULL )
        lpFrontBuffer->Release();


	if( lpDD != NULL )
        lpDD->Release();

    //
    // warn user if there is one
    //

    if( !bStress )
    {
        MessageBox( hWndMain, err, "ERROR", MB_OK );
    }
    return FALSE;
}

