//
// Map.cpp
//
// handles the tiled map stuff.. 
//
//   Map.cpp: not particularly clean, and guilty of premature optimization. I
//     originally wrote this in C and then "slurped" it up into a class. The
//     only thing nifty about it is the way the data orginization works for
//     the sprites. There is a pointer for every "tile" on the map (where a
//     tile is just an arbitrary size which happens to correspond with the
//     ground tile size) That pointer points to a list of the objects whose
//     upper-left corner is on this tile. This is my space partitioning to
//     quickly do collision detection, on-screen decisions for rendering
//     sprites, and some other things.
// 
//     The code that handles drawing the map to the screen is in here too,
//     in a class called ViewPort. I have the code which keeps the ship       
//     "in the box" in here in ViewPort::doFollowTick(). I'm not sure
//     that it really belongs here.
   
#include <stdio.h>

#include "osdep.h"
#ifdef OS_WIN
#include "drawhndl.h" // RestoreSurfaces()
#endif
#include "i_system.h" // CleanupAndExit()
#include "i_draw.h" // I_loadImage()
#include "i_video.h"

#include "donuts.h" // for "extern"s of DD surfaces
#include "sprite.h" // SpriteTmplManager
#include "main.h" // extern ConsoleView *consoleView;
#include "game.h" // extern Sprite *shipSprite;
#include "map.h"



struct curloc_struct test_view; // this should be instance data!

/*
 * Map::Map(int gr, int gc, TileSet *aTileSet)
 *
 * a Map constructor, gr = grid_rows, gc = grid_columns, TileSet is
 * a pre-setup TileSet. It will create a random map of the specified
 * size using all of the tiles in the TileSet.
 *
 */


Map::Map(int gr, int gc, TileSet *aTileSet) {
	grid_rows = gr;
	grid_cols = gc;

	if ((myTiles = aTileSet) == NULL) {
		// there is no tileset!!!!
	} else {
		map_width = grid_cols * myTiles->tile_width;
		map_height = grid_rows * myTiles->tile_height;
	}
	
    if (this->allocMap()) {
		// bail!
	}

	if (this->setup()) {
		// bail
	}

}

Map::~Map() {
	this->deallocMap();
}

int Map::allocMap() {
	int iter;
	int num_cells = grid_rows * grid_cols;	
	unsigned short int *til_walker;
	LPDBLNODE *obj_walker;

	if (!(objects_rowindex = (LPDBLNODE **)malloc(sizeof(LPDBLNODE *) * grid_rows))) {
		exit(1); // malloc failed
	}

	if (!(tilemap_rowindex = (unsigned short int **)malloc(sizeof(unsigned short int *) * grid_rows))) {
		exit(1); // malloc failed
	}

	
	if (!(obj_walker = objects = (LPDBLNODE *)malloc(sizeof(LPDBLNODE) * (num_cells)))) {
		exit(1); // malloc failed
	}

	if (!(til_walker = tilemap = (unsigned short int *)malloc(sizeof(unsigned short int) * (num_cells)))) {
		exit(1); // malloc failed
	}

	
	for (iter = 0;iter < grid_rows;iter++) {
		objects_rowindex[iter] = obj_walker;
		obj_walker += grid_cols;

		tilemap_rowindex[iter] = til_walker;
		til_walker += grid_cols;
	}

	return 0;
}

Map::deallocMap() {
	free(objects_rowindex);
	free(objects);
	free(tilemap_rowindex);
	free(tilemap);

	return 0;
}

/*
 * Map::setup()
 *
 * setup the final parameters for using the map (random)
 */
void Map::setSquare(int x, int y, int tile_type) {
	if ((x < grid_cols) && (y < grid_rows)) {
		(tilemap_rowindex[y])[x] = tile_type;
	}
}

int Map::getSquare(int x, int y) {
	if ((x < grid_cols) && (y < grid_rows)) {
		return ((tilemap_rowindex[y])[x]);
	}

	return 0;
}

Map::setup() {
	int x,y;
	int numtiles = 3;

	for (y=0;y<grid_rows;y++) {
		for (x=0;x<grid_cols;x++) {
			(tilemap_rowindex[y])[x] = 0;  // set all to tile type 0
			(objects_rowindex[y])[x] = NULL;
		}
	}		

	return 0;
}


void ViewPort::followSprite(Sprite *sp) {
	myFollowSprite = sp;
}

ViewPort::ViewPort(int x, int y, int w, int h) : View(x,y,w,h){

	// view_width = width; view_height = height;
	// myMap = aMap;
	// myTiles = myMap->myTiles;
	myMap = NULL; 
	myTiles = NULL;
	view_width = w;
	view_height = h;

	highlight_tile_x = highlight_tile_y = -1; // none!

	myFollowSprite = NULL;

	// view stuff
	// level = lev;  // what is this for???
	wantsInputFocus = TRUE;
	
	//	this->computeSizeVars();

	// Check to make sure that the viewport is at least as big as the map!!!
	// FIX!

}

void ViewPort::setMap(int width, int height, Map *aMap) {
	myMap = aMap;
	myTiles = aMap->myTiles;
	
	
	//view_width = width;
	//view_height = height;

	this->computeSizeVars();
}

/*
 * set the current location, return 1 means you were clipped 
 */

int ViewPort::setCurLoc(struct curloc_struct *loc) {
	int retval=0;

	// Clip the location first...

	if (loc->upper_left_x < 0)  {
		loc->upper_left_x = 0;
		retval = 1;
	} else {
		if (loc->upper_left_x + view_width > myMap->map_width) {
			loc->upper_left_x = myMap->map_width - view_width;
			retval = 1;
		}
	}

	if (loc->upper_left_y < 0) {
		loc->upper_left_y = 0;
		retval = 1;
	} else {
		if (loc->upper_left_y + view_height > myMap->map_height) {
			loc->upper_left_y = myMap->map_height - view_height;
			retval = 1;
		}
	}	

	// Now set our curloc to be the given curloc


	
	this->upper_left_x = loc->upper_left_x;
	this->upper_left_y = loc->upper_left_y;
	return retval;
}


/*
 * void ViewPort::computeSizeVars(void)
 *
 * Precompute all the necessary variables for painting the viewport
 */

void ViewPort::computeSizeVars(void) {

	// compute these from the pixel view width!
		view_width_tiles = (view_width / myTiles->tile_width);
		view_height_tiles = (view_height / myTiles->tile_height);

		view_width_extra = view_width - (view_width_tiles * myTiles->tile_width);
		view_height_extra = view_height - (view_height_tiles * myTiles->tile_width);

	// compute the "sprite clip" regions.. in other words, the "tile"
	// area where we have to clip sprites... Really, this is just the
	// number of (x/y) tiles completely cover the "max_sprite" size.

	sprite_clip_tiles_x = (spriteTmplManager->max_sprite.width / myTiles->tile_width);
	sprite_clip_tiles_y = (spriteTmplManager->max_sprite.height / myTiles->tile_height);


	// compute the "screen" coordinates of our bounds

	viewPort_left = my_dimension.x;
	viewPort_top = my_dimension.y;
	viewPort_right = viewPort_left + view_width;
	viewPort_bottom = viewPort_top + view_height;

	// compute the "bounding box" region offsets (relative to the upper left corner)

	bb_left = view_width / 8;
	bb_top = view_height / 8;
	bb_right = view_width - bb_left - myTiles->tile_width; // the 48 here is the width of the main
	bb_bottom = view_height - bb_top - myTiles->tile_height; // shipsprite

    // also need to compute the "partial tile" information for the left, right, top, bottom
	// and corners...


}




void ViewPort::doFollowTick(unsigned int tickDiff) {
	
    // update the view region
        //DL.posx += DL.velx * (double)tickDiff;
        //DL.posy += DL.vely * (double)tickDiff;
		// we need to bound the view to the shiplocation
		
		//test_view.upper_left_x = shipSprite->posx - 50;
		//test_view.upper_left_y = shipSprite->posy - 50;
	if (myFollowSprite) {
			if (myFollowSprite->velx != 0.0) {
				test_view.upper_left_x += (myFollowSprite->velx) * ((tickDiff >> 1) + tickDiff);
			} else {
				
			}

			if (myFollowSprite->vely != 0.0) {
				test_view.upper_left_y += (myFollowSprite->vely) * ((tickDiff >> 1) + tickDiff);	
			} else {
			}
	

		
		// try to make sure we can keep the ship inside the "bound box"

			if (myFollowSprite->posx > (test_view.upper_left_x + bb_right)) {
				test_view.upper_left_x += (myFollowSprite->posx - (test_view.upper_left_x + bb_right));
			} else if (myFollowSprite->posx < (test_view.upper_left_x + bb_left)) {
				test_view.upper_left_x += (myFollowSprite->posx - (test_view.upper_left_x + bb_left));
			}

			if (myFollowSprite->posy > (test_view.upper_left_y + bb_bottom)) {
				test_view.upper_left_y += (myFollowSprite->posy - (test_view.upper_left_y + bb_bottom));
			} else if (myFollowSprite->posy < (test_view.upper_left_y + bb_top)) {
				test_view.upper_left_y += (myFollowSprite->posy - (test_view.upper_left_y + bb_top));
			}

	
		// this will set the viewport view and clip...
			this->setCurLoc(&test_view);
	}
}



static int once_in_a_while = 0;
#ifndef MAX
#define MAX(x,y) (x > y ? x : y)
#endif
#ifndef MIN
#define MIN(x,y) (x > y ? y : x)
#endif

void ViewPort::draw_curview() {
	int x_iter,y_iter,num_x = (VIEW_TILE_WIDTH), num_y = (VIEW_TILE_HEIGHT); // width/height in tiles

	int tile_x,tile_y; // the map location via tile coordinates
	int start_tile_x, start_tile_y; // the map location of the upper left via tile coordinates
	int offset_x, offset_y; // the offset within the tile via
	int grid_width = myTiles->tile_width;
	int grid_height = myTiles->tile_height;
	RECT src,dest; // source and destination rects, the source will be constant
	RECT save_dest;
	LPDBLNODE cur_obj;
	int tile_type;
	
	// reset statistics
	draw_sprite_count = 0;
	draw_sprite_clipped_count = 0;

	lua_beginblock();

	// first, find the start row and col tile number

	start_tile_x = tile_x = (int)upper_left_x / grid_width;
	offset_x = ((int)upper_left_x) % grid_width;
	
	start_tile_y = tile_y = (int)upper_left_y / grid_height;
	offset_y = ((int)upper_left_y) % grid_height;


	// draw first row and column "partials"
	// first, setup the source rect, which is just smaller
	
	src.top = offset_y;
	src.left = offset_x;
	src.bottom = grid_height;
	src.right = grid_width;

	dest.top = my_dimension.y;
	dest.left = my_dimension.x;
	dest.right = dest.left + (grid_width - offset_x);
	dest.bottom = dest.top + (grid_width - offset_y);
	

	// now draw the corner (upper left)

	tile_type = (myMap->tilemap_rowindex[tile_y])[tile_x];
	
	myTiles->tileIndex(tile_type)->doBlit(&dest,&src);

	tile_x++;	      
	dest.right = (dest.left = dest.right) + grid_width; // increment

	src.left = 0; // reset for full width tile
	src.right = grid_width;

	for (x_iter=0;x_iter<num_x;x_iter++) { // first row (-2 because of corners)
		tile_type = (myMap->tilemap_rowindex[tile_y])[tile_x];

		myTiles->tileIndex(tile_type)->doBlit(&dest,&src);
		
		dest.left += grid_width;
		dest.right += grid_width;
		tile_x++;
	}

	// now do the upper right corner.

	src.right = offset_x;

	tile_type = (myMap->tilemap_rowindex[tile_y])[tile_x];

	
	myTiles->tileIndex(tile_type)->doBlit(&dest,&src);

	// now, go on to the left side..
	tile_x = start_tile_x;
	tile_y = start_tile_y + 1;
	src.bottom = (src.top = 0) + grid_height;
	src.left = offset_x;
	src.right = grid_width;

	dest.left = my_dimension.x;
	dest.right = (grid_width - offset_x);
	dest.bottom = (dest.top = dest.bottom) + grid_height;


	for (y_iter=0;y_iter<num_y;y_iter++) { // first col (-2 because of corners)
		tile_type = (myMap->tilemap_rowindex[tile_y])[tile_x];

		myTiles->tileIndex(tile_type)->doBlit(&dest,&src);
		dest.top += grid_height;
		dest.bottom += grid_height;
		tile_y++;
	}

	tile_x = start_tile_x + 1;
	tile_y = start_tile_y + 1;

	// now fix the source rect, and setup the destination rect offset

	src.right = (src.left = 0) + grid_width;
	src.bottom = (src.top = 0) + grid_height;
	

	dest.bottom = (dest.top = my_dimension.y + (grid_height - offset_y)) + grid_height;
	dest.right  = (dest.left = my_dimension.x + (grid_width - offset_x)) + grid_width;

	// draw full "inner" tiles

	for (x_iter=0 ; x_iter<num_x ; x_iter++) {
		int save_tile_y = tile_y;
		save_dest = dest;

		for (y_iter=0;y_iter<num_y;y_iter++) {
			// draw single tile normally
			tile_type = (myMap->tilemap_rowindex[tile_y])[tile_x];

			myTiles->tileIndex(tile_type)->doBlit(&dest,&src);

			tile_y++;
			dest.top += grid_height;
			dest.bottom += grid_height;
		}
		dest = save_dest;
		tile_y = save_tile_y;
		tile_x++;
		dest.left += grid_width;
		dest.right += grid_width;
	}

	// done with the center "complete" tiles, now do the bottom partials
	// first, setup the source rect, which is just smaller

	src.top = 0;
	src.left = offset_x;
	src.bottom = offset_y;
	src.right = grid_width;

	// reset to the leftmost position
	dest.right = (dest.left = my_dimension.x) + (grid_width - offset_x);
	dest.bottom = (dest.top = my_dimension.y + ((num_y+1) * grid_height) - offset_y) + grid_height;

	tile_x = start_tile_x;
	tile_y = start_tile_y + num_y+1;


	// now draw the corner (lower left)
	tile_type = (myMap->tilemap_rowindex[tile_y])[tile_y];

	myTiles->tileIndex(tile_type)->doBlit(&dest,&src);
	
	tile_x++;	      
	dest.right = (dest.left = dest.right) + grid_width; // increment

	// now we need the majority of the bottom row

	src.left = 0; // reset for full width tile
	src.right = grid_width;

	for (x_iter=0;x_iter<num_x;x_iter++) { // first row (-2 because of corners)

		myTiles->tileIndex((myMap->tilemap_rowindex[tile_y])[tile_x])->doBlit(&dest,&src);
		
		dest.left += grid_width;
		dest.right += grid_width;
		tile_x++;
	}

	// rightmost column (not upper right corner!!)

	tile_x = start_tile_x + num_x + 1;
	tile_y = start_tile_y + 1;
	src.bottom = (src.top = 0) + grid_height;
	src.left = 0;
	src.right = (offset_x);

	dest.bottom = (dest.top = my_dimension.y + (grid_height - offset_y)) + grid_height;
	dest.right = (dest.left = my_dimension.x + ((num_x+1) * grid_width) - offset_x) + grid_width;


	for (y_iter=0;y_iter<num_y;y_iter++) { // first col (-2 because of corners)
		myTiles->tileIndex((myMap->tilemap_rowindex[tile_y])[tile_x])->doBlit(&dest,&src);
		
		dest.top += grid_height;
		dest.bottom += grid_height;
		tile_y++;
	}

	// draw a highlight box around one tile
	
	if ((highlight_tile_x > 0) && (highlight_tile_y > 0)) {
		// draw the highlight
		// figure out which tile it falls on:
		int sgrid_x = (highlight_tile_x + offset_x) / grid_width;
		int sgrid_y = (highlight_tile_y + offset_y) / grid_height;
		
		int ul_x, ul_y;

		ul_x = (sgrid_x * grid_width) - offset_x;
		ul_y = (sgrid_y * grid_height) - offset_y;
		
		I_drawLine(ul_x,ul_y,ul_x + grid_width, ul_y); // top
		I_drawLine(ul_x + grid_width, ul_y, ul_x + grid_width, ul_y + grid_height); // r
		I_drawLine(ul_x, ul_y, ul_x, ul_y + grid_height); // left
		I_drawLine(ul_x, ul_y + grid_height, ul_x + grid_width, ul_y + grid_height); // b
			
		// dbgMsg(c_info,"drawing point at (%d,%d)",highlight_tile_x + viewPort_left,
		//	highlight_tile_y + viewPort_top);
	}





	// NOW, draw the sprites onto the screen

	// first check the border tiles for sprites which need to
	// be clipped.

	// NOTE: Since the sprites will be attached to the tile which
	// contains their upper-left corner, the left and top borders
	// will only contain FULL sprites, it's the rows and colums OFF the
	// screen to the top and left that will contain the sprites
	// which need to be clipped... for the right and bottom edges,
	// the partial sprites will be in tile rows which are visable on
	// the screen.


	// now do the "inner" tiles, and draw sprites which can just
	// be blindly drawn in full.

	tile_x = start_tile_x;
	tile_y = start_tile_y;

	for (x_iter = sprite_clip_tiles_x ; x_iter<num_x ; x_iter++) {
		int save_tile_y = tile_y;
		for (y_iter = sprite_clip_tiles_y;y_iter<num_y;y_iter++) {
			if ((cur_obj = (myMap->objects_rowindex[tile_y])[tile_x]) != NULL) {
				int fail_count = 0;

				while (cur_obj) {
					cur_obj->Draw((int)upper_left_x, (int)upper_left_y);
					draw_sprite_count++;
					cur_obj = cur_obj->tile_next;
				} // while (cur_obj)
			}

			tile_y++;			
		}
		tile_y = save_tile_y;
		tile_x++;
	}

	// now we need to draw the sprites which need to be clipped...
	// first, off the left side

	int space_avail_to_left = MIN(start_tile_x,sprite_clip_tiles_x);

	tile_x = start_tile_x - space_avail_to_left;
	tile_y = start_tile_y;

	for (x_iter = space_avail_to_left; x_iter >= 0 ; x_iter --) {
		int save_tile_y = tile_y;
			for (y_iter = sprite_clip_tiles_y ; y_iter < num_y ; y_iter++) {
				if ((cur_obj = (myMap->objects_rowindex[tile_y])[tile_x]) != NULL) {
					int fail_count = 0;
					
					while (cur_obj) {

						// we need to clip this one!!!
						

					cur_obj->DrawClipped((int)upper_left_x,(int)upper_left_y);

						
					draw_sprite_clipped_count++;
					cur_obj = cur_obj->tile_next;
					} // while (cur_obj)
				}
				tile_y++;
			}
			tile_y = save_tile_y;
			tile_x++;
	}
	
	// now we need to draw the sprites which need to be clipped...
	// off the top!

	int space_avail_above = MIN(start_tile_y,sprite_clip_tiles_y);

	tile_x = start_tile_x;
	tile_y = start_tile_y - space_avail_above;

	

	for (x_iter = sprite_clip_tiles_x; x_iter < num_x ; x_iter ++) {
		int save_tile_y = tile_y;
			for (y_iter = space_avail_above ; y_iter >= 0 ; y_iter--) {
				if ((cur_obj = (myMap->objects_rowindex[tile_y])[tile_x]) != NULL) {
					int fail_count = 0;
					
					while (cur_obj) {

						// we need to clip this one!!!

						cur_obj->DrawClipped((int)upper_left_x,(int)upper_left_y);
						
					draw_sprite_clipped_count++;
					cur_obj = cur_obj->tile_next;
					} // while (cur_obj)
				}
				tile_y++;
			}
			tile_y = save_tile_y;
			tile_x++;
	}

	// now we need to draw the sprites which need to be clipped...
	// off the bottom!

	int space_avail_below = sprite_clip_tiles_y;

	tile_x = start_tile_x;
	tile_y = start_tile_y + view_height_tiles - space_avail_below;

	for (x_iter = sprite_clip_tiles_x; x_iter < num_x; x_iter++) {
		int save_tile_y = tile_y;
			for (y_iter = space_avail_below ; y_iter >= 0 ; y_iter--) {
				if ((cur_obj = (myMap->objects_rowindex[tile_y])[tile_x]) != NULL) {
					int fail_count = 0;
					
					while (cur_obj) {

						// we need to clip this one!!!
						
					cur_obj->DrawClipped((int)upper_left_x,(int)upper_left_y);
						
					draw_sprite_clipped_count++;
					cur_obj = cur_obj->tile_next;
					} // while (cur_obj)
				}
				tile_y++;
			}
			tile_y = save_tile_y;
			tile_x++;
	}


	// now we need to draw the sprites which need to be clipped...
	// off the right!

	int space_avail_to_right = sprite_clip_tiles_x;


	tile_x = start_tile_x + view_width_tiles - space_avail_to_right;
	tile_y = start_tile_y;

	for (x_iter = space_avail_to_right; x_iter >= 0 ; x_iter--) {
		int save_tile_y = tile_y;
			for (y_iter = sprite_clip_tiles_y ; y_iter < num_y ; y_iter++) {
				if ((cur_obj = (myMap->objects_rowindex[tile_y])[tile_x]) != NULL) {
					int fail_count = 0;
					
					while (cur_obj) {

						// we need to clip this one!!!
						
					cur_obj->DrawClipped((int)upper_left_x,(int)upper_left_y);
						
					draw_sprite_count++;
					cur_obj = cur_obj->tile_next;
					} // while (cur_obj)
				}
				tile_y++;
			}
			tile_y = save_tile_y;
			tile_x++;
	}

	{
		char s[100];

		if (once_in_a_while > 200) {
			sprintf(s,"[%d/%d clipped] Sprites Drawn",draw_sprite_count,draw_sprite_clipped_count);
			consoleView->addText(s);
			once_in_a_while = 0;
		} else {
			once_in_a_while++;
		}

	}


	lua_endblock();
}



void ViewPort::drawSelf() {
	if (mainViewPort) {
		mainViewPort->draw_curview(); // stick this on there first!
	}
}


// ViewPort::highlightTile(xpos,ypos)
//
// highlight the tile at the screenspace coordinates given... or none..
//

void ViewPort::highlightTile(int xpos, int ypos) {
	int local_x, local_y;

	local_x = xpos - viewPort_left;
	local_y = ypos - viewPort_top;

	if ((local_x > 0) && (local_x < viewPort_right) && 
		(local_y > 0) && (local_y < viewPort_bottom)) {
		// it's within our bounds!!!
		
		highlight_tile_x = local_x;
		highlight_tile_y = local_y;
		
	} else {
		// it's outside us!!!
		highlight_tile_x = highlight_tile_y = -1; // none
	}
}

int ViewPort::handleEvent(IN_EVENT *ev) {
	int inchar;

	if (ev->dev_type == DT_KEYBOARD) {
		if (ev->dev.keyboard.mask & KM_ASCII_KEY) {
			inchar = ev->dev.keyboard.ascii_code;
			// we might want to filter nasty ASCII characters here...

			switch (inchar) {
				case 13:
					mainTabView->nextView();
					break;
			}
		}
	} else {
		if (ev->dev_type == DT_MOUSE) {
			dbgMsg(c_excessive,"ViewPort::handleEvent(mouse_moved), (%d,%d)",
				ev->dev.mouse.xpos,ev->dev.mouse.ypos);

			// highlight tile!!
			highlightTile(ev->dev.mouse.xpos,ev->dev.mouse.ypos);
			if (ev->dev.mouse.mask & MS_L_BUTTON) {
				highlightTile(1000,1000);
			}
		}
	}

	if (myFollowSprite) {
		myFollowSprite->handleEvent(ev);
	}
	return 0;
}

void ViewPort::handleFocusChange(int state) {
	if (!state) {
		lastInput = 0; // kill input if they switch to another screen!
	}
}


TileSet::TileSet(int tile_pixel_width, int tile_pixel_height) {

	this->tile_width = tile_pixel_width;
	this->tile_height = tile_pixel_height;
	
	this->arry_size = 50; // start size of the array
	this->tile_arry = 
		(class Tile **)malloc(sizeof(class Tile *) * this->arry_size);

	if (!this->tile_arry) {
		// puke, it failed
		printf("tileset::tileset() tile_arry malloc failed");
		CleanupAndExit("TileSet::tile_arry malloc failed");
	}

	for (int x = 0; x< arry_size;x++) {
		tile_arry[x] = NULL;
	}



	this->num_tiles = 0; // we don't have any tiles yet!
	
}

TileSet::~TileSet() {
	for (int x = 0; x<this->num_tiles; x++) {
		delete tile_arry[x]; // free the file
	}
	free(this->tile_arry); // free the array
}

TileSet::newTile(Tile *a_tile) {
	if (a_tile) {
		if (arry_size < num_tiles) {
			// resize the array!!!
			printf("TileSet::newTile() no more room!");
			CleanupAndExit("TileSet::newTile() no more room!");
		} 

		tile_arry[num_tiles] = a_tile;
		num_tiles++;
		return 0; // success
	}

	return 1; // failure
}

Tile::Tile(const char *filename) {
	// load the surface!
	if (I_loadImage(&this->my_image,filename,0)) {
		// failed!!!
		char s[100];
		sprintf(s,"Tile::Tile() failed loading '%s'",filename);
		CleanupAndExit(s);
	}

	// setup dimensions

}

Tile::~Tile() {
	// free the image!
}

Tile *TileSet::tileIndex(int index) {
	if ((index < 0) || (index > num_tiles)) {
		return NULL;
	}

	return (tile_arry[index]);
		
}

void Tile::doBlit (RECT *dest,RECT *src) 
{
  my_image.src = *src;
  I_doBlit (dest, &this->my_image);
}
