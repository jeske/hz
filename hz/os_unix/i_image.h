// HZ Engine Source
// Copyright (C) 1999 by Brandon C. Long

//
// i_image.h
// This is the os dependent part of the image
//
#ifndef HZ_I_IMAGE_H
#define HZ_I_IMAGE_H

#include <X11/Xlib.h>
#include "translate.h"

// IMAGE DATA
typedef struct {
  char *name;
  Pixmap surf;
  Pixmap mask;
  RECT src;
} IMAGE;

#endif
