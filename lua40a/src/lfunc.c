/*
** $Id: lfunc.c,v 1.1 2000/07/20 10:16:44 jeske Exp $
** Auxiliary functions to manipulate prototypes and closures
** See Copyright Notice in lua.h
*/


#include <stdlib.h>

#define LUA_REENTRANT

#include "lfunc.h"
#include "lmem.h"
#include "lstate.h"

#define gcsizeproto(L, p)	numblocks(L, 0, sizeof(Proto))
#define gcsizeclosure(L, c)	numblocks(L, c->nelems, sizeof(Closure))



Closure *luaF_newclosure (lua_State *L, int nelems) {
  Closure *c = (Closure *)luaM_malloc(L, sizeof(Closure) +
                                         sizeof(TObject)*(nelems-1));
  c->next = L->rootcl;
  L->rootcl = c;
  c->marked = 0;
  c->nelems = nelems;
  L->nblocks += gcsizeclosure(L, c);
  return c;
}


Proto *luaF_newproto (lua_State *L) {
  Proto *f = luaM_new(L, Proto);
  f->code = NULL;
  f->lineDefined = 0;
  f->source = NULL;
  f->kstr = NULL;
  f->nkstr = 0;
  f->knum = NULL;
  f->nknum = 0;
  f->kproto = NULL;
  f->nkproto = 0;
  f->locvars = NULL;
  f->next = L->rootproto;
  L->rootproto = f;
  f->marked = 0;
  L->nblocks += gcsizeproto(L, f);
  return f;
}


void luaF_freeproto (lua_State *L, Proto *f) {
  L->nblocks -= gcsizeproto(L, f);
  luaM_free(L, f->code);
  luaM_free(L, f->locvars);
  luaM_free(L, f->kstr);
  luaM_free(L, f->knum);
  luaM_free(L, f->kproto);
  luaM_free(L, f);
}


void luaF_freeclosure (lua_State *L, Closure *c) {
  L->nblocks -= gcsizeclosure(L, c);
  luaM_free(L, c);
}


/*
** Look for n-th local variable at line `line' in function `func'.
** Returns NULL if not found.
*/
const char *luaF_getlocalname (const Proto *func,
                               int local_number, int line) {
  int count = 0;
  const char *varname = NULL;
  LocVar *lv = func->locvars;
  if (lv == NULL)
    return NULL;
  for (; lv->line != -1 && lv->line < line; lv++) {
    if (lv->varname) {  /* register */
      if (++count == local_number)
        varname = lv->varname->str;
    }
    else  /* unregister */
      if (--count < local_number)
        varname = NULL;
  }
  return varname;
}

