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

// ----------------- in memory representation for the image layer tree

struct sprite_chunk_struct;

typedef struct {
  char name[20];
  struct sprite_chunk_struct *ptr;
} IMAGELISTENTRY;


enum index_type_enum { PREDEF_INDEX, OBJECT_PROPERTY_STR };

// IMAGE LIST
typedef struct {
	enum index_type_enum index_type;
	int predef_index_type;
	char prop_name[30];
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


// --------------------------------------------------------------------

class Sprite;
class SpriteType;
class SpriteList;

SpriteType *findSpriteType(const char *name);
const char *spriteTypeName(int num);

class SpriteType {
 protected:
  char myName[30];
  static void SpriteType::doBlit(RECT *dest, RECT *src, IMAGE *an_image); // platform specific blit function
  void SpriteType::loadImage(IMAGE *an_image, const char *image_name); // platform specific load image

 public: 
  SPRITECHUNK *myImageList;  // this is public for now!
  
  SpriteType(const char *name);
  char *name(void);
  void DrawRecurse(Sprite *spr_obj, int x, int y, SPRITECHUNK *cur, RECT *clip_rect);
  void DrawAt(Sprite *spr_obj, int x, int y);
  void DrawAtClipped(Sprite *spr_obj, int x, int y, RECT *clip_rect);
  virtual Sprite *makeInstance(SpriteList *aList, double x, double y, double vx, double vy) = 0;
};

class LuaSpriteType : public SpriteType {
 public:
  LuaSpriteType(const char *name, lua_Object anObj);
  void parseLuaSpriteTable(SPRITECHUNK **dest, lua_Object a_table);
  virtual Sprite *makeInstance(SpriteList *aList, double x, double y, double vx, double vy);
};


#endif /* SPRITET_H */
