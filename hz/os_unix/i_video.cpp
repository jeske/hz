
#include "config.h"
#include "translate.h"
#include "i_console.h"
#include "i_draw.h"
#include "i_video.h"
#include "i_system.h"
#include "image.h"
#include "donuts.h" // bIsActive 
#include "main.h" // realScreenView
#include "game.h" // setup_game

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XShm.h>
#ifdef LINUX
extern "C" {   
  int XShmGetEventBase( Display* dpy ); // problems with g++?
}
#endif

#define SCREENWIDTH 640
#define SCREENHEIGHT 480

Display* X_display=0;
Window X_mainWindow;
Pixmap pBackBuffer;
Colormap X_cmap;
Visual* X_visual;
GC X_gc, X_sprite_gc, X_black_gc;
XEvent X_event;
XFontStruct *X_font;
int X_screen;
XVisualInfo *X_visualinfo;
XImage* image;
int X_width;
int X_height;
int X_depth;

// MIT SHared Memory extension.
BOOL doShm;
XShmSegmentInfo X_shminfo;
int X_shmeventtype;
unsigned char *screens[2];

void I_Quit (void)
{
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
  XSetWindowAttributes attribs;
  XGCValues xgcvalues;
  int valuemask;
  static int firsttime=1;
  XVisualInfo vinfo_template;

  signal(SIGINT, (void (*)(int)) I_Quit);

  X_width = SCREENWIDTH;
  X_height = SCREENHEIGHT;
  ScreenX = X_width;
  ScreenY = X_height;

  // open the display
  X_display = XOpenDisplay(displayname);
  if (!X_display)
  {
    if (displayname)
      I_Error("Could not open display [%s]", displayname);
    else
      I_Error("Could not open display (DISPLAY=[%s])",
	  getenv("DISPLAY"));
  }

  // use the default visual 
  X_screen = DefaultScreen(X_display);
  X_visualinfo = XGetVisualInfo (X_display, VisualNoMask, &vinfo_template, &n);
  if (X_visualinfo == NULL || !n)
      I_Error ("Error getting visual info");
  else
    I_Message ("Found %d visuals.\n", n);
  /*
  if (!XMatchVisualInfo(X_display, X_screen, 8, PseudoColor,
      &X_visualinfo))
      I_Error("Currently only supports 256-color PseudoColor screens");
   */
  X_visual = X_visualinfo->visual;

  X_depth = X_visualinfo->depth;
  I_Message ("Colordepth is %d\n", X_depth);

  // check for the MITSHM extension
//  doShm = XShmQueryExtension(X_display);

  // even if it's available, make sure it's a local connection
  if (doShm)
  {
    if (!displayname) displayname = (char *) getenv("DISPLAY");
    if (displayname)
    {
      d = displayname;
      while (*d && (*d != ':')) d++;
      if (*d) *d = 0;
      if (!(!strcasecmp(displayname, "unix") || !*displayname))
	doShm = false;
    }
  }

  if (doShm)
    I_Message ("Using MITSHM extension\n");

  // create the colormap
  X_cmap = XCreateColormap(X_display, RootWindow(X_display, X_screen), 
      X_visual, AllocNone);

  // setup attributes for main window
  attribmask = CWEventMask | CWColormap | CWBorderPixel | CWBackPixel;
  attribs.event_mask = KeyPressMask | KeyReleaseMask
    | PointerMotionHintMask
    | ButtonPressMask | ButtonReleaseMask
    | ExposureMask | VisibilityChangeMask | DestroyNotify;

  attribs.colormap = X_cmap;
  attribs.border_pixel = 0;

  // create the main window
  X_mainWindow = XCreateWindow(X_display, RootWindow(X_display, X_screen),
      x, y, X_width, X_height, 0, // borderwidth
      X_depth, // depth
      InputOutput, X_visual, attribmask, &attribs );

  // Create the back buffer 
  pBackBuffer = XCreatePixmap (X_display, RootWindow (X_display, X_screen),
      X_width, X_height, X_depth);


//  XDefineCursor(X_display, X_mainWindow,
//      createnullcursor( X_display, X_mainWindow ) );

  if ((X_font = XLoadQueryFont (X_display, "fixed")) == NULL)
  {
    I_Error ("Unable to load font 'fixed'");
  }
  // create the GC
  valuemask = GCGraphicsExposures | GCFont | GCForeground | GCBackground;
  xgcvalues.graphics_exposures = False;
  xgcvalues.font = X_font->fid;
  xgcvalues.foreground = WhitePixel(X_display, DefaultScreen(X_display));
  xgcvalues.background = BlackPixel(X_display, DefaultScreen(X_display));

  X_gc = XCreateGC (X_display, X_mainWindow, valuemask, &xgcvalues);
  X_sprite_gc = XCreateGC (X_display, X_mainWindow, valuemask, &xgcvalues);

  xgcvalues.foreground = xgcvalues.background;
  X_black_gc = XCreateGC (X_display, X_mainWindow, valuemask, &xgcvalues);

  // The window manager about the window
  {
    XSizeHints hints;
    XWMHints wmhints;
    char *window_name = "Herzog Zwei";
    char *icon_name = "xhz";
    XTextProperty windowName, iconName;

    hints.flags = PSize | PMaxSize | PMinSize;
    hints.min_width = hints.max_width = hints.width = SCREENWIDTH;
    hints.min_height = hints.max_height = hints.height = SCREENHEIGHT;
    wmhints.input = True;
    wmhints.flags = InputHint;
    XStringListToTextProperty(&window_name, 1, &windowName);
    XStringListToTextProperty(&icon_name  , 1, &iconName);
    XSetWMProperties(X_display, X_mainWindow, &windowName, &iconName,
	NULL, 0, &hints, &wmhints, NULL);
  }


  // map the window
  XMapWindow(X_display, X_mainWindow);

#if 0
  // wait until it is OK to draw
  oktodraw = 0;
  while (!oktodraw)
  {
    XNextEvent(X_display, &X_event);
    if (X_event.type == Expose
	&& !X_event.xexpose.count)
    {
      oktodraw = 1;
    }
  }
#endif

  // grabs the pointer so it is restricted to this window
  /*
  if (grabMouse)
    XGrabPointer(X_display, X_mainWindow, True,
	ButtonPressMask|ButtonReleaseMask|PointerMotionMask,
	GrabModeAsync, GrabModeAsync,
	X_mainWindow, None, CurrentTime);
   */

#if 0
  if (doShm)
  {

    X_shmeventtype = XShmGetEventBase(X_display) + ShmCompletion;

    // create the image
    image = XShmCreateImage(X_display, X_visual, 8, ZPixmap, 0, &X_shminfo, 
	X_width, X_height );

//    grabsharedmemory(image->bytes_per_line * image->height);


    // UNUSED
    // create the shared memory segment

    // X_shminfo.shmid = shmget (IPC_PRIVATE,
    // image->bytes_per_line * image->height, IPC_CREAT | 0777);
    // if (X_shminfo.shmid < 0)
    // {
    // I_Perror("");
    // I_Error("shmget() failed in InitGraphics()");
    // }
    // fprintf(stderr, "shared memory id=%d\n", X_shminfo.shmid);
    // attach to the shared memory segment
    // image->data = X_shminfo.shmaddr = shmat(X_shminfo.shmid, 0,
    // 0);


    if (!image->data)
    {
      I_Perror("shmat() failed in InitGraphics()");
    }

    // get the X server to attach to it
    if (!XShmAttach(X_display, &X_shminfo))
      I_Error("XShmAttach() failed in InitGraphics()");

  }
  else
  {
    int divisor = X_depth / 8;

    image = XCreateImage(X_display, X_visual, X_depth, ZPixmap, 0, 
	(char*)malloc(X_width * X_height * divisor), X_width, X_height, X_depth, X_width *2);
    XPutImage (X_display, X_mainWindow, X_gc, image, 0, 0, 0, 0, X_width, X_height);


  }

//  if (multiply == 1)
    screens[0] = (unsigned char *) (image->data);
//  else
//    screens[0] = (unsigned char *) malloc (SCREENWIDTH * SCREENHEIGHT);

#endif

    bIsActive = 1;

}

#define UTIMER 50000            /* how long between updates (useconds) */

int I_EventLoop()
{
  XEvent event;
  KeySym key;
  IN_EVENT ev;
//  int fd = ConnectionNumber(xcpDisplay);
//  fd_set rd_set;
//  struct timeval sleepfor;

  //  while (XEventsQueued(X_display, QueuedAfterReading)) 
  
//  sleepfor.tv_sec = 0;
//  sleepfor.tv_usec = UTIMER;
#if 0
  if (!XEventsQueued(X_display, QueuedAfterReading) && 
      (ProgramState != PS_SPLASH))
    return TRUE;
#endif

  while (XEventsQueued(X_display, QueuedAfterReading) || (ProgramState == PS_SPLASH))
  {
  XNextEvent (X_display, &event);
//  I_Message ("Handling X Events\n");
  switch (event.type)
  {
    case VisibilityNotify:
      if (event.xvisibility.state == VisibilityFullyObscured)
      {
	bIsActive = 0;
	bMouseVisible = TRUE;
      }
      else
      {
	if (!bIsActive)
	{
	  bIsActive = 1;
	  lastTickCount = i_time_ms();
	  bSpecialEffects = FALSE;
	}
      }
      break;

    case Expose:    
      if (event.xexpose.count == 0)
      {
	bIsActive = 1;
	// XClearWindow (X_display, X_mainWindow);
	// FlipScreen();
      }
      break;
      
    case KeyPress:

      if (realScreenView) {

	ev.dev_type = DT_KEYBOARD;
	ev.dev.keyboard.mask = (enum keyboard_mask_enum) (KM_KEYDOWN);
	key = XKeycodeToKeysym(X_display, event.xkey.keycode, event.xkey.state & ShiftMask);
	ev.dev.keyboard.mask = KM_KEYDOWN;
	ev.dev.keyboard.vk_code = key;
	if (key >= XK_space && key <= XK_asciitilde)
	{
	  ev.dev.keyboard.mask |= KM_ASCII_KEY;
	  key = key - XK_space + ' ';
	}
	if (key == XK_Tab)
	{
	  ev.dev.keyboard.mask |= KM_ASCII_KEY;
	  key = 9;
	}
	if (key == XK_Return)
	{
	  ev.dev.keyboard.mask |= KM_ASCII_KEY;
	  key = '\n';
	}
	if (key == XK_BackSpace)
	{
	  ev.dev.keyboard.mask |= KM_ASCII_KEY;
	  key = 8;
	}

//	I_Message ("Got Key %d/%d at %lu\n", key, event.xkey.state, i_time_ms());
	ev.dev.keyboard.ascii_code = key;
	realScreenView->inputEvent(&ev);
      }

      switch (key) {
	case VK_RETURN:
	case '\n':
	  if (ProgramState == PS_SPLASH) {
//	    I_Message ("VK_RETURN at %lu\n", i_time_ms());
	    ProgramState = PS_BEGINREST;
	    DrawDisplayList();
	    setup_game();
	    XFillRectangle (X_display, pBackBuffer, X_black_gc, 0, 0, X_width, 
		X_height);
	  }
	  break;
	case VK_ESCAPE:
	case VK_F12:
	  return False;
      }

      break;

    case KeyRelease:
      // if there is a screen, then pass the key
      if (realScreenView) {

	ev.dev_type = DT_KEYBOARD;
	key = XKeycodeToKeysym(X_display, event.xkey.keycode, 0);
	ev.dev.keyboard.mask = KM_KEYUP;
	ev.dev.keyboard.vk_code = key;
	if (key >= XK_space && key <= XK_asciitilde)
	{
	  // Currently, we don't set KM_ASCII_KEY on KeyRelease or
	  // otherwise any keys interpreted in handleMVInput() get done
	  // twice since it doesn't check for KeyDown only
	  // ev.dev.keyboard.mask |= KM_ASCII_KEY;
	  key = key - XK_space + ' ';
	}
	if (key == XK_Tab)
	{
	  key = 9;
	}
	if (key == XK_Return)
	{
	  key = '\n';
	}
//	if (key >= 'A' && key <= 'Z')
//	  key = key - 'A' + 'a';
//	I_Message ("Got Key %d at %lu\n", key, i_time_ms());
	ev.dev.keyboard.ascii_code = key;
	realScreenView->inputEvent(&ev);
      }
      break;

    case MotionNotify:
    case ButtonPress:
      if (realScreenView)
      {
	Window rw, cw;
	int xr, yr, xw, yw;
	unsigned int kbstat;
	unsigned long int mask = 0;

	if (XQueryPointer (X_display, X_mainWindow, &rw, &cw, &xr, &yr, &xw, &yw, 
	    &kbstat))
	{
	  ev.dev_type = DT_MOUSE;
	  ev.dev.mouse.xpos = xw;
	  ev.dev.mouse.ypos = yw;
	  if (event.type == ButtonPress)
	  {
	    if (event.xbutton.button == Button1) {
	      mask |= MS_L_BUTTON;
	    }
	    if (event.xbutton.button == Button2) {
	      mask |= MS_M_BUTTON;
	    }
	    if (event.xbutton.button == Button3) {
	      mask |= MS_R_BUTTON;
	    }
	  }
	  ev.dev.mouse.mask =  (enum mouse_mask_enum) mask;
	  realScreenView->inputEvent (&ev);
	}
      }
      break;
    case DestroyNotify:
      return FALSE;
    default:
      break;
  }
  }
  return TRUE;
}

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

int I_CreateDrawable (RECT *src, char *name, DRAWABLE *draw)
{
  int width = src->right - src->left;
  int height = src->bottom - src->top;

  draw->image = (IMAGE *) malloc (sizeof (IMAGE));
  draw->image->name = strdup (name);
  draw->image->src = *src;
  draw->image->surf = XCreatePixmap (X_display, RootWindow (X_display, 
      DefaultScreen (X_display)), width, height, 
      DefaultDepth (X_display, DefaultScreen (X_display)));
  draw->image->mask = 0;
  draw->gc = X_gc;

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
  
  // if there is no source cliprect, use the image.
  if (src_cliprect == NULL) {
    src_cliprect = & all;
  }

#if 0
  if (dest->top == 0 && dest->left == 0)
  {
    I_Message ("I_doBlit %s %dx%d (%d,%d)\n", im->name, width, height, dest->top, dest->left);
  }
#endif

//  return XPutImage (X_display, X_mainWindow, X_gc, im->surf, 0, 0, 
//      dest->left, dest->top, width, height);

  if (im->mask != 0)
  {
    // Sprite needs mask!
    XSetClipOrigin (X_display, X_sprite_gc, dest->left, dest->top);
    XSetClipMask (X_display, X_sprite_gc, im->mask);
    XCopyArea (X_display, im->surf, pBackBuffer, X_sprite_gc, 
        src_cliprect->left, src_cliprect->top, 
        width, height, 
        dest->left, dest->top);
  }
  else
  {
    XCopyArea (X_display, im->surf, pBackBuffer, X_gc, 
        src_cliprect->left, src_cliprect->top, 
        width, height, 
        dest->left, dest->top);
  }
  // return TRUE;
  return;
}

void bltSplash (void)
{
  static IMAGE im = {NULL, 0, 0, {0,0,0,0}};
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
      FlipScreen ();
    }
    else
      I_Error ("Error loading splash.bmp");
  }
  else
  {
    I_doBlit (&dest, NULL, &im);
    FlipScreen ();
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

void EraseScreen( void )
{
//  XClearWindow (X_display, X_mainWindow);
//  XFlush (X_display);
  XFillRectangle (X_display, pBackBuffer, X_black_gc, 0, 0, X_width, 
      X_height);
}

void FlipScreen( void )
{
//  I_Message ("FlipScreen()\n");
  XCopyArea (X_display, pBackBuffer, X_mainWindow, X_gc, 0, 0, X_width, 
      X_height, 0, 0);
  XSync (X_display, FALSE);
//  XFlush (X_display);
}

void I_SetWindowText (char *title)
{
  char *window_name = title;
  char *icon_name = title;
  XTextProperty windowName, iconName;

  XStringListToTextProperty(&window_name, 1, &windowName);
  XStringListToTextProperty(&icon_name  , 1, &iconName);
  XSetWMProperties(X_display, X_mainWindow, &windowName, &iconName,
      NULL, 0, NULL, NULL, NULL);
}

void bltText( char *num, int x, int y ) {
//  I_Message ("(%d, %d) %s\n", x, y, num);

  XDrawString (X_display, pBackBuffer, X_gc, x, y, num, strlen(num));
}

void I_drawLine(int x1, int y1, int x2, int y2) {
  XDrawLine (X_display, pBackBuffer, X_gc, x1, y1, x2, y2);
}

void I_DrawLine(DRAWABLE *draw, int x1, int y1, int x2, int y2) {
//  I_Message ("Line (%d, %d) to (%d, %d)\n", x1, y1, x2, y2);
  XDrawLine (X_display, draw->image->surf, draw->gc, x1, y1, x2, y2);
}

void I_GetTextExtent (DRAWABLE *draw, char *s, int len, SIZE *line_size)
{
  // Simple case, this is currently a fixed font anyways
  line_size->cx = len * X_font->max_bounds.width;
  line_size->cy = X_font->ascent + X_font->descent;
}

void I_TextOut (DRAWABLE *draw, int x, int y, char *s, int len)
{
  XDrawString (X_display, draw->image->surf, draw->gc, x, y + X_font->ascent + X_font->descent, s, len);
}

int I_FreeDrawable (DRAWABLE *draw)
{
  XFreePixmap (X_display, draw->image->surf);
  if (draw->image->mask != 0)
  {
    XFreePixmap (X_display, draw->image->mask);
  }
  free (draw->image);
  draw->image = NULL;
}

void I_ClearDrawable (DRAWABLE *draw, int x1, int y1, int x2, int y2)
{
  int width = x2 - x1;
  int height = y2 - y1;

  XFillRectangle (X_display, draw->image->surf, X_black_gc, x1, y1, width, 
      height);
}

void I_FillRectangle (DRAWABLE *draw, int x1, int y1, int x2, int y2)
{
  int width = x2 - x1;
  int height = y2 - y1;

  XFillRectangle (X_display, draw->image->surf, X_gc, x1, y1, width, height);
}

void I_SetFGColor (DRAWABLE *draw, int r, int g, int b)
{
   XSetForeground (X_display, draw->gc, ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3));
}

int I_GetDrawContext (DRAWABLE *draw)
{
  return TRUE;
}

int I_ReleaseDrawContext (DRAWABLE *draw)
{
  return TRUE;
}
