/*
 * Pack and PackManager
 *
 */

#include "Rsc.h"  // Resource, and typed Resource subclasses
#include "Pack.h" // Pack, PackManager



PackManager::PackManager() {
	firstPack = NULL;
}


// PackManager::addPackBefore
//
// If "before_this" is NULL or not in the list, it'll end up at the end...
//
PackManager::addPackBefore(Pack *to_add, Pack *before_this) {
	if (firstPack) {
		// there is a Pack so go looking
		Pack *walker = firstPack;
		
		while ((walker->next) && (walker->next!=before_this)) {
			walker = walker->next;
		}

		if (walker->next) {
			walker->next->prev = to_add;
		}
		to_add->next = walker->next;
		to_add->prev = walker;
		walker->next = to_add;

	} else {
		// there is no pack, so just stick it at the front

		to_add->next = NULL;
		to_add->prev = NULL;
		firstPack = to_add;
	}
}

//
// Pack *PackManager::nextPack(Pack *cur_pack)
//
// This lets us walk the pack list.. feed in a NULL and you
// get the beginning of the list.
//

Pack *PackManager::nextPack(Pack *cur_pack) {
	Pack *retval;

	if (cur_pack && firstPack) {
		// yes, there is a firstPack and no, they don't want it.
		Pack *walker = firstPack;

		while ((walker->next) && (walker != cur_pack)) {
			walker = walker->next;
		}

		 retval = walker->next;
	} else {
		// nope, just give them the first one (which might be NULL)
		retval = firstPack;
	}

	return (retval);
}


Pack *PackManager::packNamed(char *pack_name) {
	Pack *walker = firstPack;


	while (walker && strcmp(pack_name,walker->name())) {
		walker = walker->next;
	}

	return (walker);
}

Resource *PackManager::resourceWithName(char *name) {
	Pack *walker = firstPack;
	Resource *retval;

	while (walker && !(retval = walker->resourceWithName(name))) {
		walker = walker->next;
	}

	return (retval);
}



ImageResource TypedPackManager::imageRscWithName(char *name) {
	return (ImageResource(this->resourceWithName(name)));
}

AnimationResource *animationRscWithName(char *name) {
	return (AnimationResource(this->resourceWithName(name)));
}

SoundResource *soundRscWithName(char *sound) {
	return (SoundResource(this->resourceWithName(name)));
}


/*
 * DirPack
 *
 */

Resource DirPack::resourceWithName(char *name) {
	return (new Resource(name));
}


DirPack::DirPack(char *rel_start_path) {
	full_start_path = malloc(strlen(rel_start_path)+1);

	if (full_start_path) {
		strcpy(full_start_path,rel_start_path);
	}
}


DirPack::~DirPack() {
	free(full_start_path);
	full_start_path = NULL;
}

