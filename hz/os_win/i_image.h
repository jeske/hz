// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

/*
 * i_image.h
 *
 */

#ifndef HZ_I_IMAGE_H
#define HZ_I_IMAGE_H

#include <ddraw.h>

// IMAGE DATA
typedef struct {
	// this MUST be here, it's publicly accessed data!
	char *name;			// image name (?? should this disappear?)
	int width, height;		// image dimensions


	// this stuff is platform dependent and shouldn't be touched outside the
	// os_* directory
	LPDIRECTDRAWSURFACE surf;
	RECT src;
} IMAGE;


#endif
