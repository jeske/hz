//
// Image Loading
// 

#include "image.h"
#include "i_console.h"
#include <string.h>
#include "bmp.h"

 
int load_image (IMAGEDATA *im, const char *filename)
{
  char *ch;

//  I_Message ("Loading image %s...\n", filename);
  ch = strrchr (filename, '.');
  if (ch == NULL)
  {
    I_Error ("Unknown image %s", filename);
  }
  if (!strcmp (ch, ".bmp"))
  {
    if (load_bmp (im, filename) < 0)
    {
      I_Error ("Unable to load image %s", filename);
      return (-1);
    }
  }
//  I_Message ("Loaded image %s, %dx%dx%d with %d colors\n", filename, im->width, 
//      im->height, im->colordepth, im->numcolors);

  return 0;
}

