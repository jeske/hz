// HZ Engine Source
// Copyright (C) 1998 by David W. Jeske

#ifndef MAP_H
#define MAP_H

#ifdef OS_UNIX
#include "translate.h"
#endif
#include "sprite.h"
#include "view.h"

#define VIEW_TILE_HEIGHT (this->view_height_tiles)
#define VIEW_TILE_WIDTH  (this->view_width_tiles)

class TileSet;

class Map {
protected:
	Sprite **objects;
	unsigned short int *tilemap;
public:	
	int grid_rows, grid_cols;  // in tile grids
	int map_width, map_height; // in pixels

	unsigned short int **tilemap_rowindex; // index to row start points
	Sprite ***objects_rowindex; // index to row start points
// public:
	TileSet *myTiles;
	Map(int gr, int gc, TileSet *aTileSet); // make a random map of a given size
	void allocMap(); // allocate and setup the map structures
	void deallocMap();
	void setup(); // final setup
	void setSquare(int x, int y, int tile_type);
	int getSquare(int x, int y);
	~Map();
        Sprite *firstSpriteAtTileXY(int tile_x,int tile_y);
};


struct curloc_struct {
	double upper_left_x, upper_left_y; // the "map location" of the upper left corner pixel of the view
	// might want to put ship location or "center" of view
	// location in here instead.. who knows
};

class ViewPort : public View {
protected:

	int highlight_tile_x, highlight_tile_y; // for highlighted tile!


	int draw_sprite_count;
	int draw_sprite_clipped_count;

	Map *myMap;
	TileSet *myTiles;
	int view_height; // pixels
	int view_width; // pixels
	Sprite *myFollowSprite;

	// computedValues
		int view_width_tiles;		// width of the view in tiles
		int view_height_tiles;		// height of the view in tiles

		int view_width_extra;		// These are the extra pixels, computed like this:
		int view_height_extra;		// (view_width_tiles * tile_width) + view_width_extra = view_width

		int sprite_clip_tiles_x, sprite_clip_tiles_y;	// the number of tile units which make up the 
														// maximum sprite size.

		int viewPort_left;
		int viewPort_top;
		int viewPort_right;
		int viewPort_bottom;

		int bb_right;  // bounding box
		int bb_top;
		int bb_bottom;
		int bb_left;

	// end computedValues

	double upper_left_x, upper_left_y; // "map location" (pixels) of the upper left corner pixel
								// of the view. 
	void computeSizeVars();
	void draw_curview(void);
	void draw_curview2(void);
	virtual void drawSelf();
	virtual void handleFocusChange(int state);
	static void doBlit(RECT *dest, RECT *src, LPDIRECTDRAWSURFACE surf);
public:
	void highlightTile(int x, int y); // screenspace coordinates
	void setMap(int width, int height, Map *aMap);
	void followSprite(Sprite *sp);
	virtual int handleEvent(struct input_event *ev); // we want key events!
	void doFollowTick(unsigned int tickDiff);

	ViewPort(int x,int y, int w, int h); // viewport size and map to use
	~ViewPort();
	int setCurLoc(struct curloc_struct *loc);
};

// Tile information


class Tile {
public:
	IMAGE my_image;
	int width, height;
	char tile_name[40];
	LPDIRECTDRAWSURFACE tile_surface;

	void doBlit(RECT *dest, RECT *src);
	Tile(const char *filename);
	~Tile();
};

class TileSet {
protected:
	int num_tiles;
	Tile **tile_arry;
	int arry_size;

public:
	int tile_width, tile_height;
	int indexFromName(const char *name);
	Tile *tileIndex(int index);
	int newTile(Tile *a_tile);
	TileSet(int tile_width, int tile_height);
	~TileSet();
};


void init_map();
extern ViewPort *mainViewPort;
extern Map *mainMap;
// extern SpriteTmplManager *spriteTmplManager;

#endif
