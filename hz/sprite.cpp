// HZ Engine Source 
// Copyright (C) 1998 David W. Jeske


// Sprite.cpp
//
//
// Sprite.cpp: the game sprites :) Alot of this code started out in the
//     C donuts demo. I slurped it up into a class, and the boundaries are
//     pretty fuzzy and poor. Lots of public variables in the class (bad).
//     There are static object types (which no longer apply), Lua objects
//     are all theoretically generic objects. There is code in there for
//     handling what I call "mirrors"
//
//     Every object in the world has a C representation and it's script-side   
//     "mirror". The two objects are connected and interrelated. When the            
//     game is running, every object alive in the world has an entry in the          
//     "objects" table in the script language.
//  
//     Sprites are stuck into a cross-linked web. Every sprite is connected to:
//  
//        - the tile it's top-left corner is on (and all the other sprites there)
//        - all other sprites via a "SpriteList"
//        - the "SpriteType" object which defines the sprite type's        
//          characteristics 
//  
//     There are many vistigal things in the Sprite instance data, like the
//       direct draw surface for the sprite, which now comes from the
//       sprite type object instead.

#include <lua.h>
#include <math.h>

#ifdef OS_WIN
#include "DrawHndl.h" // RestoreSurfaces()
#endif

#include "donuts.h"
#include "main.h"
#include "misc.h"
#include "map.h"

#include "sprite.h"


SpriteList *defaultSpriteList = NULL;


// *****************************
// class Sprite
//   - a map sprite

Sprite::Sprite(SpriteList *aList, SpriteType *a_type, double x, double y, double vx, double vy) {
	dbgMsg(c_excessive,"Sprite::Sprite(), creating typed sprite\n");
	mySpriteTypeObj = a_type;
	
	
	this->layer = 0; // set the start layer
	 // call the standard init!
	this->SpriteSetup(aList, OBJ_DONUT, x,y,vx,vy);
}

static int sprite_number = 0;

void Sprite::SpriteSetup(SpriteList *aList, SHORT a_type, double x, double y, double vx, double vy) {
	Sprite *new_node = this;

	if (new_node == NULL) {
		dbgMsg(c_error,"NULL ptr Sprite...\n");
		return;
	}

	mySpriteList = aList;
	// mySpriteTypeObj = NULL;

	this->should_die = 0;
	this->next = this->prev = NULL;
	this->type = a_type;
	this->tile_next = NULL;
	this->z_value = 0;
    this->my_map_loc = NULL;
	this->old_tile_x = -1;
	this->old_tile_y = -1;
	this->mynumber = sprite_number++;

	if (mySpriteTypeObj) {
		obj_type_string = mySpriteTypeObj->name();
	} else {
		dbgMsg(c_error,"constructed sprite without typeobj!\n");
		obj_type_string = "unknown";
	}

		if( x < 0.0) {// no position specified?
			new_node->posx = randDouble( 0.0, (double)MAX_DONUT_X );
			new_node->posy = randDouble( 0.0, (double)MAX_DONUT_Y );
		} else {
			new_node->posx = x;
			new_node->posy = y;
		}

		//new_node->posx = x;
		//new_node->posy = y;
		new_node->velx = vx;
		new_node->vely = vy;


//		new_node->surf = NULL;

		
	dbgMsg(c_excessive,"Sprite::Sprite(), going to add to SpriteList\n");
	
	if (mySpriteList) {
		mySpriteList->addSprite(this);
	}
	
	dbgMsg(c_excessive,"Sprite::Sprite(), added to spritelist (%s:%d)\n",obj_type_string,mynumber);
	
	dbgMsg(c_excessive,"Sprite::Sprite(), going to add to Lua object list\n");
	
	// see if there is an "objects" table for the destination
	// to go in, and
	// see if there is an "object_types" table for us to get the
	// template from...
	
	lua_beginblock();
	
	myLuaMirror = -1;
	
	lua_Object objects_tbl = lua_getglobal("objects");
	lua_Object object_types_tbl = lua_getglobal("object_types");
	if (!lua_istable(objects_tbl) || !lua_istable(object_types_tbl)) {
		dbgMsg(c_error,"ERR: No 'objects' table to hold new Lua mirror, _OR_ no 'object_types' table\n");
	} else {
		// get _THIS_ object type from the "object_types" table
		// of templates...
		lua_pushobject(object_types_tbl);
		lua_pushstring(obj_type_string);
		lua_Object objptr = lua_gettable();

		if (lua_istable(objptr)) {
			// get the "new" constructor from that object
			lua_pushobject(objptr);
			lua_pushstring("new");
			lua_Object constructor_fn = lua_gettable();


			if (lua_isfunction(constructor_fn)) {
				
				// create the new list with "objnum" set to the correct 
				// place (i.e. here)
				lua_Object newObj = lua_createtable();
				lua_pushobject(newObj);
				lua_pushstring("objnum");
				lua_pushuserdata((void *)this);
				lua_settable();


				
				// now we need to call the constructor with this new object
				// don't forget it's a METHOD!!!
				lua_pushobject(objptr); // push SELF!
				lua_pushobject(newObj); // push the new list...
				if (lua_callfunction(constructor_fn)) {
					if (consoleView) {
						dbgMsg(l_error,"constructor call failed..\n");
					}
				}

				lua_Object initializedObj = lua_getresult(1);

				if (lua_istable(initializedObj)) {
					
					// now we need to store the new object in the "objects" table
					lua_pushobject(objects_tbl);
					lua_pushnumber((float)mynumber); // my object number
					lua_pushobject(initializedObj);
					lua_settable();
				
					// we need a "ref" for the object, but DON'T lock it!
					lua_pushobject(initializedObj);
					myLuaMirror = lua_ref(0);
				} else {
					dbgMsg(l_error,"object type 'new' constructor didn't return a table\n");
				}
			} else {
				dbgMsg(l_error,"objtype has no 'new' constructor\n");
			}
		} else {
			dbgMsg(l_error,"objtype (%s) not an object\n",obj_type_string);
		}
	}

	lua_endblock();

	dbgMsg(c_excessive,"Sprite::Sprite(), added to Lua object list\n");
//	lua_dostring("printTables(objects);");

/*
 * server side Lua mirror 
 */


	// see if there is an "objects" table for the destination
	// to go in, and
	// see if there is an "object_types" table for us to get the
	// template from...

	lua_beginblock();

	myLuaServerMirror = -1;

	lua_Object srvobjs_tbl = lua_getglobal("srvobjs");
	lua_Object srvobj_types_tbl = lua_getglobal("srvobj_types");
	if (!lua_istable(srvobjs_tbl) || !lua_istable(srvobj_types_tbl)) {
		dbgMsg(l_error,"ERR: No 'srvobjs' table to hold new Lua Server mirror, _OR_ no 'srvobj_types' table\n");
	} else {
		// get _THIS_ object type from the "srvobj_type" table
		// of templates...
		lua_pushobject(srvobj_types_tbl);
		lua_pushstring(obj_type_string);
		lua_Object objptr = lua_gettable();

		if (lua_istable(objptr)) {
			// get the "new" constructor from that object
			lua_pushobject(objptr);
			lua_pushstring("new");
			lua_Object constructor_fn = lua_gettable();


			if (lua_isfunction(constructor_fn)) {
				
				// create the new list with "objnum" set to the correct 
				// place (i.e. here)
				lua_Object newObj = lua_createtable();
				lua_pushobject(newObj);
				lua_pushstring("objnum");
				lua_pushuserdata((void *)this);
				lua_settable();
				
				// now we need to call the constructor with this new object
				// don't forget it's a METHOD!!!
				lua_pushobject(objptr); // push SELF!
				lua_pushobject(newObj); // push the new list...
				if (lua_callfunction(constructor_fn)) {
					dbgMsg(l_error,"constructor call failed..\n");
				}

				lua_Object initializedObj = lua_getresult(1);

				if (lua_istable(initializedObj)) {
					
					// now we need to store the new object in the "objects" table
					lua_pushobject(srvobjs_tbl);
					lua_pushnumber((float)mynumber); // my object number
					lua_pushobject(initializedObj);
					lua_settable();
				
					// we need a "ref" for the object, but DON'T lock it!
					lua_pushobject(initializedObj);
					myLuaServerMirror = lua_ref(0);
				} else {
					dbgMsg(l_error,"srv-object type 'new' constructor didn't return a table\n");
				}
			} else {
				dbgMsg(l_error,"srv-objtype has no 'new' constructor\n");
			}
		} else {
			dbgMsg(l_error,"srv-objtype (%s) not a lua obj_type\n",obj_type_string);
		}
	}

	lua_endblock();


}


// destructor
Sprite::~Sprite() {

	// first, remove my Lua Mirror

	lua_beginblock();

	lua_Object objects_tbl = lua_getglobal("objects");
	if (!lua_istable(objects_tbl)) {
		dbgMsg(l_error,"ERR: No 'objects' table to remove mirror from\n");
	} else {
		// get _THIS_ object type from the "objects" table
	
		lua_pushobject(objects_tbl);
		lua_pushnumber((float)mynumber);
		lua_Object objptr = lua_gettable();
		if (lua_istable(objptr)) {
			// now we need to remove that entry..
			lua_pushobject(objects_tbl);
			lua_pushnumber((float)mynumber);
			lua_pushnil();
			lua_settable();
		}
	}

	lua_endblock();

	// now remove us from the map..
	if (mySpriteList) {
		mySpriteList->removeSprite(this);
	}
	this->removeObjectFromMap();
}

static int spriteListCount = 0;

SpriteList::SpriteList() {
	myHead = NULL;
	myNum = spriteListCount;

	dbgMsg(c_excessive,"SpriteList #%d created.\n",spriteListCount);
	spriteListCount++;
}

SpriteList::~SpriteList() {
	// should remove all of the "prev" and "next" pointers
	// for sprites in my list... or perhaps just delete them all

}


void SpriteList::doTick(unsigned int tickDiff) {
	Sprite *cur, *next;

	// For some god awful reason (namely Bullets), we need to let objects
	// delete themselves during the doTick() method, so make sure we figure out
	// who the next Sprite is before we doTick();

	cur = myHead;
	while (cur) {
		next = cur->next;
		cur->doTick(tickDiff);
		cur = next;
	}
}

void SpriteList::doAITick(unsigned int tickDiff) {
	Sprite *cur, *next;

	// For some god awful reason (namely Bullets), we need to let objects
	// delete themselves during the doTick() method, so make sure we figure out
	// who the next Sprite is before we doTick();

	cur = myHead;
	while (cur) {
		next = cur->next;
		cur->doAITick(tickDiff);
		cur = next;
	}
}


void SpriteList::addSprite(Sprite *aSprite) {

	if (!aSprite) {
		return;
	}

	dbgMsg(c_excessive,"SpriteList #%d, added Sprite\n",myNum);
	
	if (myHead) {
		aSprite->next = myHead;
		myHead->prev = aSprite;
		aSprite->prev = NULL;
		myHead = aSprite;
	} else {
		aSprite->next = NULL;
		aSprite->prev = NULL;
		myHead = aSprite;
	}
}

void SpriteList::removeSprite(Sprite *aSprite) {
	if (!aSprite) {
		return;
	}

	dbgMsg(c_excessive,"SpriteList #%d, removed Sprite\n",myNum);
	
	if (myHead == aSprite) {
		myHead = aSprite->next;
		if (myHead) {
			myHead->prev = NULL;
		}
	} else {
		aSprite->prev->next = aSprite->next;
		if (aSprite->next) {
			aSprite->next->prev = aSprite->prev;
		}
	}

	aSprite->next = NULL;
	aSprite->prev = NULL;

}

int ai_funcs = -1;

void Sprite::doAITick(unsigned int tickDiff) {
	lua_beginblock();

	if (myLuaMirror != -1) {
		lua_Object temp_obj = lua_getref(myLuaMirror);
		if (!lua_istable(temp_obj)) {
			myLuaMirror = -1;
			dbgMsg(l_error,"Obj: lost sprite ref\n");
		}

		lua_pushobject(temp_obj);
		lua_pushstring("ai_event");
		lua_Object fnobj = lua_gettable();
		if (lua_isfunction(fnobj)) {
			// it's a function, so call it!

			// actually, it's a METHOD!
			lua_pushobject(temp_obj);	// push SELF!
			lua_pushstring("evt");		// push the event
			lua_pushnumber((float)posx);		// xposition
			lua_pushnumber((float)posy);		// yposition
			int fn_result = lua_callfunction(fnobj);
			if (!fn_result) {
				// no error!
			}
		}
	
	}

	lua_endblock();
}

const char *Sprite::getPropertyStr(const char *propName) {
  lua_Object lua_obj = lua_getref(myLuaServerMirror);

  lua_pushobject(lua_obj);
  lua_pushstring(propName);
  lua_Object temp = lua_gettable();

  if (!lua_isstring(temp) && !lua_isnumber(temp)) {
				// var dosn't exist, just choose the first one	
    return NULL;
  } else {
    return lua_getstring(temp);
  }
}

int Sprite::handleEvent(struct input_event *ev) { // we want key events!
	if (ev->dev_type == DT_KEYBOARD) {

		if (ev->dev.keyboard.mask & KM_KEYUP) {
			dbgMsg(c_info,"Sprite::handleEvent() key up vk_code = #%d\n",
				ev->dev.keyboard.vk_code);
			lua_beginblock();
			if (myLuaServerMirror != -1) {
				lua_Object temp_obj = lua_getref(myLuaServerMirror);
				if (!lua_istable(temp_obj)) {
					myLuaServerMirror = -1;
					dbgMsg(l_error,"SrvObj: lost sprite ref\n");
				}
				lua_pushobject(temp_obj);
				lua_pushstring("keyUp");
				lua_Object fnobj = lua_gettable();
	
				if (lua_isfunction(fnobj)) {
					// it's a function, so call it!
						
					// actually, it's a METHOD!
					lua_pushobject(temp_obj);	// push SELF!
					lua_pushnumber((float)ev->dev.keyboard.vk_code); // vk_code
					int fn_result = lua_callfunction(fnobj);
					if (!fn_result) {
						// no error!
					}
				} else {
					dbgMsg(l_info, "Sprite::handleEvent() no 'keyDown' handler in my mirror\n");
				}
				
			} else {
				dbgMsg(l_error,"Sprite::handleEvent() myLuaServerMirror = -1\n");
			}
			
			lua_endblock();
		}


		if (ev->dev.keyboard.mask & KM_KEYDOWN) {
			dbgMsg(c_info,"Sprite::handleEvent() key down vk_code = #%d\n",
				ev->dev.keyboard.vk_code);
			lua_beginblock();
			if (myLuaServerMirror != -1) {
				lua_Object temp_obj = lua_getref(myLuaServerMirror);
				if (!lua_istable(temp_obj)) {
					myLuaServerMirror = -1;
					dbgMsg(l_error,"SrvObj: lost sprite ref\n");
				}
				lua_pushobject(temp_obj);
				lua_pushstring("keyDown");
				lua_Object fnobj = lua_gettable();
	
				if (lua_isfunction(fnobj)) {
					// it's a function, so call it!
						
					// actually, it's a METHOD!
					lua_pushobject(temp_obj);	// push SELF!
					lua_pushnumber((float)ev->dev.keyboard.vk_code); // vk_code
					int fn_result = lua_callfunction(fnobj);
					if (!fn_result) {
						// no error!
					}
				} else {
					dbgMsg(l_info, "Sprite::handleEvent() no 'keyDown' handler in my mirror\n");
				}
				
			} else {
				dbgMsg(l_error,"Sprite::handleEvent() myLuaServerMirror = -1\n");
			}
			
			lua_endblock();
		}

		if (ev->dev.keyboard.mask & KM_ASCII_KEY) {
	//		inchar = ev->dev.keyboard.ascii_code;
	
			dbgMsg(c_info, "Sprite::handleEvent() ascii key = %c\n",
				ev->dev.keyboard.ascii_code);

			lua_beginblock();
			if (myLuaServerMirror != -1) {
				lua_Object temp_obj = lua_getref(myLuaServerMirror);
				if (!lua_istable(temp_obj)) {
					myLuaServerMirror = -1;
					dbgMsg(l_error,"SrvObj: lost sprite ref\n");
				}
				lua_pushobject(temp_obj);
				lua_pushstring("inputEvent");
				lua_Object fnobj = lua_gettable();
	
				if (lua_isfunction(fnobj)) {
					// it's a function, so call it!
						
					// actually, it's a METHOD!
					lua_pushobject(temp_obj);	// push SELF!
					lua_pushnumber((float)ev->dev.keyboard.ascii_code); // ascii key
					int fn_result = lua_callfunction(fnobj);
					if (!fn_result) {
						// no error!
					}
				} else {
					dbgMsg(l_info, "Sprite::handleEvent() no 'inputEvent' handler in my mirror\n");
				}
				
			} else {
				dbgMsg(l_error,"Sprite::handleEvent() myLuaServerMirror = -1\n");
			}
			
			lua_endblock();
		}
	}

	return 1;
}


void Sprite::doTick(unsigned int tickDiff) {
	Sprite *ptr = this;
	Sprite *target = this;
	double maxx, maxy, maxframe;
	
	ptr->posx  += ptr->velx  * (double)tickDiff;
	ptr->posy  += ptr->vely  * (double)tickDiff;
		
	maxx = (double) MAX_DONUT_X;
	maxy = (double) MAX_DONUT_Y;
	maxframe = (double) MAX_DONUT_FRAME;

	// here we'll call the mirror's doTick

	lua_beginblock();

	if (myLuaServerMirror != -1) {
		lua_Object temp_obj = lua_getref(myLuaServerMirror);
		if (!lua_istable(temp_obj)) {
			myLuaServerMirror = -1;
			dbgMsg(l_error,"Obj: lost server sprite ref\n");
		}

		lua_pushobject(temp_obj);
		lua_pushstring("doTick");
		lua_Object fnobj = lua_gettable();
		if (lua_isfunction(fnobj)) {
			// it's a function, so call it!

			// actually, it's a METHOD!
			lua_pushobject(temp_obj);	// push SELF!
			lua_pushnumber((float)tickDiff);	// push the tick Count
			int fn_result = lua_callfunction(fnobj);
			if (!fn_result) {
				// no error!
			}
		}
	
	}

	lua_endblock();

	if (this->should_die) {
		delete this; // probably not the best thing to do, but it works
		return;
	}
	

	// here is the "bounce" on the edge of the map
			
			if( ptr->posx > maxx )
			{
				ptr->posx = maxx;
				ptr->velx = -ptr->velx / 2;
			}
			else if ( ptr->posx < 0 )
			{
				ptr->posx =0;
				ptr->velx = -ptr->velx;
			}
			if( ptr->posy > maxy )
			{
				ptr->posy = maxy;
				ptr->vely = -ptr->vely / 2;
			}
			else if ( ptr->posy < 0 )
			{
				ptr->posy =0;
				ptr->vely = -ptr->vely;
			}
			ptr->placeObject(mainMap);		
		



		// check for collision
		Sprite *obj_hit;
		if (obj_hit = this->checkCollision()) {
				// There was a collision so send the ge_collision message...
			lua_beginblock();

			if (myLuaServerMirror != -1) {
				lua_Object temp_obj = lua_getref(myLuaServerMirror);
				if (!lua_istable(temp_obj)) {
					myLuaServerMirror = -1;
					dbgMsg(l_error,"SrvObj: lost sprite ref\n");
				}

				lua_pushobject(temp_obj);
				lua_pushstring("ge_collision");
				lua_Object fnobj = lua_gettable();

				lua_Object whoIHit = lua_getref(obj_hit->myLuaServerMirror);

				if (lua_isfunction(fnobj)) {
					// it's a function, so call it!
					
					// actually, it's a METHOD!
					lua_pushobject(temp_obj);	// push SELF!
					lua_pushnumber((float)posx);		// xposition
					lua_pushnumber((float)posy);		// yposition
					lua_pushobject(whoIHit);	// push the object I hit!
					int fn_result = lua_callfunction(fnobj);
					if (!fn_result) {
						// no error!
					}
				}
				
			}
			
			lua_endblock();
		} // end of collision check
}



/*
 *  Sprite *Sprite::checkCollision() 
 *
 * This function checks to see if the current object has hit anyone...
 *
 * We should probably do something to prevent both objects from checking
 * that they hit eachother... or perhaps not...
 *
 */


#define MAP_DXDY_COUNT 9

int map_dxdy[MAP_DXDY_COUNT][2] = { 
	{  0,  0 }, // the square we're in
	{ -1,  0 }, // W/E/N/S
	{  1,  0 },
	{  0, -1 },
	{  0,  1 },

	{ -1, -1 }, // NW/SW/SE/NE
	{ -1,  1 },
	{  1,  1 },
	{  1, -1 }};


// tells the world if we are 'nocollide = 1' or not...

int Sprite::canCollide() {
	int retval = 0; 

	lua_beginblock();
	if (myLuaServerMirror != -1) {
		lua_Object temp_obj = lua_getref(myLuaServerMirror);
		if (!lua_istable(temp_obj)) {
			myLuaServerMirror = -1;
			dbgMsg(l_error,"SrvObj: lost sprite ref\n");
		}
		lua_pushobject(temp_obj);
		lua_pushstring("nocollide");
		lua_Object nocollide_flag = lua_gettable();
	
		if (lua_isnil(nocollide_flag)) {
			retval = 1;
		} else {
			retval = 0;
		}
				
	} else {
		dbgMsg(l_error,"Sprite::handleEvent() myLuaServerMirror = -1\n");
	}
			
	lua_endblock();

	return (retval);
}


Sprite *Sprite::checkCollision() {
	// we need to check all the mapsquares within a certain distance from us, we'll
	// check in this order:
	int my_tile_x = old_tile_x;
    int my_tile_y = old_tile_y;
	int dxdy_count = 0;
	Sprite *hit_temp = NULL;
	int did_hit;
//	double tempx, tempy;

// static size collision detection, yuck!

#define OBJ_WIDTH 64
#define OBJ_HEIGHT 64

	Sprite *ul_obj, *lr_obj;

	int check_tile_x, check_tile_y;

	if (!myMap) {
		return NULL;
	}

	while ((!hit_temp) && (dxdy_count < MAP_DXDY_COUNT)) {
		check_tile_x = my_tile_x + map_dxdy[dxdy_count][0];
		check_tile_y = my_tile_y + map_dxdy[dxdy_count][1];
		
		if ((check_tile_x >= 0) && (check_tile_y >= 0)) {
			hit_temp = (myMap->objects_rowindex[check_tile_y])[check_tile_x];

			did_hit = 0;
			while (hit_temp && !did_hit) {
				if ((hit_temp == this) || (!hit_temp->canCollide())) {
					hit_temp = hit_temp->tile_next;
				} else {
					// check to see if we hit this object
						
					if ((hit_temp->posx) > this->posx) {
						// they are to our right
						lr_obj = hit_temp;
						ul_obj = this;
					} else {
						// they are to our left
						ul_obj = hit_temp;
						lr_obj = this;
					}

					if (lr_obj->posx < (ul_obj->posx + (OBJ_WIDTH))) {
						// they hit in the "x" direction, now check y
						if ((hit_temp->posy) > this->posy) {
							// they are below us
							lr_obj = hit_temp;
							ul_obj = this;
						} else {
							// they are above us...
							ul_obj = hit_temp;
							lr_obj = this;
						}

						if (lr_obj->posy < (ul_obj->posy + (OBJ_HEIGHT))) {
							// they hit!
							did_hit = 1;
						} 
						
					}

					if (!did_hit) {
						hit_temp = hit_temp->tile_next;
					}
				}
			}
		}


		dxdy_count++;
	}

//	if (hit_temp) {
//     dbgMsg(c_info,"Collision: [%d]:%s and [%d]:%s at (%f,%f)\n",this->mynumber, this->obj_type_string,
//			hit_temp->mynumber, hit_temp->obj_type_string, this->posx, this->posy);
//	}

	return hit_temp;
}

/*
 * Sprite::setLayer(int new_layer) 
 *
 * this sets the new draw layer for the object
 */

void Sprite::setLayer(int new_layer) {
	this->layer = new_layer;
}


/*
 * Sprite::goToLoc(double newx, double newy);
 *
 * This function is called to set an object's direction and velocity to goto
 * a particular x/y point on the map.
 */

void Sprite::goToLoc(double newx, double newy) {
	double delta_x = newx - posx;
	double delta_y = newy - posy;
//	double len = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	
	double angle = atan2(delta_y,delta_x);

	velx = cos(angle) * 0.05;
	vely = sin(angle) * 0.05;
}

// placeObject: this will put an object into the linked list it belongs 
// in, and if
// it had an old location, remove it from the wrong spot.

void Sprite::removeObjectFromMap() {
	Sprite *object = this;
	Sprite **map_loc = this->my_map_loc;

	myMap = NULL;
	if (map_loc) {
		if (*map_loc == NULL) {
			consoleView->addText("Sprite::removeObjectFromMap(): NULL *map_loc!");
			return;
		}

		if (*map_loc == object) {
			// it's the first item;
			*map_loc = object->tile_next;
			object->tile_next = 0;
			object->my_map_loc = 0;
		} else {
			// it's not the first item
			while ((*map_loc)->tile_next) {
				if ((*map_loc)->tile_next == object) {
					(*map_loc)->tile_next = object->tile_next;
					object->tile_next = 0;
					object->my_map_loc = 0;

					return;
				} else {
				map_loc = &((*map_loc)->tile_next);
				}
			}
		}
		
	} 

	object->tile_next = 0;
	object->my_map_loc = 0;
}

void Sprite::addObjectToMap(LPDBLNODE *map_loc) {
	this->tile_next = (*map_loc);
	(*map_loc) = this;
	this->my_map_loc = map_loc;
}

void Sprite::placeObject(Map *aMap) {
	Sprite *object = this;
	//	char s[120];
	// first calculate the tile position of the object
	
	int tile_x,tile_y;
	
	if ((object->posx < 0.0) || (object->posx > aMap->map_width)) {
		return; // it's off the map!
	}
	
	if ((object->posy < 0.0) || (object->posy > aMap->map_height)) {
		return;
	}
	
	tile_x = ((int)object->posx) / aMap->myTiles->tile_width;
	tile_y = ((int)object->posy) / aMap->myTiles->tile_height;
	
	if (!object->my_map_loc || (tile_x != object->old_tile_x) ||
		(tile_y != object->old_tile_y)) {
		// NOPE! it's not in the same location, so we need
		// to move it...
		//	sprintf(s,"placingObject at: t(%d.%d) r(%f,%f)\n",
		//		tile_x,tile_y,object->posx,object->posy);
		//	consoleView->addText(s);
		
		if (object->my_map_loc) {
			// first remove it from it's current location
			object->removeObjectFromMap();
		} 
		// now place it in the new location
		object->addObjectToMap(&((aMap->objects_rowindex[tile_y])[tile_x]));
		myMap = aMap;
		
		// and fix it's state...
		
		object->old_tile_x = tile_x;
		object->old_tile_y = tile_y;
		
	}
	
	if (this->my_map_loc == NULL) {
		consoleView->addText("place failed...");
	}
}

void Sprite::DrawClipped(int ul_x, int ul_y, RECT *clip_rect) {
	if (mySpriteTypeObj) {

		// we need to look up the correct image in the table
		mySpriteTypeObj->DrawAtClipped(this,(int)this->posx - ul_x, (int)this->posy - ul_y, clip_rect);
		
	} else {
		consoleView->addText("sprite without typeobj!");
	}
}

void Sprite::Die() {
	this->should_die = 1;
}

void Sprite::Draw(int ul_x, int ul_y) {
	if (mySpriteTypeObj) {

		// we need to look up the correct image in the table
		mySpriteTypeObj->DrawAt(this,(int)this->posx - ul_x, (int)this->posy - ul_y);
		
	} else {
		consoleView->addText("sprite without typeobj!");
	}
}	

	   
	   // *****************************
	   
