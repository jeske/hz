// HZ Engine Source
// Copyright (C) 1998 by David W. Jeske

// SPRITEt_H
//
#ifndef SPRITET_H
#define SPRITET_H

#ifdef OS_UNIX
#include "translate.h"
#endif
#include <lua.h>

#include "i_sprtet.h" // sprite type image handling, defines the IMAGE struct

#ifndef SHORT
#define SHORT short int
#endif

// Sprite chunk data structures...

struct sprite_chunk_struct;

typedef struct {
	char name[20];
	struct sprite_chunk_struct *ptr;
} IMAGELISTENTRY;


enum index_type_enum { PREDEF_INDEX, LUA_VAR };

// IMAGE LIST
typedef struct {
	enum index_type_enum index_type;
	int predef_index_type;
	char luavar_name[30];
	int list_len;
	IMAGELISTENTRY list[1];
} IMAGELIST;


enum content_type_enum { TYPE_IMAGELIST, TYPE_IMAGE };

typedef struct sprite_chunk_struct {
	enum content_type_enum content_type;
	union {
		IMAGELIST im_list;
		IMAGE im_data;
	} content;
} SPRITECHUNK;


class Sprite;
// class SpriteType 
class SpriteType;

SpriteType *findSpriteType(char *name);
char *spriteTypeName(int num);

class SpriteType {
private:
	char myName[30];
	static void SpriteType::doBlit(RECT *dest, RECT *src, IMAGE *an_image); // platform specific blit function
	void SpriteType::loadImage(IMAGE *an_image, const char *image_name); // platform specific load image
public: 
	SPRITECHUNK *myImageList;  // this is public for now!
	char *name();
	void SpriteType::DrawRecurse(Sprite *spr_obj, lua_Object lua_obj, int x, int y, SPRITECHUNK *cur, RECT *clip_rect);
	void SpriteType::DrawAt(Sprite *spr_obj, lua_Object lua_obj, int x, int y);
	void SpriteType::DrawAtClipped(Sprite *spr_obj, lua_Object lua_obj, int x, int y, RECT *clip_rect);
	void SpriteType::parseSpriteTable(SPRITECHUNK **dest, lua_Object a_table);
	SpriteType(char *name, lua_Object anObj);
};


#endif SPRITET_H
