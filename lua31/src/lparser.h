/*
** $Id: lparser.h,v 1.1 2000/07/20 06:57:22 jeske Exp $
** Syntax analizer and code generator
** See Copyright Notice in lua.h
*/

#ifndef lparser_h
#define lparser_h

#include "lobject.h"
#include "lzio.h"


void luaY_codedebugline (int line);
TProtoFunc *luaY_parser (ZIO *z);
void luaY_error (char *s);
void luaY_syntaxerror (char *s, char *token);


#endif
