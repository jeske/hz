//
// i_video.h
//
// platform specific video routines

#ifndef HZ_I_VIDEO_H
#define HZ_I_VIDEO_H

#include <ddraw.h>
#include "i_sprtet.h"

extern LPDIRECTDRAW            lpDD;
extern DWORD                   dwTransType;
extern LPDIRECTDRAWSURFACE     lpFrontBuffer;
extern LPDIRECTDRAWSURFACE     lpBackBuffer;

typedef struct _drawable
{
  IMAGE *image;
  HDC hdc;
} DRAWABLE;

BOOL I_InitVideo( void );
void I_doBlit(RECT *dest, IMAGE *an_image);
BOOL I_vid_setpalette(const char *filename);
BOOL initAppWindow( HINSTANCE hInstance, int nCmdShow );
void    bltSplash( void );
void I_SetWindowText(char *str);
int I_CreateDrawable (RECT *src, char *name, DRAWABLE *draw);
int I_FreeDrawable (DRAWABLE *draw);
void I_GetTextExtent (DRAWABLE *draw, char *s, int len, SIZE *line_size);
void I_DrawLine(DRAWABLE *draw, int x1, int y1, int x2, int y2);
void I_TextOut (DRAWABLE *draw, int x, int y, char *s, int len);
void I_ClearDrawable (DRAWABLE *draw, int x1, int y1, int x2, int y2);
int I_GetDrawContext (DRAWABLE *draw);
int I_ReleaseDrawContext (DRAWABLE *draw);

#endif
