// HZ Engine Source
// Copyright (C) 1998 David W. Jeske

// s_hz.cpp
//
// These are the C++ versions of the sprite class!!

#include <stdio.h>

#include <lua.h>
#include "main.h"
#include "misc.h"
#include "map.h"
#include "sprite.h"
#include "hash_map.h"
#include "s_hz.h"

// ------ CSPRITE

struct eqint
{
  bool operator()(int s1, int s2) const
  {
    return (s1 == s2);
  }
};

hash_map<int, const char *, hash<int>, eqint> int_to_string_table;


const char *int_to_string(int an_int) {
  const char *str = int_to_string_table[an_int];
  if (str == NULL) {
    str = (const char *)malloc(15);
    sprintf((char *)str,"%d",an_int);
    int_to_string_table[an_int] = str;
  }
  return str;
}


const char *CSprite::getPropertyStr(const char *propName) {
  return str_properties[propName];
}

CSprite::CSprite(SpriteList *aList,SpriteType *a_type, double x, double y, 
		 double vx, double vy): Sprite(aList,a_type,x,y,vx,vy) {
};

// --------------

SHZFlying::SHZFlying(SpriteList *aList,SpriteType *a_type, double x, double y, 
		     double vx, double vy) : CSprite(aList,a_type,x,y,vx,vy) {

  c_dest_dir = 30;
  c_centered = 0;
  str_properties["imgdir"] = "1";
}

void SHZFlying::handleCollision(Sprite *obj_hit) {
}

void SHZFlying::doTick(unsigned int tickDiff) {
  double tick_diff = tickDiff;
  float imgdir = atoi(str_properties["imgdir"]) - 1;
  const char *str;
  double ax, ay;
  double vx = velx, vy = vely;
  int MAX_SHIP_FRAME = 40;

  // compute object velocity

  if (c_centered) {
    // stop!
    ax = 0.0;
    ay = 0.0;
  } else {
    // accelerate in the control direction
    ax = Dirx[c_dest_dir];
    ay = Diry[c_dest_dir];
  }

  if (ax == 0.0) {
    // coast!
    if (vx > tick_diff/2000.0) {
      vx -= tick_diff/2000.0;
    } else if (vx < -tick_diff/2000.0) {
      vx += tick_diff/2000.0;
    } else {
      vx = 0.0;
    }
  } else {
    // apply the acceleration
    vx += (ax * tick_diff/4000.0);
  }

  if (ay == 0.0) {
    // coast!
    if (vy > tick_diff/2000.0) {
      vy -= tick_diff/2000.0;
    } else if (vy < -tick_diff/2000.0) {
      vy += tick_diff/2000.0;
    } else {
      vy = 0.0;
    }
  } else {
    // apply the acceleration
    vy += (ay * tick_diff/4000.0);
  }

  if (c_centered) {
    // if control is centered
    // ---------- stop here!!! -----------------
    velx = vx; vely = vy;
    return;
  }

  // compute our rotation
  
  if ((int)imgdir == (int)c_dest_dir) {
    // we're facing, so give acceleration boost!
    vx += (ay * tick_diff/2000.0);
    vy += (ay * tick_diff/2000.0);
  } else {
    // we need to turn according to the user request
    float cw_distance,ccw_distance;
    if (imgdir > c_dest_dir) {
      ccw_distance = imgdir - c_dest_dir;
      cw_distance = MAX_SHIP_FRAME - (ccw_distance);
    } else {
      cw_distance = c_dest_dir - imgdir;
      ccw_distance = MAX_SHIP_FRAME - (cw_distance);
    }
    float TURN_RATE = 1.0;
    float turn_vec = 0.0;
    
    if (cw_distance < ccw_distance) {
      if (cw_distance < TURN_RATE) {
	turn_vec = cw_distance;
      } else {
	turn_vec = TURN_RATE; // cw
      }
    } else {
      if (ccw_distance < TURN_RATE) {
	turn_vec = 0.0 - ccw_distance;
      } else {
	turn_vec = 0.0 - TURN_RATE; // ccw
      }
    }
    
    imgdir = (int)((double)imgdir + turn_vec);
    
    // printf("c_dest_dir %d,imgdir %f, turn_vec %f\n", c_dest_dir,imgdir,turn_vec);
    
    if (imgdir < 0) {
      imgdir += MAX_SHIP_FRAME;
    }
    if (imgdir >= MAX_SHIP_FRAME) {
      imgdir -= MAX_SHIP_FRAME;
    }
  }

  velx = vx; vely = vy; // save our computation

  // adjust for non-40 image sprites here
  
  str_properties["imgdir"] = int_to_string(imgdir+1); // +1 is because lua has arrays based at 1
}

void SHZFlying::doAITick(unsigned int tickDiff) {
}

int SHZFlying::handleEvent(struct input_event *ev) {
  if (ev->dev_type == DT_KEYBOARD) {
    if (ev->dev.keyboard.mask & KM_ASCII_KEY) {
      if (ev->dev.keyboard.ascii_code == 'd') {
	c_centered = 0;
	c_dest_dir = 10;
      } else if (ev->dev.keyboard.ascii_code == 'a') {
	c_centered = 0;
	c_dest_dir = 30;
      } else if (ev->dev.keyboard.ascii_code == 'w') {
	c_centered = 0;
	c_dest_dir = 0;
      } else if (ev->dev.keyboard.ascii_code == 'x') {
	c_centered = 0;
	c_dest_dir = 20;
      } else if (ev->dev.keyboard.ascii_code == 's') {
	c_centered = 1;
      }
    }
  }
}

void doAITick(unsigned int tickDiff);
int handleEvent(struct input_event *ev); // we want key events!
