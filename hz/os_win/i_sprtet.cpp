//
// i_sprtet.cpp
//
// windows specific version of the sprite draw interface
//

#include <ddraw.h> // for RECT, get rid of this!
#include "i_video.h" // lpBackBuffer, lpDD
#include "..\spritet.h"
#include "..\donuts.h"
#include "..\VConsole.h" // for dbgMsg();

void SpriteType::doBlit(RECT *dest, IMAGE *an_image) {
	HRESULT ddrval;
	do {
				
			/*
			 *	ddrval = lpBackBuffer->BltFast(x,y, an_image->surf, 
			 *	&(an_image->src), dwTransType  | DDBLTFAST_WAIT );
			 */
				
			ddrval = lpBackBuffer->Blt(dest, an_image->surf, 
							&(an_image->src), dwTransType | DDBLT_KEYSRC , NULL);

			if (ddrval != DD_OK) {
				if( ddrval == DDERR_SURFACELOST ) {
					an_image->surf->Restore();
				} else {
					dbgMsg(c_error,"failed drawing image [%s] (ERR = %d)",an_image->name, ddrval);
				}

			/*
			 * else if ( ddrval != DDERR_WASSTILLDRAWING ) {
			 *    dbgMsg(c_error,"DDERR_WASSTILLDRAWING");
			 *    Sleep(10);
			 *    fail_count++;
			 *    if (fail_count > 20) {
			 *        return;
			 *    }
			 * }
			 */

			}
		} while (ddrval == DDERR_WASSTILLDRAWING);
}

void SpriteType::loadImage(IMAGE *an_image, const char *image_name) {

		an_image->name = strdup(image_name);
		// load the image and put it somewhere!!!!
		an_image->surf = DDLoadBitmap(lpDD, image_name, &(an_image->src), 0, 0); /* dx, dy */

		if (an_image->surf) { // did the image load correctly? 
			DDSetColorKey( an_image->surf, CLR_INVALID );
		}
}
