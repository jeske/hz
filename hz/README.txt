


------------------------------------------------------------------------

                               HZ Engine
                       David W. Jeske <jeske@chat.net>

------------------------------------------------------------------------

0. Introduction

This package contains the HZ Engine, written by David W. Jeske. 
This engine is a sprite-based 2d game engine designed to use 
hardware 2d acceleration to get fast performance at resolutions 
up to 1024x768x16bits using Windows DirectDraw. 


The HZ Engine is Copyright (C) 1998 by David W. Jeske 
  Linux Port (os_unix) Copyright Brandon C. Long
  Original artwork is Copyright Barry Gillhespy
  Some misc artwork is borrowed (without permission) from 
    other sources.

Homepage: http://www.chat.net/~jeske/Projects/HZ/
Author:   David W. Jeske <jeske@chat.net>

1. License

The public source code release is currently under the GPL 
(Gnu Public License). You should have received a copy of the
GPL along with this source kit. However, if you did not, please
visit:

   http://www.gnu.org/copyleft/gpl.html

2. Motivations and Goals

There are two motivations for writing this engine. If you choose
to help contribute to the code, I hope you agree with these causes.

1 - One of the earliest real-time action strategy games ever made
  was called Herzog Zwei (pronounced "he-a-tsuk zvei", means "Lord Two"
  in German). It was a cartridge for the Sega Genesis which a few of
  us are still proud to have ahold of. You can read all about why
  Herzog Zwei is a great game on my webpage:

   http://www.chat.net/~jeske/Projects/HZ/docs/why_is_hz_great.html 

2 - I spent time working at both S3 and 3Dfx (PC graphics chip companies)
  when each of them were hot companies with hot products. PC 3D 
  graphics has taken off, with many PCs now having 16 or 32MB of video
  RAM for rending complex 3D scenes. Yet 2D game engines have never
  made use of all the 2d blitting horsepower these graphics chips 
  provide. Everyone in the 2d real-time action strategy world is 
  converting their games into true 3D, with some form of 2d-esq view
  management (ala Myth, Dark Reign 2, Warcraft III, etc). I want to
  play a 800x600x16bitx70fps 2d RTS game. If you download and run this
  engine, you'll see how easily possible that is on modern hardware.

3. Developer Info/Installation

This source kit contains everything you need to compile and run HZ.
If you have the windows kit, it comes with a full installation of
Mingw (Gcc for windows), the appropriate include files, and directx
libraries. If you have the Linux kit, you just have the HZ source.
On Windows, you'll need to run c:\local\startshell.bat, and then
you should be able to "make" first inside lua31, and then inside 
the c:\hz\hz-files\hz directory. If you have any problems with the
build, email me at <jeske@chat.net>.

NOTE: The reason it compiles so slow (on windows) is that gcc does
      not yet support precompiled headers and the windows header
      files are quite large. Perhaps someday they'll fix this.

4. Acknowledgements

The engine has been ported to XWindows by Brandon Long. Specifically 
Linux, but should run on other *NIX. It dosn't get nearly the stunning
performance out of Linux/X, but it works and that's cool enough.

