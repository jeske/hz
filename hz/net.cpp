/*
 *   Net.cpp
 */

#ifdef OS_WIn
#include <dplay.h>
#endif
#include "donuts.h" // hWndMain
#include "main.h" // consoleView
#include "map.h"
#include "net.h"


SpriteList *serverObjList = NULL;
Map *serverMap = NULL;

void init_server(void) {
#ifdef REMOVE_SRVTILES
	int x;
	int val = 0;
	TileSet *aTileSet = new TileSet(48,48);

	printf("init_map\n");
	fflush(stdout);

	serverObjList = new SpriteList();


	for (x=0; x<aTileSet->num_tiles; x++) { // put something in the tiles!!!
		aTileSet->tile_arry[x].width = aTileSet->tile_width;
		aTileSet->tile_arry[x].height = aTileSet->tile_height;
		sprintf(aTileSet->tile_arry[x].tile_name, "TILE-%02d",x);
	}

	aTileSet->tile_arry[0].tile_surface = NULL;
	aTileSet->tile_arry[1].tile_surface = NULL;
	aTileSet->tile_arry[2].tile_surface = NULL;


	dbgMsg(c_excessive,"initmap(): going to init Map\n");
	// Now init the Map with that loaded tileset
	
	serverMap = new Map(100,100,aTileSet);

//	shipSprite = new Sprite(defaultSpriteList,OBJ_SHIP,50.0,50.0,0,0);
   
//	printf("initMap(): added shipsprite\n");
//	fflush(stdout);
#endif
}


void tick_server(int tickDiff) {
	defaultSpriteList->doTick(tickDiff);
//	serverObjList->doTick(tickDiff);
}
