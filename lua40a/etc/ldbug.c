/*
** ldbug.c
** compatibility with old debug API
** See Copyright Notice in lua.h
*/

#include <stdlib.h>

#include "lua.h"
#include "luadebug.h"
#include "ldbug.h"

#undef lua_setdebug
#undef lua_getlocal
#undef lua_setlocal
#undef lua_setlinehook
#undef lua_setcallhook

#define	L	lua_state


/* -- stack and function information --------------------------------------- */

lua_Function lua_stackedfunction (int level) {
  lua_Debug ar;
  lua_getstack(L,level,&ar);
  return ar._func;
}

void lua_funcinfo (lua_Object func, const char **source, int *linedefined) {
  lua_Debug ar;
  ar._func=func;
  lua_getinfo(L,"S",&ar);
  *source=ar.source;
  *linedefined=ar.linedefined;
}

int lua_currentline (lua_Function func) {
  lua_Debug ar;
  ar._func=func;
  lua_getinfo(L,"l",&ar);
  return ar.currentline;
}

const char *lua_getobjname (lua_Object o, const char **name) {
  lua_Debug ar;
  ar._func=o;
  lua_getinfo(L,"n",&ar);
  *name=ar.name;
  return ar.what;
}

int luaI_setdebug (int debug) {
  return lua_setdebug(L,debug);
}


/* -- manipulating local variables ----------------------------------------- */

lua_Object luaI_getlocal (lua_Function func, int local_number, const char **name) {
  lua_Debug ar;
  lua_Localvar v;
  ar._func=func;
  v.index=local_number;
  if (!lua_getlocal(L,&ar,&v)) return LUA_NOOBJECT;
  *name=v.name;
  return v.value;
}

int luaI_setlocal (lua_Function func, int local_number) {
  lua_Debug ar;
  lua_Localvar v;
  ar._func=func;
  v.index=local_number;
  v.value=lua_getparam(1);
  return lua_setlocal(L,&ar,&v);
}


/* -- line hook ------------------------------------------------------------ */

static lua_LHFunction linehook=NULL;

static void do_linehook (lua_State *L, lua_Debug *ar) {
  linehook(ar->currentline);
}

lua_LHFunction luaI_setlinehook (lua_LHFunction func) {
  lua_LHFunction old=linehook;
  linehook=func;
  lua_setcallhook(L,do_linehook);
  return old;
}


/* -- call hook ------------------------------------------------------------ */

static lua_CHFunction callhook=NULL;

static void do_callhook (lua_State *L, lua_Debug *ar) {
  if (ar->event[0]=='c') {
    lua_getinfo(L,"S",ar);
    callhook(ar->_func,ar->source,ar->linedefined);
  }
  else
    callhook(LUA_NOOBJECT,"(return)",0);
}

lua_CHFunction luaI_setcallhook (lua_CHFunction func) {
  lua_CHFunction old=callhook;
  callhook=func;
  lua_setcallhook(L,do_callhook);
  return old;
}
