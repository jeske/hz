// HZ Engine Source
// Copyright (C) 1999 by Brandon C. Long


#include "config.h"
#include "translate.h"
#include "i_console.h"
#include "i_draw.h"
#include "i_video.h"
#include "i_system.h"
#include "image.h"
#include "main.h" // realScreenView
#include "game.h" // setup_game

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_gfxPrimitives.h"


#define SCREENWIDTH 640
#define SCREENHEIGHT 480

int X_screen;
int X_width;
int X_height;
int X_depth;

// MIT SHared Memory extension.
BOOL doShm;
unsigned char *screens[2];
int FullScreen = 0;

SDL_Surface *SScreen;
SDL_Surface *sBackBuffer;
TTF_Font *fArialFont;

void I_Quit (void)
{
  SDL_Quit();
  exit (0);
}

BOOL I_InitVideo (void)
{
  char* displayname = NULL;
  char* d;
  int n, pnum, x=0, y=0;
  char xsign=' ';
  char ysign=' ';
  int oktodraw;
  unsigned long attribmask;
  int valuemask;
  static int firsttime=1;
  uint32 vid_flags;

  signal(SIGINT, (void (*)(int)) I_Quit);

  if ((SDL_Init (SDL_INIT_VIDEO) == -1))
  {
    I_Error ("Could not initialize SDL: %s.", SDL_GetError());
    return FALSE;
  }

  SDL_EnableUNICODE(1);

  X_width = SCREENWIDTH;
  X_height = SCREENHEIGHT;
  ScreenX = X_width;
  ScreenY = X_height;

  // open the display
  vid_flags = SDL_HWSURFACE|SDL_ANYFORMAT|SDL_DOUBLEBUF;
  if (FullScreen) vid_flags |= SDL_FULLSCREEN;
  SScreen = SDL_SetVideoMode (SCREENWIDTH, SCREENHEIGHT, 16, vid_flags);
  if (SScreen == NULL)
  {
    I_Error ("Couldn't get %dx%dx16 video mode: %s", SCREENWIDTH, SCREENHEIGHT, 
	SDL_GetError());
    return FALSE;
  }

  // init ttf and load arial font
  if (TTF_Init())
  {
    I_Error ("TTF_Init failed %s", SDL_GetError());
    return FALSE;
  }

  fArialFont = TTF_OpenFont ("/usr/local/jre/lib/fonts/LucidaTypewriterRegular.ttf", 10);

  bIsActive = 1;

  return TRUE;
}

#define UTIMER 50000            /* how long between updates (useconds) */

int I_EventLoop()
{
  SDL_Event event;
  SDL_keysym key;
  IN_EVENT ev;
  int ascii_key = 0;


  while (SDL_PollEvent (&event) || ProgramState == PS_SPLASH)
  {
    I_Message ("Got event %d in %d\n", event.type, ProgramState);
    switch (event.type)
    {
    case SDL_ACTIVEEVENT:
      if (!(event.active.state & SDL_APPACTIVE))
      {
// 	bIsActive = 0;
	bMouseVisible = TRUE;
      }
      else
      {
	if (!bIsActive)
	{
	  bIsActive = 1;
	  lastTickCount = i_time_ms();
	}
      }
      break;

#if 0
    case Expose:    
      if (event.xexpose.count == 0)
      {
	bIsActive = 1;
	// XClearWindow (X_display, X_mainWindow);
	// FlipScreen();
      }
      break;
#endif
      
    case SDL_KEYDOWN:
      if (realScreenView) {

	// SDL keysyms are usually the same as ascii keys....
	ascii_key = event.key.keysym.unicode;
	if (ascii_key == 0)
	{
	  ev.dev.keyboard.mask = KM_KEYDOWN; 
	  ascii_key = event.key.keysym.sym;
	}
	else
	{
	  ev.dev.keyboard.mask = KM_KEYDOWN | KM_ASCII_KEY;
	}

	ev.dev_type = DT_KEYBOARD;
	ev.dev.keyboard.vk_code = ascii_key;
	ev.dev.keyboard.ascii_code = ascii_key;
//	I_Message ("Got Key %d/%d at %lu\n", key, event.xkey.state, i_time_ms());
	realScreenView->inputEvent(&ev);
      }

      switch (ascii_key) {
	case VK_RETURN:
	case '\n':
#if 0   
      // we handle this in the platform code anymore...
	  if (ProgramState == PS_SPLASH) {
//	    I_Message ("VK_RETURN at %lu\n", i_time_ms());
	    ProgramState = PS_BEGINREST;
	    DrawDisplayList();
	    setup_game();
	    XFillRectangle (X_display, pBackBuffer, X_black_gc, 0, 0, X_width, 
		X_height);
	  }
#endif
	  break;
	case VK_ESCAPE:
	case VK_F12:
	  return False;
      }

      break;

    case SDL_KEYUP:
      // if there is a screen, then pass the key
      if (realScreenView) {

	ascii_key = event.key.keysym.unicode;

	ev.dev_type = DT_KEYBOARD;
	ev.dev.keyboard.mask = KM_KEYUP;
	ev.dev.keyboard.vk_code = event.key.keysym.sym;
	I_Message ("Got Key %c (%d) at %lu\n", ascii_key, ascii_key, i_time_ms());
	ev.dev.keyboard.ascii_code = event.key.keysym.sym;
	realScreenView->inputEvent(&ev);
      }
      break;

    case SDL_MOUSEMOTION:
      if (realScreenView)
      {
	ev.dev_type = DT_MOUSE;
	ev.dev.mouse.xpos = event.motion.x;
	ev.dev.mouse.ypos = event.motion.y;
	ev.dev.mouse.mask =  (enum mouse_mask_enum) 0;
	realScreenView->inputEvent (&ev);
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (realScreenView)
      {
	unsigned long int mask = 0;
	ev.dev_type = DT_MOUSE;
	ev.dev.mouse.xpos = event.button.x;
	ev.dev.mouse.ypos = event.button.y;
	if (event.button.button == 0)
	{
	  mask |= MS_L_BUTTON;
	}
	if (event.button.button == 1) {
	  mask |= MS_M_BUTTON;
	}
	if (event.button.button == 2) {
	  mask |= MS_R_BUTTON;
	}
	ev.dev.mouse.mask =  (enum mouse_mask_enum) mask;
	realScreenView->inputEvent (&ev);
      }
      break;
    case SDL_QUIT:
      return FALSE;
    default:
      break;
  }
  }
  return TRUE;
}

#if 0
int I_createimage (IMAGEDATA *imd, IMAGE *image, int is_sprite)
{
  XImage *bImage = NULL, *mImage = NULL;
  int xx, yy; 
  uint16 *imdata;
  uint8 *mask_data;
  int size;
  int r, g, b;
  int divisor;

  divisor = X_depth / 8;

  I_Message ("Creating image %dx%d, Size is %d\n", imd->width, imd->height, 
  imd->width * imd->height * divisor);

  imdata = (uint16 *) malloc (imd->width * imd->height * 8);

  if (imdata == NULL)
    return FALSE;

  if (is_sprite)
  {
    size = (imd->width / 8);
    if (imd->width % 8)
      size++;
    mask_data = (uint8 *) calloc (1, size * imd->height);
    if (mask_data == NULL)
      return FALSE;
  }

  for (yy = 0; yy < imd->height; yy++)
  {
    for (xx = 0; xx < imd->width; xx++)
    {
      switch (X_depth)
      {
	case 24:
	  uint32 dp;

	  if (imd->colordepth == 24)
	  {
	    /* 24 to 16 bit */
	    b = (imd->data[(xx + yy * imd->width) * 3]);
	    g = (imd->data[(xx + yy * imd->width) * 3+1]);
	    r = (imd->data[(xx + yy * imd->width) * 3+2]);
	  }
	  else if (imd->colordepth == 8)
	  {
	    b = imd->palette[imd->data[(xx + yy * imd->width)]].blue; 
	    r = imd->palette[imd->data[(xx + yy * imd->width)]].red; 
	    g = imd->palette[imd->data[(xx + yy * imd->width)]].green; 
	  }
	  dp = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3); 
	  imdata[xx + yy * imd->width] = dp;
	  if (is_sprite && dp == imdata[0])
	  {
	    // this is a mask bit
	    mask_data[(xx / 8) + (yy * size)] |= (1 << (xx % 8));
	  }
	  break;
	  if (imd->colordepth == 24)
	  {
	  }
	  break;
	case 16:
	  uint16 dp;

	  if (imd->colordepth == 24)
	  {
	    /* 24 to 16 bit */
	    b = (imd->data[(xx + yy * imd->width) * 3]);
	    g = (imd->data[(xx + yy * imd->width) * 3+1]);
	    r = (imd->data[(xx + yy * imd->width) * 3+2]);
	  }
	  else if (imd->colordepth == 8)
	  {
	    b = imd->palette[imd->data[(xx + yy * imd->width)]].blue; 
	    r = imd->palette[imd->data[(xx + yy * imd->width)]].red; 
	    g = imd->palette[imd->data[(xx + yy * imd->width)]].green; 
	  }
	  dp = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3); 
	  imdata[xx + yy * imd->width] = dp;
	  if (is_sprite && dp == imdata[0])
	  {
	    // this is a mask bit
	    mask_data[(xx / 8) + (yy * size)] |= (1 << (xx % 8));
	  }
	  break;
      }
    }
  }

  bImage = XCreateImage(X_display, X_visual, X_depth, ZPixmap, 0, 
	(char *)imdata, imd->width, imd->height, 32, imd->width *divisor); 

  image->surf = XCreatePixmap (X_display, RootWindow (X_display, 
      DefaultScreen (X_display)), imd->width, imd->height, 
      DefaultDepth (X_display, DefaultScreen (X_display)));

  XPutImage (X_display, image->surf, X_gc, bImage, 0, 0, 0, 0, imd->width, 
      imd->height);

  image->mask = 0;

  if (is_sprite)
  {
    XGCValues values;
    GC mask_gc;

    mImage = XCreateImage(X_display, X_visual, 1, XYBitmap, 0, 
	(char *)mask_data, imd->width, imd->height, 8, size); 


    image->mask = XCreatePixmap (X_display, RootWindow (X_display, 
	DefaultScreen (X_display)), imd->width, imd->height, 1);

    mask_gc = XCreateGC(X_display, image->mask, 0, &values);

    XPutImage (X_display, image->mask, mask_gc, mImage, 0, 0, 0, 0, imd->width, 
	imd->height);

    XFreeGC (X_display, mask_gc);
    XDestroyImage (mImage);
  }

  XDestroyImage (bImage);

  return TRUE;
}
#endif

int I_CreateDrawable (RECT *src, char *name, DRAWABLE *draw)
{
  int width = src->right - src->left;
  int height = src->bottom - src->top;

  draw->image = (IMAGE *) malloc (sizeof (IMAGE));
  draw->image->name = strdup (name);
  draw->image->src.left = 0;
  draw->image->src.top = 0;
  draw->image->src.right = src->right - src->left;
  draw->image->src.bottom = src->bottom - src->top;
  draw->image->surf = SDL_CreateRGBSurface (SDL_HWSURFACE, width, height, 24, 0, 0, 0, 0);
  draw->fgcolor = SDL_MapRGB (draw->image->surf->format, 255, 255, 255);
  draw->bgcolor = SDL_MapRGB (draw->image->surf->format, 0, 0, 0);

  if (draw->image->surf) {
    I_ClearDrawable (draw, src->left, src->top, src->right, src->bottom);
    return 0;  // success
  } else {
    return 1;
  }
}

void I_doBlit (RECT *dest, RECT *src_cliprect, IMAGE *im)
{
  int width = dest->right - dest->left;
  int height = dest->bottom - dest->top;
  static RECT all  = { 0,0,0,0 };
  SDL_Rect dstrect, srcrect;
  int r = 0;
  
 // I_Message ("I_doBlit (%s, %x)\n", im->name, src_cliprect);
  // if there is no source cliprect, use the image.
#if 0
  if (src_cliprect == NULL) {
    src_cliprect = & (im->src);
    if (src_cliprect->left != 0)
    {
      I_Message ("src_cliprect %s = %d %d %d %d\n", im->name, src_cliprect->left, src_cliprect->top, src_cliprect->right - src_cliprect->left, src_cliprect->bottom - src_cliprect->top);
    }
  }
#endif

  dstrect.x = dest->left;
  dstrect.y = dest->top;
  dstrect.w = width;
  dstrect.h = height;

  if (src_cliprect != NULL) 
  {
    srcrect.x = src_cliprect->left;
    srcrect.y = src_cliprect->top;
    srcrect.w = width; // src_cliprect->right - src_cliprect->left;
    srcrect.h = height; // src_cliprect->bottom - src_cliprect->top;
    // I_Message ("I_doBlit (%s, (%d, %d), (%d, %d)) image = %d %d %d %d\n", im->name, srcrect.x, srcrect.y, srcrect.w, srcrect.h, im->src.left, im->src.top, im->src.right - im->src.left, im->src.bottom - im->src.top);
    if (height || width)
      r = SDL_BlitSurface (im->surf, &srcrect, SScreen, &dstrect);
  }
  else
  {
    if (height || width)
      r = SDL_BlitSurface (im->surf, NULL, SScreen, &dstrect);
  }
  if (r)
  {
    I_Error ("SDL_BlitSurface returned %d", r);
  }


  return;
}

void bltSplash (void)
{
  static IMAGE im = {NULL, NULL, {0,0,0,0}};
  RECT dest;

  dest.right = 640;
  dest.left = 0;
  dest.bottom = 480;
  dest.top = 0;

  if (im.surf == 0)
  {
    if (!I_loadImage (&im, "splash.bmp", 0))
    {
      I_doBlit (&dest, NULL, &im);
      I_FlipScreen ();
    }
    else
      I_Error ("Error loading splash.bmp");
  }
  else
  {
    I_doBlit (&dest, NULL, &im);
    I_FlipScreen ();
  }

  // delete image
  
  // return 0;
  return;
}

/* This function will need to load the palette from a bmp, eventually
 * Currently, we only implement 16 bit displays, which means no palette
 */
BOOL I_vid_setpalette (const char *filename)
{
  I_Message ("I_vid_setpalette (NOT IMPLEMENTED)\n");
  return TRUE;
}

void I_EraseScreen( void )
{
  uint32 color;

  color = SDL_MapRGB (SScreen->format, 0, 0, 0);
  SDL_FillRect (SScreen, NULL, color);
}

void I_FlipScreen( void )
{
  SDL_Flip (SScreen);
//  I_Message ("FlipScreen()\n");
}

void I_SetWindowText (char *title)
{
#if 0
  char *window_name = title;
  char *icon_name = title;
  XTextProperty windowName, iconName;

  XStringListToTextProperty(&window_name, 1, &windowName);
  XStringListToTextProperty(&icon_name  , 1, &iconName);
  XSetWMProperties(X_display, X_mainWindow, &windowName, &iconName,
      NULL, 0, NULL, NULL, NULL);
#endif
}

void bltText( char *num, int x, int y ) {
//  I_Message ("(%d, %d) %s\n", x, y, num);
  SDL_Surface *text;
  SDL_Color color = {255,255,255,0};
  SDL_Rect dstrect;
  int r;

  stringColor (SScreen, x, y, num, 0xffffffff);
#if 0
  text = TTF_RenderText_Solid (fArialFont, num, color);
  if (text == NULL) return;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = text->w;
  dstrect.h = text->h;
  r = SDL_BlitSurface (text, NULL, SScreen, &dstrect);
  SDL_FreeSurface (text);
#endif
}

void I_drawLine(int x1, int y1, int x2, int y2) {
  lineColor (SScreen, x1, y1, x2, y2, 0xffffffff);
}

void I_DrawLine(DRAWABLE *draw, int x1, int y1, int x2, int y2) {
//  I_Message ("Line (%d, %d) to (%d, %d)\n", x1, y1, x2, y2);
//  BUG: this should use the gc info of the drawable at some point
  lineColor (draw->image->surf, x1, y1, x2, y2, 0xffffffff);
}

void I_GetTextExtent (DRAWABLE *draw, char *s, int len, SIZE *line_size)
{
  // Simple case, this is currently a fixed font anyways
  line_size->cx = len * 8;
  line_size->cy = 8;
}

void I_TextOut (DRAWABLE *draw, int x, int y, char *s, int len)
{
  // BUG: use gc info for color
  // I_Message ("I_TextOut (%s)\n", s);
  stringColor (draw->image->surf, x, y, s, 0xffffffff);
}

int I_FreeDrawable (DRAWABLE *draw)
{
  SDL_FreeSurface (draw->image->surf);
  free (draw->image);
  draw->image = NULL;
  return 0;
}

void I_ClearDrawable (DRAWABLE *draw, int x1, int y1, int x2, int y2)
{
  int width = x2 - x1;
  int height = y2 - y1;
  uint32 color;
  SDL_Rect dstrect;

  dstrect.x = x1;
  dstrect.y = y1;
  dstrect.w = width;
  dstrect.h = height;

  color = SDL_MapRGB (draw->image->surf->format, 0, 0, 0);
  SDL_FillRect (draw->image->surf, &dstrect, color);
}

void I_FillRectangle (DRAWABLE *draw, int x1, int y1, int x2, int y2)
{
  int width = x2 - x1;
  int height = y2 - y1;
  SDL_Rect dstrect;

  dstrect.x = x1;
  dstrect.y = y1;
  dstrect.w = width;
  dstrect.h = height;

  SDL_FillRect (draw->image->surf, &dstrect, draw->bgcolor);
}

void I_SetFGColor (DRAWABLE *draw, int r, int g, int b)
{
  draw->fgcolor = SDL_MapRGB (draw->image->surf->format, r, g, b);
}

int I_GetDrawContext (DRAWABLE *draw)
{
  return TRUE;
}

int I_ReleaseDrawContext (DRAWABLE *draw)
{
  return TRUE;
}
