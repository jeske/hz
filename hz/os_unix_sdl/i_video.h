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
#include "SDL.h"

extern unsigned char *screens[2];

#define VK_ESCAPE	SDLK_ESCAPE
#define VK_RETURN	SDLK_RETURN
#define VK_SPACE	SDLK_SPACE
#define VK_NUMPAD1	SDLK_KP1
#define VK_NUMPAD2	SDLK_KP2
#define VK_NUMPAD3	SDLK_KP3
#define VK_NUMPAD4	SDLK_KP4
#define VK_NUMPAD5	SDLK_KP5
#define VK_NUMPAD6	SDLK_KP6
#define VK_NUMPAD7	SDLK_KP7
#define VK_NUMPAD8	SDLK_KP8
#define VK_NUMPAD9	SDLK_KP9
#define VK_LEFT		SDLK_LEFT
#define VK_RIGHT	SDLK_RIGHT
#define VK_UP		SDLK_UP
#define VK_DOWN		SDLK_DOWN
#define VK_HOME		SDLK_HOME
#define VK_END		SDLK_END
#define VK_NEXT		SDLK_PAGEUP
#define VK_PRIOR	SDLK_PAGEDOWN
#define VK_F1		SDLK_F1
#define VK_F2		SDLK_F2
#define VK_F3		SDLK_F3
#define VK_F4		SDLK_F4
#define VK_F5		SDLK_F5
#define VK_F12		SDLK_F12

typedef struct _drawable
{
  IMAGE *image;
  uint32 fgcolor;
  uint32 bgcolor;
//  GC gc;
} DRAWABLE;

BOOL I_InitVideo (void);
BOOL I_EventLoop (void);
void I_doBlit (RECT *dest, RECT *src_cliprect, IMAGE *im); 
int I_createimage (IMAGEDATA *imd, IMAGE *image, int is_sprite);
void bltSplash (void); 
BOOL I_vid_setpalette (const char *filename);
void I_EraseScreen (void);
void I_FlipScreen (void);
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
