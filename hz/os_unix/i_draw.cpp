//
// i_draw.cpp
//
// unix drawing
//

#include "i_video.h"
#include <string.h>
#include "i_system.h"   // for i_convert_path()

#include "i_draw.h"      

#include "image.h"

g_images_loaded = 0;

// I_loadImage(IMAGE *an_image, const char *image_name);
//
// load an image from disk into an imagerep
//
// return 0 on success, non-zero on failure

int I_loadImage(IMAGE *an_image, const char *dos_image_name, int is_sprite) 
{
  IMAGEDATA imdata;
  char image_name[strlen(dos_image_name) + 1];

  strcpy(image_name,dos_image_name);

  i_convert_path (image_name);
  an_image->name = strdup (image_name);
  load_image (&imdata, image_name);
  // load the image and put it somewhere!!!!
  I_createimage (&imdata, an_image, is_sprite);
  an_image->src.left = 0;
  an_image->src.top = 0;
  an_image->src.right = imdata.width;
  an_image->src.bottom = imdata.height;
  
  if (an_image->surf) { // did the image load correctly? 
    g_images_loaded++;
    return 0; // success!
  } else {
    return 1; // failure!
  }
}

