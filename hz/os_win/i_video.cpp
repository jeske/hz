// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

//
// i_video.cpp
//
// platform specific video routines
//
// this should setup a double buffered display for drawing inside i_draw.cpp
//

#include "i_video.h"
#include "..\donuts.h"
#include "drawhndl.h"
#include "i_system.h" // CleanupAndExit()
#include "..\map.h" // ViewPort
#include "..\vconsole.h"

#include "hndlmgr.h"

void bltText( char *num, int x, int y );

LPDIRECTDRAW            lpDD;
LPDIRECTDRAWSURFACE     lpFrontBuffer;
LPDIRECTDRAWSURFACE     lpBackBuffer;
DWORD                   dwTransType;
static HPEN 					linepen;
static HBRUSH					solidbrush;
static HPEN 					blackpen;
static HBRUSH 					blackbrush;

long FAR PASCAL MainWndproc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

BOOL initAppWindow( HINSTANCE hInstance, int nCmdShow )
{
    WNDCLASS    wc;
    BOOL        rc;

    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = MainWndproc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = ((HICON) LoadIconA( (HINSTANCE) hInstance, "WIN_ICON"));
    wc.hCursor = ((HCURSOR) LoadCursor( (HINSTANCE)NULL, IDC_ARROW ));
    wc.hbrBackground = GetStockBrush( BLACK_BRUSH );
    wc.lpszMenuName =  NULL;
    wc.lpszClassName = "SSGameClass";
    rc = RegisterClass( &wc );
    if( !rc )
    {
        return FALSE;
    }

    hWndMain = CreateWindowEx(0,  // WS_EX_TOPMOST,
        "SSGameClass",
        "HZ",
        WS_VISIBLE | // so we don't have to call ShowWindow
        WS_POPUP |   // non-app window
        WS_SYSMENU,  // so we get an icon in the tray
        500, // x, we are going to put it mostly off the screen because
        500, // y, DirectX is fucked...
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        (HWND) NULL,
        (HMENU) NULL,
        (HINSTANCE) hInstance,
        (LPVOID) NULL );

    if( !hWndMain )
    {
        return FALSE;
    }

    UpdateWindow( hWndMain );

    return TRUE;

} /* initAppWindow */



LPDIRECTDRAWPALETTE lpArtPalette = NULL;

BOOL I_vid_setpalette(const char *filename) {
	// should free the old palette
	
	// Create and set the palette for the art bitmap
	lpArtPalette = DDLoadPalette( lpDD, filename );
	if( NULL == lpArtPalette )
        return CleanupAndExit("DDLoadPalette DONUTS");
	
	// set the palette
    lpFrontBuffer->SetPalette(lpArtPalette );
	return 1; // pass
}

// #define NT_HACK 1

BOOL I_InitVideo( void )
{
    DDCAPS          ddcaps;
    HRESULT         ddrval;
    DDSURFACEDESC   ddsd;
    DDSCAPS         ddscaps;
#ifdef NT_HACK
    DDSURFACEDESC DDSurfDesc;
#endif

    score = 0;
    if( bTest )
        ShowLevelCount = 1000;

    if( bUseEmulation )
        ddrval = DirectDrawCreate( (GUID *)DDCREATE_EMULATIONONLY, &lpDD, NULL );
    else
        ddrval = DirectDrawCreate( NULL, &lpDD, NULL );

    if( ddrval != DD_OK )
        return CleanupAndExit("DirectDrawCreate Failed!");
	
	if( !bUseEmulation ) {
		ddrval = lpDD->SetCooperativeLevel(hWndMain,
					DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN  );
		if( ddrval != DD_OK )
			return CleanupAndExit("SetCooperativeLevel Failed");

	    
	}



    #ifdef NT_HACK
        DDSurfDesc.dwSize = sizeof(DDSurfDesc);
        ddrval = lpDD->GetDisplayMode(&DDSurfDesc);
        if(ddrval == DD_OK) {
           ScreenBpp = DDSurfDesc.ddpfPixelFormat.dwRGBBitCount;
        }
    #endif

    // set the mode
	ddrval = lpDD->SetDisplayMode(ScreenX, ScreenY, ScreenBpp );
	if( ddrval != DD_OK ) {
		return CleanupAndExit("SetDisplayMode Failed!");
	}

    // check the color key hardware capabilities
    dwTransType = DDBLTFAST_SRCCOLORKEY;
    ddcaps.dwSize = sizeof( ddcaps );

//#ifdef DEBUG
//    if( GetProfileInt( "Donuts", "force_dest_blt", 0) )
//    {
//        dwTransType = DDBLTFAST_DESTCOLORKEY;
//    }
//    bHELBlt = GetProfileInt( "Donuts", "force_HEL_blt", bHELBlt );
//#endif

    // Create surfaces

	if (!bUseEmulation) {
		memset( &ddsd, 0, sizeof( ddsd ) );
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
			DDSCAPS_FLIP |
			DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 1;

		ddrval = lpDD->CreateSurface(&ddsd, &lpFrontBuffer, NULL );

		if( ddrval != DD_OK ) {
			return CleanupAndExit("CreateSurface FrontBuffer Failed!");
		}
	} else {

		
		memset( &ddsd, 0, sizeof( ddsd ) );
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 0;

		ddrval = lpDD->CreateSurface(&ddsd, &lpFrontBuffer, NULL );

		if( ddrval != DD_OK ) {
			return CleanupAndExit("CreateSurface FrontBuffer Failed!");
		}
	}

	DDBLTFX ddbltfx;
	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.dwFillColor = 0; // black

	lpFrontBuffer->Blt(
		NULL, 		// Destination is entire surface
		NULL,		// No source surface
		NULL,		// No source rect
		DDBLT_COLORFILL, &ddbltfx);

    // get a pointer to the back buffer
    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    ddrval = lpFrontBuffer->GetAttachedSurface(
                &ddscaps,
                &lpBackBuffer );
    if( ddrval != DD_OK )
        return CleanupAndExit("GetAttachedDurface Failed!");

    ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
#ifdef DEBUG
    if( bHELBlt )
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
#endif

    if( !RestoreSurfaces() )
        return CleanupAndExit("RestoreSurfaces Failed!");

    hndlMgr->addHandle(linepen =  CreatePen(PS_SOLID,0,RGB(255,255,0)));
    hndlMgr->addHandle(blackpen = CreatePen(PS_SOLID,0,RGB(0,0,0)));
    hndlMgr->addHandle(blackbrush = CreateSolidBrush(RGB(0,0,0)));
    hndlMgr->addHandle(solidbrush = CreateSolidBrush(RGB(255,255,0)));
    if (!linepen || !blackpen || !blackbrush) {
      CleanupAndExit("Couldn't CreatePen() in ConsoleView::ConsoleView()");
    }

    return TRUE;
}

// bltSplash(void)
//
// it is crappy to just throw this in here. However, this function should disappear
// anyhow eventually....

void bltSplash( void )
{
    HRESULT     ddrval;
    HBITMAP     hbm;

    // set the palette before loading the splash screen
    lpFrontBuffer->SetPalette(lpSplashPalette);

    hbm = (HBITMAP)LoadImage( GetModuleHandle( NULL ), "SPLASH", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
//    hbm = (HBITMAP)LoadImage( NULL, "SPLASH", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
    if ( NULL == hbm )
        return;

    // if the surface is lost, DDCopyBitmap will fail and the surface will
    // be restored in FlipScreen.
    ddrval = DDCopyBitmap( lpBackBuffer, hbm, 0, 0, 0, 0 );

    DeleteObject( hbm );

    FlipScreen();
}

#ifdef REMOVE_VIEWPORT_BLIT
void ViewPort::doBlit(RECT *dest,RECT *src, LPDIRECTDRAWSURFACE surf) {
	HRESULT ddrval;	
		ddrval = lpBackBuffer->BltFast(dest->left, dest->top, 
						surf, src, dwTransType );
				switch (ddrval) {
				case DD_OK:	
					break;
				case DDERR_SURFACELOST:
					if( !RestoreSurfaces() )
						return;
				case DDERR_WASSTILLDRAWING:
					return;
				}
}
#endif

void I_doBlit(RECT *dest, RECT *src_cliprect, IMAGE *an_image) {
	HRESULT ddrval;
	

	if (src_cliprect == NULL) {
		src_cliprect = &(an_image->src);
	}

	do {
				
			/*
			 *	ddrval = lpBackBuffer->BltFast(x,y, an_image->surf, 
			 *	&(an_image->src), dwTransType  | DDBLTFAST_WAIT );
			 */
				
		//ddrval = lpBackBuffer->Blt(dest, an_image->surf, 
		//					&(an_image->src), dwTransType  | DDBLT_KEYSRC , NULL);
		ddrval = lpBackBuffer->BltFast(dest->left,dest->top,
					an_image->surf,src_cliprect, dwTransType);

			if (ddrval != DD_OK) {
				if( ddrval == DDERR_SURFACELOST ) {
					an_image->surf->Restore();
				} else {
					dbgMsg(c_error,"failed drawing image [%s] (ERR = %d)",an_image->name, ddrval);
				}

			/*
			 * else if ( ddrval != DDERR_WASSTILLDRAWING ) {
			 *    dbgMsg(c_error,"DDERR_WASSTILLDRAWING");
			 *    Sleep(10);
			 *    fail_count++;
			 *    if (fail_count > 20) {
			 *        return;
			 *    }
			 * }
			 */

			}
		} while (ddrval == DDERR_WASSTILLDRAWING);
}

#if 0
void doBlitOLD(RECT *dest,RECT *src) {
	HRESULT ddrval;	
		ddrval = lpBackBuffer->BltFast(dest->left, dest->top, 
						this->my_image.surf, src, dwTransType );
				switch (ddrval) {
				case DD_OK:	
					break;
				case DDERR_SURFACELOST:
					if( !RestoreSurfaces() )
						return;
				case DDERR_WASSTILLDRAWING:
					return;
				default:
					break;
					{
						char s[200];
						sprintf(s,"unknown return type (%X)from BltFast in Tile::doBlit(), dest=(%d,%d,%d,%d), src=(%d,%d,%d,%d) ",
							ddrval, dest->left,dest->top, dest->right, dest->bottom, src->left,src->top,src->right,src->bottom);
						CleanupAndExit(s);
					}
				}
}
#endif

void I_SetWindowText(char *str) {
	SetWindowText(hWndMain,str);
}

int I_CreateDrawable (RECT *src, char *name, DRAWABLE *draw)
{
  // setup the offscreen backstore
  DDSURFACEDESC ddsd;
  HRESULT ddrval;
  int width = src->right - src->left;
  int height = src->bottom - src->top;

  draw->image = (IMAGE *) malloc (sizeof (IMAGE));
  draw->image->name = strdup (name);
  draw->image->src.left = 0;
  draw->image->src.top = 0;
  draw->image->src.right = width;
  draw->image->src.bottom = height;
  draw->hdc = NULL;
  // Create surfaces
  memset (&ddsd, 0, sizeof (ddsd));
  ddsd.dwSize = sizeof (ddsd);
  ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
  ddsd.dwWidth = width;
  ddsd.dwHeight = height;
  //ddsd.ddsCaps.dwCaps |= DDSCAPS_OFFSCREENPLAIN;
  ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;

  ddrval = lpDD->CreateSurface (&ddsd, &(draw->image->surf), NULL);
  if (ddrval != DD_OK) {
    CleanupAndExit ("I_CreateDrawable: CreateSurface Failed!");
  }

  DDSetColorKey (draw->image->surf, CLR_INVALID);
 
  // choose the standard non-proportional font...
  ddrval = draw->image->surf->GetDC(&draw->hdc);
  SelectObject(draw->hdc, GetStockObject(ANSI_FIXED_FONT));
  draw->image->surf->ReleaseDC(draw->hdc);
  draw->hdc = NULL;

  return TRUE;
} 

int I_FreeDrawable (DRAWABLE *draw)
{
  draw->image->surf->Release();
  return TRUE;
}

void I_ClearDrawable (DRAWABLE *draw, int x1, int y1, int x2, int y2)
{

  if (draw->hdc) {
	
	SetBkMode(draw->hdc,OPAQUE);
	SelectObject(draw->hdc,blackbrush); // the "inside" of the rectangle
	SelectObject(draw->hdc,blackpen);   // the "outline" of the rectangle..
	Rectangle(draw->hdc, x1, y1, x2, y2);

	// SetBkColor(draw->hdc,RGB(0,0,0));
	// SetBkMode(draw->hdc,TRANSPARENT);
	// SetTextColor(draw->hdc,RGB(255,255,0));

  } else {
	// Alternate implementation, faster for clearing whole ddraw surface?
	HRESULT     ddrval;
	DDBLTFX     ddbltfx;
	
	ddbltfx.dwSize = sizeof (ddbltfx);
	ddbltfx.dwFillColor = dwFillColor;
	while( 1 )
	{
	    ddrval = draw->image->surf->Blt(NULL, NULL, NULL, DDBLT_COLORFILL, &ddbltfx );
	
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

  
}

void I_GetTextExtent (DRAWABLE *draw, char *s, int len, SIZE *line_size)
{
  GetTextExtentPoint32 (draw->hdc, s, len, line_size);
}

void I_TextOut (DRAWABLE *draw, int x, int y, char *s, int len)
{
	SelectObject (draw->hdc,linepen);
	SetBkMode (draw->hdc, OPAQUE);
	SetBkColor(draw->hdc,RGB(0,0,0));
	SetTextColor (draw->hdc, RGB(255,255,0));
	TextOut (draw->hdc, x, y, s, len);
	
	// bltText(s,x,y); // hack
}

int I_GetDrawContext (DRAWABLE *draw)
{
  HRESULT ddrval;

  if (draw->hdc != NULL) {
	  CleanupAndExit("I_GetDrawContext(): hdc not null!");
  }

  ddrval = draw->image->surf->GetDC(&draw->hdc);

  if (ddrval != DD_OK) {
    CleanupAndExit ("I_GetDrawContext: GetDC Failed!");
    return FALSE;
  } else {
    SelectObject (draw->hdc, linepen);
    SelectObject(draw->hdc, GetStockObject(ANSI_FIXED_FONT));
  }

  // SelectObject(draw->hdc, GetStockObject(ANSI_FIXED_FONT));

  return TRUE;
}

int I_ReleaseDrawContext (DRAWABLE *draw)
{
  draw->image->surf->ReleaseDC(draw->hdc);
  draw->hdc = NULL;

  return TRUE;
}

void I_FillRectangle (DRAWABLE *draw, int x1, int y1, int x2, int y2)
{
  // SelectObject (draw->hdc,linepen);
  SetBkMode (draw->hdc, OPAQUE);
  SetBkColor(draw->hdc,RGB(255,255,0));
  SelectObject(draw->hdc,solidbrush);
  Rectangle (draw->hdc, x1, y1, x2, y2);
}

void I_SetFGColor (DRAWABLE *draw, int r, int g, int b)
{
  SetTextColor (draw->hdc, RGB(r,g,b));
}

void I_DrawLine(DRAWABLE *draw, int x1, int y1, int x2, int y2)
{
  POINT line[2];

  if (!draw->hdc) {
	  CleanupAndExit("I_DrawLine() tried to draw to null hdc");
  }
  SelectObject(draw->hdc, linepen);
  line[0].x = x1;
  line[0].y = y1;
  line[1].x = x2;
  line[1].y = y2;

  Polygon (draw->hdc, line, 2);
}


void bltText( char *num, int x, int y ) {
	HDC hdc;
	
	if (linepen == NULL) {
		hndlMgr->addHandle(linepen =  CreatePen(PS_SOLID,0,RGB(255,255,0)));
	}

	if (lpBackBuffer->GetDC(&hdc) == DD_OK) {
		SelectObject(hdc,linepen);
		//SetBkColor(hdc,RGB(0,0,0));
		//SetBkMode(hdc,TRANSPARENT);

		TextOut(hdc,x,y,num, strlen(num));
		lpBackBuffer->ReleaseDC(hdc);
	}

}


void I_drawLine(int x1, int y1, int x2, int y2) {
	HDC hdc;
	POINT line[2];

	if (linepen == NULL) {
		hndlMgr->addHandle(linepen =  CreatePen(PS_SOLID,0,RGB(255,255,0)));
	}

	if (lpBackBuffer->GetDC(&hdc) == DD_OK) {
		SelectObject(hdc,linepen);
		//SetBkColor(hdc,RGB(0,0,0));
		//SetBkMode(hdc,TRANSPARENT);

		line[0].x = x1;
		line[0].y = y1;
		line[1].x = x2;
		line[1].y = y2;

		Polygon(hdc, line,2);

		lpBackBuffer->ReleaseDC(hdc);
	}
}
