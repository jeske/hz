/*
** $Id: lgc.h,v 1.1 2000/07/20 10:16:44 jeske Exp $
** Garbage Collector
** See Copyright Notice in lua.h
*/

#ifndef lgc_h
#define lgc_h


#include "lobject.h"


void luaC_checkGC (lua_State *L);
void luaC_collect (lua_State *L, int all);


#endif
