/*
** $Id: lapi.h,v 1.1 2000/07/20 06:57:22 jeske Exp $
** auxiliar functions from Lua API
** See Copyright Notice in lua.h
*/

#ifndef lapi_h
#define lapi_h


#include "lua.h"
#include "lobject.h"


TObject *luaA_Address (lua_Object o);
void luaA_pushobject (TObject *o);
void luaA_packresults (void);
int luaA_passresults (void);

#endif
