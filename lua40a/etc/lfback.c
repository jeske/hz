/*
** lfback.c
** compatibility with old fallback system
** See Copyright Notice in lua.h
*/

/*
* There are two implementations of the old fallback system.
* One is in Lua, on top of tag methods (see etc/setfallback.lua), which should
* suffice for Lua code that uses the setfallback predefined function.
* The other is this file, which is needed for C code that uses lua_setfallback.
* This file also exports a C implementation of setfallback.
* To use setfallback as a predefined function, call lua_openfallback().
*/

#include <stdio.h>

#define LUA_REENTRANT

#include "lapi.h"
#include "lfback.h"
#include "lauxlib.h"
#include "ldo.h"
#include "lstring.h"
#include "ltm.h"


static void errorFB (lua_State *L) {
  lua_Object o = lua_getparam(L, 1);
  if (lua_isstring(L, o))
    fprintf(stderr, "lua: %s\n", lua_getstring(L, o));
  else
    fprintf(stderr, "lua: unknown error\n");
}


static void nilFB (lua_State *L) {
  UNUSED(L);
}


static void typeFB (lua_State *L) {
  lua_error(L,"unexpected type");
}


static void fillvalids (lua_State *L, IMS e, TObject *func) {
  int t;
  for (t=TAG_USERDATA; t<=TAG_NIL; t++)
    if (luaT_validevent(t, e))
      *luaT_getim(L, t, e) = *func;
}


static void setfallback (lua_State *L) {
  static const char *const oldnames [] =
	{"error", "getglobal", "arith", "order", NULL};
  TObject oldfunc;
  lua_CFunction replace;
  const char *name = luaL_check_string(L, 1);
  lua_Object func = lua_getparam(L, 2);
  luaL_arg_check(L, lua_isfunction(L, func), 2, "function expected");
  switch (luaL_findstring(name, oldnames)) {
    case 0: {  /* old error fallback */
      TObject *em = &(luaS_assertglobalbyname(L, "_ERRORMESSAGE")->value);
      oldfunc = *em;
      *em = *func;
      replace = errorFB;
      break;
    }
    case 1:  /* old getglobal fallback */
      oldfunc = *luaT_getim(L, TAG_NIL, IM_GETGLOBAL);
      *luaT_getim(L, TAG_NIL, IM_GETGLOBAL) = *func;
      replace = nilFB;
      break;
    case 2: {  /* old arith fallback */
      int i;
      oldfunc = *luaT_getim(L, TAG_NUMBER, IM_POW);
      for (i=IM_ADD; i<=IM_UNM; i++)  /* ORDER IM */
        fillvalids(L, i, func);
      replace = typeFB;
      break;
    }
    case 3: {  /* old order fallback */
      int i;
      oldfunc = *luaT_getim(L, TAG_NIL, IM_LT);
      for (i=IM_LT; i<=IM_LT; i++)  /* ORDER IM */
        fillvalids(L, i, func);
      replace = typeFB;
      break;
    }
    default: {
      int e;
      if ((e = luaL_findstring(name, luaT_eventname)) >= 0) {
        oldfunc = *luaT_getim(L, TAG_NIL, e);
        fillvalids(L, e, func);
        replace = (e == IM_GC || e == IM_INDEX) ? nilFB : typeFB;
      }
      else {
        luaL_verror(L, "`%.50s' is not a valid fallback name", name);
        replace = NULL;  /* to avoid warnings */
      }
    }
  }
  if (oldfunc.ttype != TAG_NIL)
    luaA_pushobject(L, &oldfunc);
  else
    lua_pushcfunction(L, replace);
}


static void do_unprotectedrun (lua_State *L, lua_CFunction f, int nParams, int nResults) {
  StkId base = L->top - nParams;
  luaD_openstack(L, base);
  base->ttype = TAG_CCLOSURE;
  base->value.cl->f.c = f;
  luaD_call(L, base, nResults);
}

/* --- public interface ---------------------------------------------------- */

/*
** API: set a function as a fallback
*/

lua_Object lua_setfallback (lua_State *L, char *name, lua_CFunction fallback) {
  lua_pushstring(L, name);
  lua_pushcfunction(L, fallback);
  do_unprotectedrun(L, setfallback, 2, 1);
  return luaA_putObjectOnTop(L);
}

/*
* register setfallback as a predefined function
*/

void lua_openfallback (lua_State *L) {
  lua_register(L,"setfallback", setfallback);
}
