/*
 * Net.h
 */

#ifndef NET_H
#define NET_H

#include "map.h"

class Sprite;
struct crosslink_struct {
	char name[20];
	struct linker_struct *head;
};

struct linker_struct {
	struct linker_struct *next;
	Sprite *owner;

	struct linker_struct *crosslink;
	struct crosslink_struct *crosslink_owner;
};


struct DPlayDev_struct {
	int index;
	struct DPlayDev_struct *next;
	GUID guid;
	char name[80];
	int major_version;
	int minor_version;
};

extern struct DPlayDev_struct *dplay_head;


extern SpriteList *serverObjList;
extern Map *serverMap;


void init_server(void);
void tick_server(int tickDiff);

#endif // NET_H
