// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

// DrawHndl.cpp
// this will handle the platform specific drawing stuff...

#include "i_video.h"
#include "..\Donuts.h"   // this shouldn't be here
#include "DrawHndl.h"
#include "..\Main.h"     // nor should this
#include "i_system.h" // CleanupAndExit()

void EraseScreen( void )
{
    DDBLTFX     ddbltfx;
    HRESULT     ddrval;

    if( bSpecialEffects )   // cool looking screen with no colorfill
        return;

    // Erase the background
    ddbltfx.dwSize = sizeof( ddbltfx );
    ddbltfx.dwFillColor = dwFillColor;
    while( 1 )
    {
        ddrval = lpBackBuffer->Blt(NULL, NULL,
                 NULL, DDBLT_COLORFILL, &ddbltfx );

        if( ddrval == DD_OK )
        {
            break;
        }
        if( ddrval == DDERR_SURFACELOST )
        {
            if( !RestoreSurfaces() )
                return;
        }
        if( ddrval != DDERR_WASSTILLDRAWING )
        {
           return;
        }
    }
}

void FlipScreen( void )
{
    HRESULT     ddrval;

    // Flip the surfaces
    while( 1 )
    {
        ddrval = lpFrontBuffer->Flip(NULL, 0 );
        if( ddrval == DD_OK )
        {
            break;
        }
        if( ddrval == DDERR_SURFACELOST )
        {
            if( !RestoreSurfaces() )
            {
                return;
            }
        }
        if( ddrval != DDERR_WASSTILLDRAWING )
        {
            break;
        }
    }
}



// this pretty much does not work!

int RestoreSurfaces( void )
{
    HRESULT     ddrval;

	if (consoleView) {
		consoleView->addText("Restore Surfaces...");
	}

    ddrval = lpFrontBuffer->Restore();
    if( ddrval != DD_OK )
        return FALSE;

#if 0
    // Create and set the palette for the splash bitmap
    lpSplashPalette = DDLoadPalette( lpDD, "SPLASH" );
    if( NULL == lpSplashPalette )
        return CleanupAndExit("DDLoadPalette SPLASH");
#endif

    // set the palette before loading the art
//    lpFrontBuffer->SetPalette(lpArtPalette );

    return TRUE;
}
