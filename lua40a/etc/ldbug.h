/*
** ldbug.h
** Debugging API
** See Copyright Notice in lua.h
*/


#ifndef ldbug_h
#define ldbug_h

#include "lua.h"

typedef lua_Object lua_Function;

typedef void (*lua_LHFunction) (int line);
typedef void (*lua_CHFunction) (lua_Function func, const char *file, int line);

lua_Function lua_stackedfunction (int level);
void lua_funcinfo (lua_Object func, const char **source, int *linedefined);
int lua_currentline (lua_Function func);
const char *lua_getobjname (lua_Object o, const char **name);

lua_Object luaI_getlocal (lua_Function func, int local_number, const char **name);
int luaI_setlocal (lua_Function func, int local_number);

int lua_nups (lua_Function func);

lua_LHFunction luaI_setlinehook (lua_LHFunction func);
lua_CHFunction luaI_setcallhook (lua_CHFunction func);
int luaI_setdebug (int debug);

#define lua_setdebug		luaI_setdebug
#define lua_getlocal		luaI_getlocal
#define lua_setlocal		luaI_setlocal
#define lua_setlinehook		luaI_setlinehook
#define lua_setcallhook		luaI_setcallhook

#endif
