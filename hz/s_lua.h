// HZ Engine Source
// Copyright (C) 1998 David W. Jeske

#ifndef S_LUA_H
#define S_LUA_H 1

#include "sprite.h"
#include <lua.h>

class LuaSprite : public Sprite {
public:
	int myLuaMirror; // the "ref" for my Lua Mirror    <-- client
	int myLuaServerMirror; // the "ref" for my Lua "server" Mirror   <-- server

	LuaSprite(SpriteList *aList,SpriteType *a_type, double x, double y, 
			double vx, double vy);

	virtual void SpriteTeardown(void);

	// callbacks
	virtual int canCollide(void);
	virtual void doTick(unsigned int tickDiff); // move the object
	virtual void doAITick(unsigned int tickDiff);
	virtual int handleEvent(struct input_event *ev); // we want key events!
	virtual void handleCollision(Sprite *obj_hit);
	virtual const char *getPropertyStr(const char *propName); // get object property value
        virtual void handleNearbyObjects(Sprite *nearby_objects[],int nearby_objects_count);
};

#if 0
class AISprite : public LuaSprite {
public:
	void doAITick(unsigned int tickDiff); // do the AI
	AISprite(SpriteList *aList, SHORT a_type, double x, double y, double vx, double vy);
	~AISprite();
	AISprite();
};
#endif


#endif /* S_LUA_H */

