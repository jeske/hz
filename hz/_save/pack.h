#ifndef PACK_H
#define PACK_H


/*
 * Pack and PackManager
 *
 * These class will be generic data-retrieval classes. This will abstract the conecpt
 * of getting data from "PCK" (Pack) files. In the beginning I will likely
 * make a Pack subclass which will just use a straight directory
 * heirarchy. The final shipped version should probably be a Pack subclass
 * which can read a compressed archive of some sort. Each could be usefull in
 * the final version though. PackManager will just Manage Packs.
 */
#include "Rsc.h" // the Resource handlers 


/* 
 * class PackManager
 * 
 * This holds Packs in a priority order and serves 
 * resources out of those Packs in that order.
 *
 * Resources will be accessed by name in a heirarchy. There is limited
 * support for certain datatypes. Ultimately it would be good to use
 * RTTI (Run-Time Type Information) extensions to C++ to return datatype
 * handlers for specific types. However, this may make it non-portable.
 * For now I'll subclass this into a "TypedPackManager" which will have accessor
 * methods for different resource types.
 *
 */


class Pack; // the Pack storage class

class PackManager {
	protected:
		Pack *firstPack;
	public:
		
    // PackManagement methods:	

		// if before_this is null, the last
		addPackBefore(Pack *to_add,Pack *before_this); 

		// if cur_pack is null, the first pack
		Pack *nextPack(Pack *cur_pack); 
		Pack *packNamed(char *pack_name);
	
    // Resource Accessing

		Resource *resourceWithName(char *name);

};

class TypedPackManager : public PackManager {
	public:
		ImageResource *imageRscWithName(char *name);
		AnimationResource *animationRscWithName(char *name);
		SoundResource *soundRscWithName(char *sound);
};


/*
 * class Pack
 *
 * This holds resources. It will most commonly be accessed
 * through a PackManager, however, it could be accesed independently
 * also.
 *
 
 */



class Pack {
protected:
public:
	Pack *next;
	Pack *prev;
	virtual Resource *resourceWithName(char *name);
};


class DirPack : public Pack {
protected:
	char *full_start_path; // the path to the start of the dirpack
public:
	virtual Resource *resourceWithName(char *name);
	DirPack(char *rel_start_path); // give it the dirname for the dirpack
	~DirPack();
}


#endif // PACK_H
