//
// i_sprtet.cpp
//
// unix/X11 specific version of the sprite draw interface
//

#include "translate.h" // for RECT
#include "i_video.h" 
#include "spritet.h"
#include "i_sprtet.h"
#include "i_draw.h"
#include "i_console.h"
#include "osdep.h"

void SpriteType::doBlit (RECT *dest, IMAGE *an_image) 
{
  I_doBlit (dest, NULL, an_image);
}

void SpriteType::loadImage(IMAGE *an_image, const char *image_name) 
{
  I_loadImage (an_image, image_name, 1);
}
