// HZ Engine Source
// Copyright (C) 1998 by David W. Jeske

/*
 * osdep.h
 *
 * required os dependent functions.
 *
 * All os_* ports must implement these functions.
 *
 */
#ifndef HZ_OSDEP_H
#define HZ_OSDEP_H

#include <i_image.h> // this is where the platform dependent IMAGE structure is defined
#include <i_video.h>



BOOL I_InitVideo( void );			// setup the video 
void I_SetWindowText(char *str);	// set the window title

void    bltSplash( void );			// blit the splash (this should disappear)


BOOL I_vid_setpalette(const char *filename);	// set the 8bit palette (if in 8bit mode)
void bltText( char *num, int x, int y );		// draw the specified text at (x,y)
void I_drawLine(int x1, int y1, int x2, int y2);// draw a line from x1,y1 to x2,y2

int I_loadImage(IMAGE *an_image, const char *image_name, int is_sprite); // load an IMAGE
void I_doBlit(RECT *dest, RECT *src_cliprect, IMAGE *an_image);		// blit an IMAGE at a destination

unsigned long int i_time_ms(void); 

int     RestoreSurfaces( void );
void    EraseScreen( void );
void    FlipScreen( void );

void I_FillRectangle (DRAWABLE *draw, int x1, int y1, int x2, int y2);
void I_SetFGColor (DRAWABLE *draw, int r, int g, int b);

#endif
