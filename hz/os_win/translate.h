//
// translate.h
//
// create win32isms for other platforms

#ifndef _TRANSLATE_H_
#define _TRANSLATE_H_ 1

#include "config.h"

typedef int BOOL;
#define FALSE 0
#define TRUE 1

typedef struct _rect 
{
  int left, right;
  int top, bottom;
} RECT;

typedef struct _point
{
  int x, y;
} POINT;

typedef struct _rgbquad
{
  int red;
  int green;
  int blue;
  int reserved;
} RGBQUAD;

typedef struct _size
{
  int cx;
  int cy;
} SIZE;


#if 0
#define HPEN	int
#define HBRUSH	int
#define HWND	int
#define GUID	int
#define HRESULT int
#define LPDIRECTDRAWSURFACE XImage
#define LPDIRECTDRAWPALETTE Colormap

#endif

#define ULONG uint32
#define SCODE uint32
#define FAR
#define LPVOID void *
#define WORD uint16
#define DWORD uint32
#define LONG int32
#define BYTE uint8


BOOL I_InitVideo (void);
BOOL I_vid_setpalette (const char *filename);

#endif /* _TRANSLATE_H_ */
