// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

#include "HndlMgr.h"


HandleManager::HandleManager() {
	this->head = 0; // initialize list
}

void HandleManager::addHandle(HANDLE a) {
	struct handle_link_struct *temp = (struct handle_link_struct *)malloc(sizeof(struct handle_link_struct));

	if (!temp || !a) {
		// error!!!!
	} else {
		// insert into list
		temp->ptr = a;
		temp->next = this->head;
		this->head = temp;
		
	}
}

// destroy HandleManager

HandleManager::~HandleManager() {
	struct handle_link_struct *walker = this->head;

	while (walker) {
		if (walker->ptr) {
			DeleteObject(walker->ptr); // tell windows to delete the GDI object
			
		}	
		walker->ptr = 0;
		walker = walker->next;
	}
}

HandleManager *hndlMgr = 0;
