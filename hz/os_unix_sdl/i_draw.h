// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

// i_draw.h
//
// os dependent text draw function... used for basic stuff like
// the framerate display
//
#ifndef HZ_I_DRAW_H
#define HZ_I_DRAW_H

#include "i_sprtet.h"

extern int g_images_loaded;

int I_loadImage(IMAGE *an_image, const char *image_name, int is_sprite);
void I_drawLine(int x1, int y1, int x2, int y2);
#endif
