// HZ Engine Source
// Copyright (C) 1999 by Brandon C. Long

//
// i_video.h
// X11 video routines
//

#ifndef _I_VIDEO_H_
#define _I_VIDEO_H_ 1

#include "translate.h"
#include "image.h"
#include "i_sprtet.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>

extern unsigned char *screens[2];

#define VK_ESCAPE	XK_Escape
#define VK_RETURN	XK_Return
#define VK_SPACE	XK_space
#define VK_NUMPAD1	XK_KP_1
#define VK_NUMPAD2	XK_KP_2
#define VK_NUMPAD3	XK_KP_3
#define VK_NUMPAD4	XK_KP_4
#define VK_NUMPAD5	XK_KP_5
#define VK_NUMPAD6	XK_KP_6
#define VK_NUMPAD7	XK_KP_7
#define VK_NUMPAD8	XK_KP_8
#define VK_NUMPAD9	XK_KP_9
#define VK_LEFT		XK_Left
#define VK_RIGHT	XK_Right
#define VK_UP		XK_Up
#define VK_DOWN		XK_Down
#define VK_HOME		XK_Home
#define VK_END		XK_End
#define VK_NEXT		XK_Next
#define VK_PRIOR	XK_Prior
#define VK_F1		XK_F1
#define VK_F2		XK_F2
#define VK_F3		XK_F3
#define VK_F4		XK_F4
#define VK_F5		XK_F5
#define VK_F12		XK_F12

typedef struct _drawable
{
  IMAGE *image;
  GC gc;
} DRAWABLE;

BOOL I_InitVideo (void);
BOOL I_EventLoop (void);
void I_doBlit (RECT *dest, RECT *src_cliprect, IMAGE *im); 
int I_createimage (IMAGEDATA *imd, IMAGE *image, int is_sprite);
void bltSplash (void); 
BOOL I_vid_setpalette (const char *filename);
void EraseScreen (void);
void FlipScreen (void);
void I_SetWindowText (char *title);
void bltText(char *num, int x, int y);
int I_CreateDrawable (RECT *src, char *name, DRAWABLE *draw);
int I_FreeDrawable (DRAWABLE *draw);
void I_GetTextExtent (DRAWABLE *draw, char *s, int len, SIZE *line_size);
void I_DrawLine(DRAWABLE *draw, int x1, int y1, int x2, int y2);
void I_TextOut (DRAWABLE *draw, int x, int y, char *s, int len);
void I_ClearDrawable (DRAWABLE *draw, int x1, int y1, int x2, int y2);
void I_FillRectangle (DRAWABLE *draw, int x1, int y1, int x2, int y2);
void I_SetFGColor (DRAWABLE *draw, int r, int g, int b);
int I_GetDrawContext (DRAWABLE *draw);
int I_ReleaseDrawContext (DRAWABLE *draw);

#endif /* _I_VIDEO_H_ */
