// HZ Engine Source
// Copyright (C) 1998 by David W. Jeske

#ifndef HZ_LUABASE_H
#define HZ_LUABASE_H

// base class which handles lua behavior

#include <lua.h>

class LuaBase {
protected:	
	LuaBase();
	~LuaBase();
	virtual void lfb_gettable(lua_Object index); 
	virtual void lfb_gc(void);
public:
	static void slfb_gettable(void);
	static void slfb_gc(void);
};

#endif
