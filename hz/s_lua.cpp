// HZ Engine Source
// Copyright (C) 1998 David W. Jeske

// s_lua.cpp
//
// This is the lua-specific sprite subclass....

#include <lua.h>
#include "main.h"
#include "misc.h"
#include "map.h"

#include "s_lua.h"

LuaSprite::LuaSprite(SpriteList *aList,SpriteType *a_type, double x, double y, 
		     double vx, double vy) : Sprite(aList,a_type,x,y,vx,vy) {

  this->type = OBJ_LUA; 
  
  Sprite *new_node = this;
  
  if (new_node == NULL) {
    dbgMsg(c_error,"NULL ptr Sprite...\n");
    return;
  }
  
  if (mySpriteTypeObj) {
    obj_type_string = mySpriteTypeObj->name();
  } else {
    dbgMsg(c_error,"constructed sprite without typeobj!\n");
    obj_type_string = "unknown";
  }
  
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
void LuaSprite::SpriteTeardown() {

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
}
void LuaSprite::doTick(unsigned int tickDiff) {
  LuaSprite *ptr = this;
  Sprite *target = this;
  
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
}

void LuaSprite::handleCollision(Sprite *obj_hit) {
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
    
    if (obj_hit->type == OBJ_LUA) {
      LuaSprite *obj_hit_luaSprite = (LuaSprite *)obj_hit;
      lua_Object whoIHit = lua_getref(obj_hit_luaSprite->myLuaServerMirror);
      
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
    } else {	// we couldn't cast to a LuaSprite!!!
      // don't even notify about the collision
    }
    
  }
  lua_endblock();
}

// tells the world if we are 'nocollide = 1' or not...

int LuaSprite::canCollide() {
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

int ai_funcs = -1;

void LuaSprite::doAITick(unsigned int tickDiff) {
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

const char *LuaSprite::getPropertyStr(const char *propName) {
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

int LuaSprite::handleEvent(struct input_event *ev) { // we want key events!
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


