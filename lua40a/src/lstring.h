/*
** $Id: lstring.h,v 1.1 2000/07/20 10:16:44 jeske Exp $
** String table (keep all strings handled by Lua)
** See Copyright Notice in lua.h
*/

#ifndef lstring_h
#define lstring_h


#include "lobject.h"
#include "lstate.h"


#define NUM_HASHSTR     32
#define NUM_HASHUDATA   31
#define NUM_HASHS (NUM_HASHSTR+NUM_HASHUDATA)


/*
** any taggedstring with mark>=FIXMARK is never collected.
** Marks>=RESERVEDMARK are used to identify reserved words.
*/
#define FIXMARK		2
#define RESERVEDMARK	3


void luaS_init (lua_State *L);
void luaS_resize (lua_State *L, stringtable *tb, int newsize);
TString *luaS_createudata (lua_State *L, void *udata, int tag);
void luaS_freeall (lua_State *L);
void luaS_free (lua_State *L, TString *ts);
TString *luaS_newlstr (lua_State *L, const char *str, long l);
TString *luaS_new (lua_State *L, const char *str);
TString *luaS_newfixed (lua_State *L, const char *str);
GlobalVar *luaS_assertglobal (lua_State *L, TString *ts);
GlobalVar *luaS_assertglobalbyname (lua_State *L, const char *name);
int luaS_globaldefined (lua_State *L, const char *name);


#endif
