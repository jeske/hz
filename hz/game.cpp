// HZ Engine Source
// Copyright (C) 1998 David W. Jeske


// Game.cpp
//
//
// This file serves two purposes right now. It exports functions to lua, and it
// sets up the basic 'game' stuff. The exports come in two forms, "C_xxx" functions
// and "C_obj_xxx" functions. The "obj" functions are designed to operate on
// individual sprites (and thus take a sprite pointer as their first argument),
// while the other ones are general functions which can be called independent
// of any sprite.
//

#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <luadebug.h>


#include "i_system.h" // i_time_ms()
#include "i_video.h" // this should not be here, it's for the set palette
#include "i_console.h"

#include "map.h"
#include "s_lua.h"
#include "s_hz.h"
#include "spritet.h" // sprite type
#include "view.h" // for multiView class
#include "main.h" // for mainTabView
#include "game.h"
#include "net.h"  // tick_server()

extern int g_images_loaded; // from i_draw.h

Map *mainMap = 0;
ViewPort *mainViewPort = 0;
SpriteTmplManager *spriteTmplManager = 0;
TileSet *aTileSet = NULL;

void C_getmapsize(void) {
	lua_pushnumber((float)mainMap->grid_cols);
	lua_pushnumber((float)mainMap->grid_rows);
}

void C_getmapsquare(void) {
	int tile_type;
	int x = (int)lua_getnumber(lua_getparam(1));
	int y = (int)lua_getnumber(lua_getparam(2));
	
	if (mainMap) {
		tile_type = mainMap->getSquare(x,y);
		lua_pushnumber((float)tile_type);
	}
}

// takes (x,y,tile_type)
// 
void C_setmapsquare(void) {
	int x = (int)lua_getnumber(lua_getparam(1));
	int y = (int)lua_getnumber(lua_getparam(2));
	int tile_type = (int)lua_getnumber(lua_getparam(3));

	if (mainMap) {
		mainMap->setSquare(x,y,tile_type);
	}
}


// this will set the palette based on the palette of the image
// specified by the string filename in arg1

void C_setpalette(void) {
	lua_Object file = lua_getparam(1);
	const char *filename;

	if (lua_isstring(file)) {
		filename = lua_getstring(file);
		I_vid_setpalette(filename);
	}

}

// this will make our view follow and our keys goto, another sprite!
// they must have a keyDown, or inputEvent or something

void C_obj_followsprite() {
	Sprite *sp;
	lua_Object objnum = lua_getparam(1);

	if (!lua_isuserdata(objnum)) {
		lua_error("incorrect argument 1 to function C_obj_followsprite()");
	}

	sp = (Sprite *)lua_getuserdata(objnum);

	mainViewPort->followSprite(sp);	
}

void C_obj_setLayer() {
	Sprite *sp;
	lua_Object objnum	= lua_getparam(1);
	lua_Object layer    = lua_getparam(2);	

	if (!lua_isuserdata(objnum)) {
		lua_error("incorrect argument 1 to function C_obj_setlayer()");
	}

	if (!lua_isnumber(layer)) {
		lua_error("incorrect argument 2 to function C_obj_setlayer()");
	}

	sp = (Sprite *)lua_getuserdata(objnum);

	sp->setLayer((int)lua_getnumber(layer));

}

void C_obj_pos() {
	Sprite *sp;
	lua_Object objnum = lua_getparam(1);

	if (!lua_isuserdata(objnum)) {
		lua_error("incorrect argument 1 to function C_obj_pos()");
	}

	sp = (Sprite *)lua_getuserdata(objnum);

	lua_pushnumber((float)sp->posx);
	lua_pushnumber((float)sp->posy);
}

// C_obj_goTo(objnum, xloc, yloc) : a Lua function
//
// objnum : userdata pointer to Sprite
// xloc, yloc : location to move to in pixels

void C_obj_setVelocity() {
	Sprite *sp;
	lua_Object objnum  = lua_getparam(1);
	lua_Object velx    = lua_getparam(2);
	lua_Object vely    = lua_getparam(3);

	if (!lua_isuserdata(objnum)) {
		lua_error("incorrect argument 1 to function C_obj_setVelocity");
	}

	sp = (Sprite *)lua_getuserdata(objnum);

	if (lua_isnumber(velx)) {
		sp->velx = lua_getnumber(velx);
	}
	if (lua_isnumber(vely)) {
		sp->vely = lua_getnumber(vely);
	}
}

// return the x, y velocity and current rotation
void C_obj_getVelocity() {
	Sprite *sp;
	lua_Object objnum = lua_getparam(1);

	if (!lua_isuserdata(objnum)) {
		lua_error("incorrect argument 1 to function C_obj_getVelocity");
	}

	sp = (Sprite *)lua_getuserdata(objnum);

	lua_pushnumber((float)sp->velx);     // x velocity
	lua_pushnumber((float)sp->vely);     // y velocity

}

void C_obj_goTo() {
	Sprite *temp;
	lua_Object objnum, xloc, yloc;

	if (!lua_isuserdata(objnum = lua_getparam(1))) {
		lua_error("incorrect argument 1 to function C_obj_goTo()");
	}
	if (!lua_isnumber(xloc = lua_getparam(2))) {
		lua_error("incorrect argument 2 to function C_obj_goTo()");
	}
	if (!lua_isnumber(yloc = lua_getparam(3))) {
		lua_error("incorrect argument 3 to function C_obj_goTo()");
	}

	// okay, we have the right arguments!
	temp = (Sprite *)lua_getuserdata(objnum);

	temp->goToLoc(lua_getnumber(xloc),lua_getnumber(yloc));

}

// C_obj_delete(objnum) : a Lua function
//
// objnum : userdata pointer to Sprite

void C_obj_delete() {
	Sprite *temp;
	lua_Object objnum;

	if (!lua_isuserdata(objnum = lua_getparam(1))) {
		lua_error("incorrect argument 1 to function C_obj_delete()");
	}

	// printf("deleting sprite!\n");

	temp = (Sprite *) lua_getuserdata(objnum);
	temp->Die();
}

void C_addsprite() {
	SpriteType *type;
	const char *type_name;
	LuaSprite *new_obj;
	double x = 0, y = 0, vx = 0, vy = 0;

	lua_beginblock();
	if (!lua_isstring(lua_getparam(1))) {
		lua_error("incorrect argument 1 to function C_addsprite() (expected string)");
		return;
	}
	type_name = lua_getstring(lua_getparam(1));


	if (lua_isnumber(lua_getparam(2))) {
		x = lua_getnumber(lua_getparam(2));
	}
	if (lua_isnumber(lua_getparam(3))) {
		y = lua_getnumber(lua_getparam(3));
	}
	if (lua_isnumber(lua_getparam(4))) {
		vx = lua_getnumber(lua_getparam(4));
	}
	if (lua_isnumber(lua_getparam(5))) {
		vy = lua_getnumber(lua_getparam(5));
	}


	/* okay, we got all the info we need, now make the sprite! */
	type = findSpriteType(type_name);
	if (type) {
	  dbgMsg(c_excessive,"C_addsprite('%s',%f,%f,%f,%f).\n",type_name,x,y,vx,vy);
	  type->makeInstance(defaultSpriteList,x,y,vx,vy);
	  // lua_pushobject(lua_getref(new_obj->myLuaServerMirror));
	} else {
		dbgMsg(l_error,"no such SpriteType! [%s]\n",type_name);
	}
	lua_endblock();

}

void C_tile_addtype() {
	lua_Object lua_tile;
	const char *filename;
	Tile *atile;

	lua_tile = lua_getparam(1);

	if (lua_isstring(lua_tile)) {
		filename = lua_getstring(lua_tile);

		atile = new Tile(filename);
		aTileSet->newTile(atile);

	}

	
}


void C_sprite_addtype() {
	SpriteType *newtype;
	lua_Object lua_sprite;
	const char *type_name;
	
	lua_beginblock();

	if (!lua_isstring(lua_getparam(1))) {
		lua_error("incorrect argument 1 to function C_sprite_addtype() (expected string)");
	} else {
		type_name = lua_getstring(lua_getparam(1));
	}

	if (!lua_istable(lua_sprite = lua_getparam(2))) {
		lua_error("incorrect argument 2 to function C_sprite_addtype() (expected table)");
	}

	newtype = new LuaSpriteType(type_name,lua_sprite);

	lua_endblock();
	dbgMsg(c_excessive,"C_sprite_addtype(): added sprite type (%s)\n",type_name);
	dbgMsg(c_excessive,"ERROR: Now you need to make the code put it somewhere!!!\n");
	
}

void C_sprite_listtypes() {
	const char *name;
	int cur = 0;
	char s[100];

	consoleView->addText("SpriteTypes: ");
	while (name = spriteTypeName(cur)) {
		sprintf(s,"%02d: ",cur);
		consoleView->addString(s);
		consoleView->addText(name);
		cur++;
	}
}

void C_obj_viewFollow() {
	lua_Object param1 = lua_getparam(1);
	Sprite *sp;

	if (!lua_isuserdata(param1)) {
		lua_error("bad arg1 to C_followsprite()");
	}

	sp = (Sprite *)lua_getuserdata(param1);

	mainViewPort->followSprite(sp);
}



int old_error_ref = -1;

static void lua_printstack ()
{
  int level = 1;  /* skip level 0 (it's this function) */
  lua_Object func;
  while ((func = lua_stackedfunction(level++)) != LUA_NOOBJECT) {
    char *name;
    int currentline;
    char *filename;
    int linedefined;
    lua_funcinfo(func, &filename, &linedefined);
    printf((level==2) ? "Active Stack:\n\t" : "\t");
    switch (*lua_getobjname(func, &name)) {
      case 'g':
        printf("function %s", name);
        break;
      case 't':
        printf("`%s' tag method", name);
        break;
      default: {
        if (linedefined == 0)
          printf("main of %s", filename);
        else if (linedefined < 0)
          printf("%s", filename);
        else
          printf("function (%s:%d)", filename, linedefined);
        filename = NULL;
      }
    }
    if ((currentline = lua_currentline(func)) > 0)
      printf(" at line %d", currentline);
    if (filename)
      printf(" [in file %s]", filename);
    printf("\n");
  }
}


void C_luaerror_handler() {
	lua_Object old_handler;
	lua_Object param1 = lua_getparam(1);

	// switch to the console display
	
//	mainTabView->switchTo(1);
	printf("**** LUA ERROR **** '%s'\n",lua_getstring(param1));
	lua_printstack();
	printf("****\n");

	// call the old error handler

	old_handler = lua_getref(old_error_ref);

	lua_pushobject(param1);
	lua_callfunction(old_handler);

}

void register_luafunctions() {
	// C_obj_goTo(objnum, xloc, yloc); 
	// locations in pixels
	// objnum should be a "userdata" pointer to a sprite...
	lua_register("C_obj_goTo",C_obj_goTo);
	lua_register("C_obj_delete",C_obj_delete);
	lua_register("C_sprite_addtype",C_sprite_addtype);
	lua_register("C_addsprite",C_addsprite);
	lua_register("C_sprite_listtypes", C_sprite_listtypes);
	lua_register("C_obj_viewFollow", C_obj_viewFollow);
	lua_register("C_obj_getVelocity", C_obj_getVelocity);
	lua_register("C_obj_setVelocity", C_obj_setVelocity);
	lua_register("C_obj_followsprite", C_obj_followsprite);
	lua_register("C_obj_pos", C_obj_pos );
	lua_register("C_obj_setLayer", C_obj_setLayer);
	lua_register("C_setpalette", C_setpalette);
	lua_register("C_tile_addtype", C_tile_addtype);
	lua_register("C_setmapsquare", C_setmapsquare);
	lua_register("C_getmapsquare", C_getmapsquare);
	lua_register("C_getmapsize", C_getmapsize);
	
	// register our error handler
#if 0
	lua_pushstring("error");
	lua_pushcfunction(C_luaerror_handler);
	lua_callfunction(lua_getglobal("setfallback"));
	old_error_handler = lua_getparam(1);
#endif

#if USING_LUA25

  lua_pushobject(lua_setfallback("error", C_luaerror_handler));
  old_error_ref = lua_ref(1);

#endif

// USING LUA31
  lua_pushCclosure(C_luaerror_handler,0);
  lua_pushobject(lua_seterrormethod());
  old_error_ref = lua_ref(1); //locked ref!

}



void init_lua_objects() {
        
        printf ("init_lua_objects(): Starting\n");

	strlib_open();
	mathlib_open();
	
        printf ("init_lua_objects(): register lua functions\n");
	lua_beginblock();
	register_luafunctions();
	lua_endblock();

	printf("Starting Lua [lua\\init.lua]\n");
        consoleView->runningLua(1);
	lua_beginblock();
#ifdef OS_WIN
	if (lua_dofile("lua\\init.lua")) {
		printf("Error loading [lua\\init.lua]\n");
	}
#else
	if (lua_dofile("lua/init.lua")) {
		printf("Error loading [lua/init.lua]\n");
	}
#endif
	lua_endblock();
        consoleView->runningLua(0);
	printf("%d Images loaded\n",g_images_loaded);

}



void init_map() {
	int val = 0;
		
	aTileSet = new TileSet(32,32);

	printf("init_map\n");
	fflush(stdout);

	spriteTmplManager = new SpriteTmplManager;
	spriteTmplManager->max_sprite.width = 250;  // this sets up the max sprite size
	spriteTmplManager->max_sprite.height = 250;

//	aTileSet->newTile(new Tile("std/Tile00.bmp"));
//	aTileSet->newTile(new Tile("std/Tile01.bmp"));
//	aTileSet->newTile(new Tile("std/Tile02.bmp"));

	dbgMsg(c_excessive,"initmap(): going to init Map\n");

	// Now init the Map with that loaded tileset
	
	mainMap = new Map(100,100,aTileSet);
	dbgMsg(c_excessive,"initMap(): going to startup Main Viewport\n");
	mainViewPort->setMap(450,400,mainMap);

	// mainMap->setSquare(0,0,0);
	// mainMap->setSquare(0,1,0);
	// mainMap->setSquare(1,0,0);
	// mainMap->setSquare(1,1,0);

}


// main entry point for game startup
void setup_game(void)
{
	dbgMsg(c_info,"setup_game\n");
    restCount = i_time_ms();

//	initJoystick(); // DAVE
    
	defaultSpriteList = new SpriteList(); 
	init_map();

	init_lua_objects();
	
	// now create our mainship, this should be done in lua soon...

	dbgMsg(c_excessive,"initMap(): going to add Ship Sprite\n");			
	SpriteType *type;
	Sprite *sp;
	type = findSpriteType("mainship");
	if (type) {
	  dbgMsg(c_info,"adding SpriteType mainship\n");
	  sp = type->makeInstance(defaultSpriteList,50.0,50.0,0.0,0.0);
	  mainViewPort->followSprite(sp);
	} else {
		dbgMsg(c_info,"no mainship SpriteType!\n");					
	}
   	dbgMsg(c_info,"initMap(): added shipsprite\n");

	lua_beginblock();
	lua_Object obj = lua_getglobal("setupGameSprites");

	if (lua_isfunction(obj)) {
		lua_callfunction(obj);
	} else {
		dbgMsg(l_error,"no setupGameSprites()!!!\n");
	}
	lua_endblock();

	// hack to try the C++ sprites

	Sprite *c_sprite = new SHZFlying(defaultSpriteList,type,50.0,100.0,0.0,0.0);
	mainViewPort->followSprite(c_sprite);

	printf("setup_game() finished\n");
	fflush(stdout);
	mainTabView->switchTo(0);
}

