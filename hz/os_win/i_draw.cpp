// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

//
// i_draw.cpp
//
// windows drawing
//

#include <ddraw.h>       // for BltFast
#include "drawhndl.h"    // for RestoreSurfaces()
#include "i_video.h"     // for lpDD
#include "hndlmgr.h"

#include "i_system.h"
#include "i_draw.h"      

#include "ddutil.h"

int g_images_loaded = 0;

// I_loadImage(IMAGE *an_image, const char *image_name);
//
// load an image from disk into an imagerep
//
// return 0 on success, non-zero on failure

int I_loadImage(IMAGE *an_image, const char *image_name,int is_sprite) {

  image_name = i_fix_path(image_name);

		// strcpy(an_image->name,image_name);
		an_image->name = strdup (image_name);
		// load the image and put it somewhere!!!!
		an_image->surf = DDLoadBitmap(lpDD, image_name, 
				&(an_image->src), 0, 0); /* dx, dy */

		if (an_image->surf) { // did the image load correctly? 
			DDSetColorKey( an_image->surf, RGB(0,0,0) );
			an_image->width = an_image->src.right - an_image->src.left;
			an_image->height = an_image->src.bottom - an_image->src.top;

			g_images_loaded++;

			return 0; // success!
		} else {
			return 1; // failure!
		}
}

