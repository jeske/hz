// HndlMgr.h
#include <ddraw.h>


struct handle_link_struct {
	struct handle_link_struct *next;
	HANDLE ptr;
};

class HandleManager {
	struct handle_link_struct *head;
public:
	HandleManager();
	~HandleManager();
	void addHandle(HANDLE );
};

extern HandleManager *hndlMgr;