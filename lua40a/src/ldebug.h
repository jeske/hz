/*
** $Id: ldebug.h,v 1.1 2000/07/20 10:16:44 jeske Exp $
** Auxiliary functions from Debug Interface module
** See Copyright Notice in lua.h
*/

#ifndef ldebug_h
#define ldebug_h


#include "lobject.h"
#include "luadebug.h"


void luaG_callerror (lua_State *L, TObject *func);
void luaG_indexerror (lua_State *L, TObject *t);


#endif
