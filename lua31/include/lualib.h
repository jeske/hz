/*
** $Id: lualib.h,v 1.1 2000/07/20 06:57:22 jeske Exp $
** Lua standard libraries
** See Copyright Notice in lua.h
*/


#ifndef lualib_h
#define lualib_h

#include <lua.h>

#ifdef __cplusplus
extern "C" {
#endif




void lua_iolibopen   (void);
void lua_strlibopen  (void);
void lua_mathlibopen (void);




/* To keep compatibility with old versions */

#define iolib_open			lua_iolibopen
#define strlib_open			lua_strlibopen
#define mathlib_open		lua_mathlibopen



/* auxiliar functions (private) */

int luaI_singlematch (int c, char *p, char **ep);

#ifdef __cplusplus
}
#endif
#endif

