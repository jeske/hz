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

#include "osdep.h"
#include "i_video.h" // for initAppWindow()
#include "i_system.h" // for timer..
#include "i_console.h"
#include "i_draw.h"
#include "net.h" // for init_server();
#include "main.h" // for initViews();
#include "donuts.h" // various vars that should be elsewhere


int usage (char *argv0)
{
  fprintf (stderr, "BMP Viewer for Unix/X11\n");
  fprintf (stderr, "\n");
  fprintf (stderr, "Usage:\n");
  fprintf (stderr, "    %s <image.bmp>\n", argv0);
  fprintf (stderr, "  Where:\n");
  fprintf (stderr, "\n");
  fprintf (stderr, "    <image.bmp>	BMP to load\n");
  fprintf (stderr, "\n");
  exit (-1);
}

int main (int argc, char *argv[])
{
  char c;
  IMAGE image;

  I_Message ("Starting viewer\n");

  if (argc != 2)
    usage (argv[0]);

  I_Message ("I_InitVideo\n");
  if( !I_InitVideo() )
  {
    return FALSE;
  }

  I_loadImage (&image, argv[1], 0);
  I_doBlit (&image.src, &image);
  FlipScreen();

  while(I_EventLoop ());
}
