// HZ Engine Source
// Copyright (C) 1999 by Brandon C. Long

//
// i_draw.cpp
//
// unix drawing
//

#include "SDL.h"
#include <string.h>
#include "i_video.h"
#include "i_system.h"   // for i_convert_path()

#include "i_draw.h"      

#include "image.h"

int g_images_loaded = 0;

/*
 *  * Return the pixel value at (x, y)
 *   * NOTE: The surface must be locked before calling this!
 *    */
static Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
  int bpp = surface->format->BytesPerPixel;
  /* Here p is the address to the pixel we want to retrieve */
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

  switch(bpp) {
    case 1:
      return *p;

    case 2:
      return *(Uint16 *)p;

    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
	return p[0] << 16 | p[1] << 8 | p[2];
      else
	return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
      return *(Uint32 *)p;

    default:
      return 0;       /* shouldn't happen, but avoids warnings */
  }
}

// I_loadImage(IMAGE *an_image, const char *image_name);
//
// load an image from disk into an imagerep
//
// return 0 on success, non-zero on failure

int I_loadImage(IMAGE *an_image, const char *dos_image_name, int is_sprite) 
{
  IMAGEDATA imdata;
  char image_name[strlen(dos_image_name) + 1];
  SDL_Surface *temp;
  uint32 color;

  strcpy(image_name,dos_image_name);

  i_convert_path (image_name);
  an_image->name = strdup (image_name);
  temp = SDL_LoadBMP (image_name);
  if (temp == NULL) return 1;
  an_image->surf = SDL_DisplayFormat (temp);
  SDL_FreeSurface(temp);
  an_image->src.left = 0;
  an_image->src.top = 0;
  if (an_image->surf) { // did the image load correctly? 
    g_images_loaded++;
    an_image->src.right = an_image->surf->w;
    an_image->src.bottom = an_image->surf->h;
    if (is_sprite)
    {
      SDL_SetAlpha (an_image->surf, 0, SDL_ALPHA_TRANSPARENT);
      SDL_LockSurface(an_image->surf);
      color = getpixel (an_image->surf, 0, 0);
      SDL_UnlockSurface(an_image->surf);
      if (SDL_SetColorKey (an_image->surf, SDL_SRCCOLORKEY, color))
      {
	return 1;
      }
    }
    return 0; // success!
  } else {
    return 1; // failure!
  }
}

