/*
** $Id: ldo.h,v 1.1 2000/07/20 10:16:44 jeske Exp $
** Stack and Call structure of Lua
** See Copyright Notice in lua.h
*/

#ifndef ldo_h
#define ldo_h


#include "lobject.h"
#include "lstate.h"


/*
** macro to increment stack top.
** There must be always an empty slot at the L->stack.top
*/
#define incr_top {if (L->top == L->stack_last) luaD_checkstack(L, 1); L->top++;}


void luaD_init (lua_State *L, int stacksize);
void luaD_adjusttop (lua_State *L, StkId base, int extra);
void luaD_openstack (lua_State *L, StkId pos);
void luaD_lineHook (lua_State *L, StkId func, int line);
void luaD_call (lua_State *L, StkId func, int nResults);
void luaD_callTM (lua_State *L, const TObject *f, int nParams, int nResults);
int luaD_protectedrun (lua_State *L);
void luaD_checkstack (lua_State *L, int n);


#endif
