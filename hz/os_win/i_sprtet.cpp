// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

//
// i_sprtet.cpp
//
// windows specific version of the sprite draw interface
//

#include <ddraw.h> // for RECT, get rid of this!
#include "ddutil.h"


#include "i_video.h" // lpBackBuffer, lpDD
#include "..\spritet.h"
#include "..\VConsole.h" // for dbgMsg();

