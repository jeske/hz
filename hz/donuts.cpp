// HZ Engine
// Copyright (C) 1998 David W. Jeske


// Donuts.cpp
//
// Originally part of Microsoft DirectX SpaceDonuts demo, 
// but all that really remains is the filename... :)
//



#include <stdio.h>
#include <stdlib.h>
#include "osdep.h"
#ifdef OS_WIN
#include <io.h>
#include "resource.h"
#include "DrawHndl.h"
#endif
#include "i_draw.h"
#include "i_video.h"
#include "i_system.h" // for i_time_ms()

#include "main.h"
#include "donuts.h"
#include "view.h"
#include "sprite.h"
#include "spritet.h"
#include "misc.h"
#include "game.h"
#include "map.h"
#include "net.h"

// START ORIGINAL DONUTS STUFF!!!

