/*
** $Id: luadebug.h,v 1.1 2000/07/20 06:57:22 jeske Exp $
** Debuging API
** See Copyright Notice in lua.h
*/


#ifndef luadebug_h
#define luadebug_h

#ifdef __cplusplus
extern "C" {
#endif


#include "lua.h"

typedef lua_Object lua_Function;

typedef void (*lua_LHFunction) (int line);
typedef void (*lua_CHFunction) (lua_Function func, char *file, int line);

lua_Function lua_stackedfunction (int level);
void lua_funcinfo (lua_Object func, char **filename, int *linedefined);
int lua_currentline (lua_Function func);
char *lua_getobjname (lua_Object o, char **name);

lua_Object lua_getlocal (lua_Function func, int local_number, char **name);
int lua_setlocal (lua_Function func, int local_number);


extern lua_LHFunction lua_linehook;
extern lua_CHFunction lua_callhook;
extern int lua_debug;



#ifdef __cplusplus
}
#endif
#endif
