/*
** $Id: lbuiltin.h,v 1.1 2000/07/20 10:16:44 jeske Exp $
** Built-in functions
** See Copyright Notice in lua.h
*/

#ifndef lbuiltin_h
#define lbuiltin_h

#include "lua.h"

void luaB__ALERT (lua_State *L);
void luaB__ERRORMESSAGE (lua_State *L);
void luaB_assert (lua_State *L);
void luaB_call (lua_State *L);
void luaB_collectgarbage (lua_State *L);
void luaB_copytagmethods (lua_State *L);
void luaB_dofile (lua_State *L);
void luaB_dostring (lua_State *L);
void luaB_error (lua_State *L);
void luaB_foreach (lua_State *L);
void luaB_foreachi (lua_State *L);
void luaB_foreachvar (lua_State *L);
void luaB_getglobal (lua_State *L);
void luaB_getn (lua_State *L);
void luaB_gettagmethod (lua_State *L);
void luaB_newtag (lua_State *L);
void luaB_next (lua_State *L);
void luaB_nextvar (lua_State *L);
void luaB_print (lua_State *L);
void luaB_rawgetglobal (lua_State *L);
void luaB_rawgettable (lua_State *L);
void luaB_rawsetglobal (lua_State *L);
void luaB_rawsettable (lua_State *L);
void luaB_setglobal (lua_State *L);
void luaB_settag (lua_State *L);
void luaB_settagmethod (lua_State *L);
void luaB_sort (lua_State *L);
void luaB_tag (lua_State *L);
void luaB_tinsert (lua_State *L);
void luaB_tonumber (lua_State *L);
void luaB_tostring (lua_State *L);
void luaB_tremove (lua_State *L);
void luaB_type (lua_State *L);

void luaB_predefine (lua_State *L);


#endif
