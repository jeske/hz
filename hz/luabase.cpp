// HZ Engine Source
// Copyright (C) 1998 David W. Jeske


#include "luabase.h"
#include <lua.h>
#include "vconsole.h"


LuaBase::LuaBase() {

}

LuaBase::~LuaBase() {
}

// static dispatch implementations

void LuaBase::slfb_gettable(void) {
	lua_Object param1 = lua_getparam(1);
	LuaBase *obj;

	if (!lua_isuserdata(param1)) {
		lua_error("bad arg1 to LuaBase::slfb_gettable()");
	}

	obj = (LuaBase *)lua_getuserdata(param1);

	obj->lfb_gettable(lua_getparam(2));
}

void LuaBase::slfb_gc(void) {
	lua_Object param1 = lua_getparam(1);
	LuaBase *obj;

	if (!lua_isuserdata(param1)) {
		lua_error("bad arg1 to LuaBase::slfb_gc()");
	}

	obj = (LuaBase *)lua_getuserdata(param1);

	obj->lfb_gc();
}
// default implementations

// lfb_gettable(index)

void LuaBase::lfb_gettable(lua_Object index) {
	lua_error("LuaBase::lfb_gettable(): unhandled gettable");
	return;
}

void LuaBase::lfb_gc() {
	dbgMsg(c_error,"LuaBase::lfb_gc(), unhandled garbage collect");
	return;
}

