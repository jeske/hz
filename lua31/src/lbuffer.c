/*
** $Id: lbuffer.c,v 1.1 2000/07/20 06:57:22 jeske Exp $
** Auxiliar functions for building Lua libraries
** See Copyright Notice in lua.h
*/


#include <stdio.h>

#include "lauxlib.h"
#include "lmem.h"
#include "lstate.h"


/*-------------------------------------------------------
**  Auxiliar buffer
-------------------------------------------------------*/

#define BUFF_STEP	32

#define openspace(size)  if (L->Mbuffnext+(size) > L->Mbuffsize) Openspace(size)

static void Openspace (int size)
{
  LState *l = L;  /* to optimize */
  int base = l->Mbuffbase-l->Mbuffer;
  l->Mbuffsize *= 2;
  if (l->Mbuffnext+size > l->Mbuffsize)  /* still not big enough? */
    l->Mbuffsize = l->Mbuffnext+size;
  l->Mbuffer = luaM_realloc(l->Mbuffer, l->Mbuffsize);
  l->Mbuffbase = l->Mbuffer+base;
}


char *luaL_openspace (int size)
{
  openspace(size);
  return L->Mbuffer+L->Mbuffnext;
}


void luaL_addchar (int c)
{
  openspace(BUFF_STEP);
  L->Mbuffer[L->Mbuffnext++] = c;
}


void luaL_resetbuffer (void)
{
  L->Mbuffnext = L->Mbuffbase-L->Mbuffer;
}


void luaL_addsize (int n)
{
  L->Mbuffnext += n;
}


int luaL_newbuffer (int size)
{
  int old = L->Mbuffbase-L->Mbuffer;
  openspace(size);
  L->Mbuffbase = L->Mbuffer+L->Mbuffnext;
  return old;
}


void luaL_oldbuffer (int old)
{
  L->Mbuffnext = L->Mbuffbase-L->Mbuffer;
  L->Mbuffbase = L->Mbuffer+old;
}


char *luaL_buffer (void)
{
  return L->Mbuffbase;
}

