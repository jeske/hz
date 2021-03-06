// HZ Engine Source
// Copyright (C) 1999 by Brandon C. Long


//
// i_main.cpp
//
// This is the main entry point for the program, it should handle
// parsing command line args, setting up a primary display, initializing
// the game, and then doing the high-level input message handling for
// the OS.
//

#include <unistd.h>
#include <stdlib.h>

#include "i_video.h" // for initAppWindow()
#include "i_system.h" // for timer..
#include "i_console.h"
#include "net.h" // for init_server();
#include "main.h" // for initViews();


int usage (char *argv0)
{
  fprintf (stderr, "Herzog Zwei for Unix/X11, based on the Jeske Game Engine(TM)\n");
  fprintf (stderr, "\n");
  fprintf (stderr, "Usage:\n");
  fprintf (stderr, "    %s [-e] [-t] [-S] [-x]\n", argv0);
  fprintf (stderr, "  Where:\n");
  fprintf (stderr, "\n");
  fprintf (stderr, "    -e	Enable Emulation\n");
  fprintf (stderr, "    -t	Enable Testmode\n");
  fprintf (stderr, "    -S	Disable Sound\n");
  fprintf (stderr, "    -x	Enable Stress Test\n");
  fprintf (stderr, "    -f	Run full screen\n");
  fprintf (stderr, "\n");
  exit (-1);
}

extern int FullScreen;

int main (int argc, char *argv[])
{
  int c;

  I_Message ("Starting...\n");
  /* first we need to process command line arguments */
  while ((c = getopt (argc, argv, "etShxf")) != -1)
  {
    switch (c)
    {
      case 'S':
	bWantSound = FALSE;
	break;
      case 'f':
	FullScreen = 1;
	break;
      case 'h':
      case '?':
      default:
	usage (argv[0]);
	break;
    }
  }

  if( !I_InitVideo() )
  {
    return FALSE;
  }
  lastTickCount = i_time_ms();

  //    InitializeSound();

  ProgramState = PS_SPLASH;
  UpdateFrame();


  init_server();

  initViews();

  dwFrameTime = i_time_ms();

  UpdateFrame();
  while(I_EventLoop ())
  {
    if (bIsActive)
    {
//      I_Message ("UpdateFrame\n");
      UpdateFrame();

      // we should do some kind of speed independent "doTick" here 
    }
  }
}
