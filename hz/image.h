//
// images.h
// loaded images
//

#ifndef _IMAGES_H_
#define _IMAGES_H_ 1

#ifdef OS_UNIX
#include "translate.h"
#endif

typedef struct _imagedata
{
  unsigned int height;
  unsigned int width;
  unsigned int colordepth;
  unsigned int numcolors;
  BYTE *data;
  RGBQUAD *palette;
} IMAGEDATA;
 
extern int load_image (IMAGEDATA *, const char *filename); 

#endif /* _IMAGES_H_ */
