// HZ Engine Source
// Copyright 1998 (C) David W. Jeske

// spritet.cpp
// class SpriteType
//
//
// Spritet.cpp: this is the most recently written, and thus the better   
//    code there. It includes the code to parse my "lua sprite           
//    representation", and the associated data structures to store it   
//    in the C side. check out spritet.h, the data structures there are  
//    useful.

#include <lua.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef OS_WIN
#include "drawhndl.h" // for RestoreSurfaces()
#endif

#include "i_draw.h"
#include "view.h" // for console view
#include "main.h" // for console view

#include "sprite.h"

#include "spritet.h"

// a crappy hack for now...

#define MAX_SPRITETYPE 25
int cur_num_spritetype = 0;
typedef struct {
	const char name[30];
	SpriteType *type;
} SPRITETYPELIST;

SPRITETYPELIST spritetype_list[MAX_SPRITETYPE];

SpriteType *findSpriteType(const char *name) {
		SPRITETYPELIST *walker = spritetype_list;
		int curloc = 0;
		
		while (curloc < cur_num_spritetype) {

			if (!strcmp(walker->name,name)) {
				return (walker->type);
			} else {
				walker++;
				curloc++;
			}
		}
		return (NULL);
}

const char *spriteTypeName(int num) {
	if ((num < 0) || (num > cur_num_spritetype)) {
		return NULL;
	}

	return (spritetype_list[num].name);
}


void addSpriteType(const char *name, SpriteType *type) {
	if (cur_num_spritetype < MAX_SPRITETYPE) {
		strcpy((char *)spritetype_list[cur_num_spritetype].name,name);
		spritetype_list[cur_num_spritetype].type = type;
		cur_num_spritetype++;
	}
}

// @Layer is the only valid special type right now!

char *builtins[] = { "@Direction" , "@Layer" , "@Frame", NULL };

// if something isn't in the list, it's going to return the index of the
// NULL item (i.e. the last item in the list)

int lookup_builtin(char *name) {
	int cur = 0;

	while (builtins[cur] && strcmp(name,builtins[cur])) {
		cur++;
	}

	return (cur);

}

SPRITECHUNK *find_entry(IMAGELIST *a_list, const char *string) {
	int curloc = 0;

	while (curloc < a_list->list_len) {
		if (!strcmp(a_list->list[curloc].name,string)) {
			return (a_list->list[curloc].ptr);
		}

		curloc++;
	}

	return (NULL);
}

char *SpriteType::name() {
	return (myName);
}




void SpriteType::DrawRecurse(Sprite *spr_obj, int x, int y, SPRITECHUNK *cur, RECT *clip_rect) {
	IMAGELIST *a_list;

	if (cur == NULL) {
		dbgMsg(c_error,"DrawRecurse got NULL SPRITECHUNK *\n");
		return;
	}

	if (cur->content_type == TYPE_IMAGELIST) {
		a_list = &(cur->content.im_list);

		if (a_list->index_type == PREDEF_INDEX) {
			switch (a_list->predef_index_type) {	
#if 0
			case 0: // direction
				if (a_list->list_len<40 || ((spr_obj->facing_dir < 0) || (spr_obj->facing_dir>39))) {
					dbgMsg(l_info,"facing dir = %d\n",spr_obj->facing_dir);
					DrawRecurse(spr_obj, x, y, a_list->list[0].ptr, clip_rect); // chain down the first one
				} else {
					DrawRecurse(spr_obj, x, y, a_list->list[spr_obj->facing_dir].ptr, clip_rect);
				}
				break;
#endif
			case 1: // layer
				{ 
					int i;
					for (i = 0; i < a_list->list_len; i++) {
						DrawRecurse(spr_obj, x, y, a_list->list[i].ptr,clip_rect); // chain for each one
					}
				}
				break;
			case 2: // frame
			default: // unknown!
				DrawRecurse(spr_obj, x, y, a_list->list[0].ptr,clip_rect); // chain down the first one
				break;
			};

		} else if (a_list->index_type == OBJECT_PROPERTY_STR) {
		  const char *str_value = spr_obj->getPropertyStr(a_list->luavar_name);

		  if (str_value == NULL) {
				// var dosn't exist, just choose the first one
		    DrawRecurse(spr_obj, x, y, a_list->list[0].ptr,clip_rect);
		  } else {
		    DrawRecurse(spr_obj, x, y, find_entry(a_list,str_value),clip_rect);
		  }
		} else {
			dbgMsg(l_error,"unknown list index_type\n");
			return;
		}

	} else {
		// we found the image so draw it!
		IMAGE *an_image = &(cur->content.im_data);
		RECT dest;

		
		if (an_image->surf) {
		dbgMsg(c_error,"drawing image [%s] (%d,%d)\n",an_image->name,an_image->src.right, an_image->src.bottom);
		

		if (clip_rect == NULL) {
			// no clip!

			dest.left = x;
			dest.top = y;
			dest.right = dest.left + an_image->src.right;
			dest.bottom = dest.top + an_image->src.bottom;
			
			if ((x < 0) || (y < 0)) {
				dbgMsg(c_error,"couldn't draw [%s] at (%d,%d)\n",an_image->name,x,y);
				return;
			}
			this->doBlit(&dest, NULL, an_image);
		} else {
			int clip_dist;
			RECT src = an_image->src;
			// need to clip it!
			dest.left = x;
			dest.top = y;
			dest.right = dest.left + an_image->src.right;
			dest.bottom = dest.top + an_image->src.bottom;

			
			if ((dest.bottom < clip_rect->top) ||
				(dest.right < clip_rect->left) ||
				(dest.top > clip_rect->bottom) || 
				(dest.left > clip_rect->right)) {
				// completely out of the region
				dbgMsg(c_error,"couldn't draw [%s] at (%d,%d)\n",an_image->name,x,y);
				return;
			}

			if (dest.left < clip_rect->left) {
				clip_dist = clip_rect->left - dest.left;
				dest.left += clip_dist;
				src.left  += clip_dist;
				dbgMsg(c_error,"clipleft [%s] at (%d,%d)\n",an_image->name,x,y);
			}

			if (dest.top < clip_rect->top) {
				clip_dist = clip_rect->top - dest.top;
				dest.top += clip_dist;
				src.top += clip_dist;
				dbgMsg(c_error,"cliptop [%s] at (%d,%d)\n",an_image->name,x,y);
			}

			if (dest.right > clip_rect->right) {
				clip_dist = dest.right - clip_rect->right;
				dest.right -= clip_dist;
				src.right  -= clip_dist;
				dbgMsg(c_error,"clipright [%s] at (%d,%d)\n",an_image->name,x,y);
			}

			if (dest.bottom > clip_rect->bottom) {
				clip_dist = dest.bottom - clip_rect->bottom;
				dest.bottom -= clip_dist;
				src.bottom -= clip_dist;
				dbgMsg(c_error,"clipbottom [%s] at (%d,%d)\n",an_image->name,x,y);
			}
			
			
						
			this->doBlit(&dest, &src, an_image);
		}
	} else {
		dbgMsg(c_error,"no-image named [%s]\n",an_image->name);
	}
		

  }
}

void SpriteType::DrawAt(Sprite *spr_obj, int x, int y) {
	this->DrawRecurse(spr_obj, x,y,myImageList, NULL);
}


void SpriteType::DrawAtClipped(Sprite *spr_obj, int x, int y, RECT *clip_rect) {
	this->DrawRecurse(spr_obj,  x,y,myImageList, clip_rect);
}


void SpriteType::parseSpriteTable(SPRITECHUNK **dest, lua_Object a_tbl) {
	lua_Object next_fn, temp_ref, tbl_idx, tbl_val; 
	int table_len = 0;
	int curindex = 0;
	int cur_count = 0;
	int index_ref, value_ref;
	int table_ref;
	char *index_string;
	IMAGELIST *a_list = NULL; // in case this is a list
	IMAGE *an_image = NULL;   // in case this is an image

	// check that we have a table

	dbgMsg(c_excessive,"SpriteType::parseSpriteType() entered.\n");
	if (!lua_istable(a_tbl)) {
		lua_error("SpriteType::parseSpriteTable() passed non-table.");
	}

	lua_pushobject(a_tbl);
	table_ref = lua_ref(0);

	// get the index string
	{
		lua_Object index_string_obj;
		lua_pushobject(lua_getref(table_ref));
		lua_pushstring("IndexedBy");
		if (lua_isstring(index_string_obj = lua_gettable())) {
			index_string = lua_getstring(index_string_obj);
		} else {
			index_string = NULL;
		}
	}

	// count the entries (table_len), remember to account for the index string

	next_fn = lua_getglobal("next"); // get the "next(a,b);" function
	temp_ref = LUA_NOOBJECT; // set to nil



	do {

		lua_beginblock();
		lua_pushobject(lua_getref(table_ref));
		if (temp_ref == LUA_NOOBJECT) {
			lua_pushnil();
		} else {
			lua_pushobject(lua_getref(temp_ref));
		}
		if (lua_callfunction(next_fn)) {
			// an error occured!!!
			lua_error("error calling next() builtin Lua function");
		}
		
		// now get off the two return values
		
		tbl_idx = lua_getresult(1);  // index, should be a string or number
		tbl_val = lua_getresult(2);  // value, should be a table, unless it's the indexname
	
		if (lua_istable(tbl_val)) {
			// the value is another table, so store and count it
			table_len++;
		}
		
		if (!lua_isnil(tbl_idx)) {
			// we're not going to exit the loop this time!
			lua_pushobject(tbl_idx);
			temp_ref = lua_ref(0); // not locked
			
		}
		lua_endblock();		
	} while (!lua_isnil(tbl_idx));

	

	// check if we have another sprite chunk or an actual image

	if (index_string) {
		// we have another list of sprite chunks

		printf("Table(IndexedBy = %s) with %d elements\n",index_string,table_len);
		// allocate the table!!!

		// should this be "table_len - 1" below???
		(*dest) = (SPRITECHUNK *)malloc(sizeof(SPRITECHUNK) + (sizeof(IMAGELISTENTRY) * table_len)); 
		(*dest)->content_type = TYPE_IMAGELIST;
			
		a_list = &((*dest)->content.im_list);
		a_list->list_len = table_len;
		
		// check if the index is a builtin

		if (index_string[0] == '@') {
			// it's a builtin!
			a_list->index_type = PREDEF_INDEX;
			a_list->predef_index_type = lookup_builtin(index_string);
		} else {
			// it's an object property
			a_list->index_type = OBJECT_PROPERTY_STR;

			if (strlen(index_string) > sizeof(a_list->luavar_name)) {
				lua_error("IndexedBy name too big in table"); // should do better than this
			}
			strcpy(a_list->luavar_name, index_string);
		}


	// now go through the table AGAIN and do something which each element
	dbgMsg(c_excessive,"starting table parse\n");

	temp_ref = LUA_NOOBJECT; // set to nil
	curindex = 0;
	cur_count = 0;
	int reached_end = 0;

	

	do {
		lua_beginblock();
		lua_pushobject(lua_getref(table_ref));
		if (cur_count++ == 0) {
			dbgMsg(c_excessive,"DrawAt(): pushed nil\n");
			lua_pushnil();
		} else {
			lua_pushobject(lua_getref(temp_ref));
		}

		if (lua_callfunction(next_fn)) {
			// an error occured!!!
			lua_error("error calling next() builtin Lua function");
		}
			
		// now get off the two return values
			
		tbl_idx = lua_getresult(1);  // index, should be a string or number
		tbl_val = lua_getresult(2);  // value, should be a table, unless it's the indexname

		lua_pushobject(tbl_idx);
		index_ref = lua_ref(0);
		lua_pushobject(tbl_val);
		value_ref = lua_ref(0);

		if (lua_isnil(tbl_idx)) {
			// no more elements in the table...
			dbgMsg(c_excessive,"end of table reached\n");
			break; // exit the while loop!
		}
		
		if (lua_isstring(tbl_idx)) {
			reached_end = lua_isnil(lua_getref(index_ref)); // what's with this?
				
			dbgMsg(c_excessive,"handle element(%d/%d/%d): %s\n",curindex,table_len,
				reached_end,lua_getstring(lua_getref(index_ref)));
			// don't count it because it's a string
		} 
				
	
		if (lua_istable(lua_getref(value_ref))) {
				//the value is another table, so store and count it
			if (curindex < table_len) {
				if (lua_isstring(lua_getref(index_ref))) {
					strcpy(a_list->list[curindex].name,lua_getstring(lua_getref(index_ref))); // size check!!
					lua_beginblock();
					this->parseSpriteTable(&(a_list->list[curindex].ptr),lua_getref(value_ref)); // recurse
					lua_endblock();
				} else {
					dbgMsg(c_error,"non-string index on sprite chunk!\n");
					lua_error("can't allow sprite chunk with non-string index currently");
				}
			}
			curindex++;
				
		}

		temp_ref = index_ref;
		dbgMsg(c_excessive,"Finished parse (%d/%d/%d)\n",
				curindex,table_len,lua_isnil(lua_getref(temp_ref)));

		lua_endblock();
	} while ((!lua_isnil(lua_getref(temp_ref))) && (curindex < table_len));

	

	
	// and sort them

	} else {
		// we have an actual image
		char *image_name;

		
		// print it out ! 
//		lua_pushobject(a_table);
//		lua_call("printTables");

		lua_pushobject(lua_getref(table_ref));
		lua_pushnumber(1.0f);
		if ((image_name = lua_getstring(lua_gettable())) != NULL) {
			dbgMsg(c_excessive,"Loading image [%s]...\n",image_name);
		} else {
			lua_error("Failed loading image, first element not string");
		}

		// allocate the image

		(*dest) = (SPRITECHUNK *)malloc(sizeof(SPRITECHUNK));
		(*dest)->content_type = TYPE_IMAGE;

		an_image = &((*dest)->content.im_data);
		this->loadImage(an_image,image_name);
	}

	
	return;
}

SpriteType::SpriteType(const char *name, lua_Object anObj) {
	lua_Object image_table;
	lua_Object sprite_type_tbl;
		
	this->myImageList = 0;

	printf("Loading SpriteType(%s)...\n",name);

	// copy our name...
	strncpy(myName,name,28);
	myName[29] = 0;


	// first pull out the images table and send it to the parser

	lua_pushobject(anObj);
	lua_pushstring("VisualRep");
	image_table = lua_gettable();
	if (lua_istable(image_table)) {
		this->parseSpriteTable(&myImageList, image_table);
	} else {
		dbgMsg(l_error,"SpriteType::SpriteType(%s), no VisualRep\n",name);
	}

	// second, delete the images table to save space??? perhaps, perhaps not...

	lua_pushobject(anObj);
	lua_pushstring("VisualRep");
	lua_pushnil();
	lua_settable();

	// third, create the sprite template in lua

	sprite_type_tbl = lua_getglobal("sprite_types");
	if (!lua_istable(sprite_type_tbl)) {
		// we need to create it
		dbgMsg(c_info,"Creating sprite_types table\n");
		sprite_type_tbl = lua_createtable();
		lua_pushobject(sprite_type_tbl);
		lua_setglobal("sprite_types");

	}

	lua_pushobject(sprite_type_tbl);
	lua_pushstring(name);
	lua_pushobject(anObj);
	lua_settable();

	addSpriteType(name,this);
	printf("...done loading SpriteType\n");

}


// this is the nastiest bit of platform specific code left in here...

#ifdef OS_UNIX

void SpriteType::doBlit (RECT *dest, RECT *src, IMAGE *an_image) 
{
  I_doBlit (dest, src, an_image);
}

void SpriteType::loadImage(IMAGE *an_image, const char *image_name) 
{
  I_loadImage (an_image, image_name, 1);
}

#else 

#include "ddutil.h"

void SpriteType::doBlit(RECT *dest, RECT *src, IMAGE *an_image) {
	HRESULT ddrval;
	if (src == NULL) {
		src = &an_image->src;
	}
	do {
				
			/*
			 *	ddrval = lpBackBuffer->BltFast(x,y, an_image->surf, 
			 *	&(an_image->src), dwTransType  | DDBLTFAST_WAIT );
			 */
				
			ddrval = lpBackBuffer->Blt(dest, an_image->surf, 
							src, dwTransType | DDBLT_KEYSRC , NULL);

			if (ddrval != DD_OK) {
				if( ddrval == DDERR_SURFACELOST ) {
					an_image->surf->Restore();
				} else {
					dbgMsg(c_error,"failed drawing image [%s] (ERR = %d)",an_image->name, ddrval);
				}

			/*
			 * else if ( ddrval != DDERR_WASSTILLDRAWING ) {
			 *    dbgMsg(c_error,"DDERR_WASSTILLDRAWING");
			 *    Sleep(10);
			 *    fail_count++;
			 *    if (fail_count > 20) {
			 *        return;
			 *    }
			 * }
			 */

			}
		} while (ddrval == DDERR_WASSTILLDRAWING);
}

void SpriteType::loadImage(IMAGE *an_image, const char *image_name) {

		an_image->name = strdup(image_name);
		// load the image and put it somewhere!!!!
		an_image->surf = DDLoadBitmap(lpDD, image_name, &(an_image->src), 0, 0); /* dx, dy */

		if (an_image->surf) { // did the image load correctly? 
			DDSetColorKey( an_image->surf, CLR_INVALID );
		}
}


#endif
