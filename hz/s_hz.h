// HZ Engine Source
// Copyright (C) 1998 David W. Jeske

#ifndef S_HZ_H
#define S_HZ_H 1

#include "hash_map.h"
#include "sprite.h"

struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};


class CSprite : public Sprite {
 protected:
  hash_map<const char*, const char *, hash<const char*>, eqstr> str_properties;
  hash_map<const char*, int, hash<const char*>, eqstr> int_properties;
 public:
  CSprite(SpriteList *aList,SpriteType *a_type, double x, double y, 
	  double vx, double vy);
  virtual const char *getPropertyStr(const char *propName); // get object property value
};

class SHZFlying : public CSprite {
 protected:
  // control variables
  int c_dest_dir;  // 0-39 requested direction
  int c_centered;  // are they pressing anykey?

  // state variables
  unsigned int damage; 

  // PROPERTIES (for defaults)
  // int max_damage 
  // int turn_rate         (in ticks)
  // int fire_rate         (in ticks)
  // double max_velocity

  // PROPERTIES (for rendering)
  // int imgdir            (0-39 images)

 public:
  SHZFlying(SpriteList *aList,SpriteType *a_type, double x, double y, 
	    double vx, double vy);
  virtual void doTick(unsigned int tickDiff); // move the object
  virtual void doAITick(unsigned int tickDiff);
  virtual int handleEvent(struct input_event *ev); // we want key events!
  virtual void handleCollision(Sprite *obj_hit);
};

#endif /* S_HZ_H */
