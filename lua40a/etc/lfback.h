/*
** lfback.h
** compatibility with old fallback system
** See Copyright Notice in lua.h
*/

#ifndef lfback_h
#define lfback_h

lua_Object lua_setfallback (lua_State *L, char *name, lua_CFunction fallback);
void lua_openfallback (lua_State *L);

#ifndef LUA_REENTRANT

#define lua_setfallback(name,fallback)	\
				(lua_setfallback)(lua_state,name,fallback)
#define lua_openfallback()	(lua_openfallback)(lua_state)

#endif

#endif
