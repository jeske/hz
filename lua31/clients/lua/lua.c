/*
** $Id: lua.c,v 1.1 2000/07/20 06:57:22 jeske Exp $
** Lua stand-alone interpreter
** See Copyright Notice in lua.h
*/


#include <stdio.h>
#include <string.h>

#include "lua.h"
#include "luadebug.h"
#include "lualib.h"


#ifndef OLD_ANSI
#include <locale.h>
#else
#define setlocale(a,b)  0
#endif

#ifdef _POSIX_SOURCE
#include <unistd.h>
#else
#define isatty(x)       (x==0)  /* assume stdin is a tty */
#endif


static void print_message (void)
{
  fprintf(stderr,
"Lua: command line options:\n"
"  -v       print version information\n"
"  -d       turn debug on\n"
"  -e stat  dostring `stat'\n"
"  -q       interactive mode without prompt\n"
"  -i       interactive mode with prompt\n"
"  -        executes stdin as a file\n"
"  a=b      sets global `a' with string `b'\n"
"  name     dofile `name'\n\n");
}


static void assign (char *arg)
{
  if (strlen(arg) >= 500)
    fprintf(stderr, "lua: shell argument too long");
  else {
    char buffer[500];
    char *eq = strchr(arg, '=');
    lua_pushstring(eq+1);
    strncpy(buffer, arg, eq-arg);
    buffer[eq-arg] = 0;
    lua_setglobal(buffer);
  }
}

#define BUF_SIZE	512

static void manual_input (int prompt)
{
  int cont = 1;
  while (cont) {
    char buffer[BUF_SIZE];
    int i = 0;
    lua_beginblock();
    if (prompt)
      printf("%s", lua_getstring(lua_getglobal("_PROMPT")));
    for(;;) {
      int c = getchar();
      if (c == EOF) {
        cont = 0;
        break;
      }
      else if (c == '\n') {
        if (i>0 && buffer[i-1] == '\\')
          buffer[i-1] = '\n';
        else break;
      }
      else if (i >= BUF_SIZE-1) {
        fprintf(stderr, "lua: argument line too long\n");
        break;
      }
      else buffer[i++] = c;
    }
    buffer[i] = 0;
    lua_dostring(buffer);
    lua_endblock();
  }
  printf("\n");
}

#ifdef _POSIX_SOURCE

#include <sys/time.h>

void C_utime(void) {
  struct timeval curtime;
  int ret;
  double nowfp, nowip;

  ret = gettimeofday(&curtime,NULL);

  if (ret == 0) {
    nowfp = (double)(curtime.tv_usec) / 1000000.0;
    nowip = (double)(curtime.tv_sec);

    lua_pushnumber(nowip);
    lua_pushnumber(nowfp);
  } else {
    lua_error("call to gettimeofday() failed");
  }
}

void C_time(void) {
  time_t now = time(NULL);

  lua_pushnumber((double)now);
}

#endif


int main (int argc, char *argv[])
{
  int i;
  setlocale(LC_ALL, "");
  lua_iolibopen();
  lua_strlibopen();
  lua_mathlibopen();
  lua_pushstring("> "); lua_setglobal("_PROMPT");
#ifdef _POSIX_SOURCE
  lua_register("utime",C_utime);
  lua_register("time",C_time);
#endif

  if (argc < 2) {  /* no arguments? */
    if (isatty(0)) {
      printf("%s  %s\n", LUA_VERSION, LUA_COPYRIGHT);
      manual_input(1);
    }
    else
      lua_dofile(NULL);  /* executes stdin as a file */
  }
  else for (i=1; i<argc; i++) {
    if (argv[i][0] == '-') {  /* option? */
      switch (argv[i][1]) {
        case 0:
          lua_dofile(NULL);  /* executes stdin as a file */
          break;
        case 'i':
          manual_input(1);
          break;
        case 'q':
          manual_input(0);
          break;
        case 'd':
          lua_debug = 1;
          break;
        case 'v':
          printf("%s  %s\n(written by %s)\n\n",
                 LUA_VERSION, LUA_COPYRIGHT, LUA_AUTHORS);
          break;
        case 'e':
          i++;
          if (lua_dostring(argv[i]) != 0) {
            fprintf(stderr, "lua: error running argument `%s'\n", argv[i]);
            return 1;
          }
          break;
        default:
          print_message();
          exit(1);
      }
    }
    else if (strchr(argv[i], '='))
      assign(argv[i]);
    else {
      int result = lua_dofile(argv[i]);
      if (result) {
        if (result == 2) {
          fprintf(stderr, "lua: cannot execute file ");
          perror(argv[i]);
        }
        exit(1);
      }
    }
  }
#ifdef DEBUG
  lua_close();
#endif
  return 0;
}

