/*
** $Id: lualib.h,v 1.1 2000/07/20 10:16:44 jeske Exp $
** Lua standard libraries
** See Copyright Notice in lua.h
*/


#ifndef lualib_h
#define lualib_h

#include "lua.h"

void lua_iolibopen (lua_State *L);
void lua_strlibopen (lua_State *L);
void lua_mathlibopen (lua_State *L);
void lua_dblibopen (lua_State *L);


void lua_userinit (lua_State *L);


/* 
** ===============================================================
** Macros for single-state use
** ===============================================================
*/

#ifndef LUA_REENTRANT

#define lua_iolibopen()		(lua_iolibopen)(lua_state)
#define lua_strlibopen()	(lua_strlibopen)(lua_state)
#define lua_mathlibopen()	(lua_mathlibopen)(lua_state)
#define lua_dblibopen()		(lua_dblibopen)(lua_state)
#define lua_userinit()		(lua_userinit)(lua_state)

#endif



/* Auxiliary functions (private) */

const char *luaI_classend (lua_State *L, const char *p);
int luaI_singlematch (int c, const char *p, const char *ep);

#endif
