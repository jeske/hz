// HZ Engine Source
// Copyright (C) 1998 by David W. Jeske

// View.h
// 
// This is the code for the View class, it has to be given
// a size and a location on the screen when it's created. So you
// can only decide whether to draw it or not (i.e. tile/tab views)
// you can't move it... at least not yet...

#ifndef VIEW_H
#define VIEW_H

#ifdef OS_WIN
#include <ddraw.h>
#include "i_video.h"
#endif

#ifdef OS_UNIX
#include "translate.h"
#include "i_sprtet.h"
#include "i_video.h"
#endif

typedef struct dimension_struct {
	unsigned int x,y;
	unsigned int width, height;
} dimension;

class View;

// stuff will always be drawn to lpBackBuffer right now.. we should
// figure something out here....

#ifndef NULL
#define NULL (0)
#endif

enum dev_type_enum {
	DT_KEYBOARD = 0x01,
	DT_JOYSTICK = 0x02,
	DT_MOUSE = 0x03
};

typedef unsigned int keyboard_mask_enum;

#define	KM_KEYDOWN 0x01
#define	KM_KEYUP 0x02
#define KM_ASCII_KEY 0x04
#define	KM_ASCII_KEYRPT 0x08

enum mouse_mask_enum {
	MS_L_BUTTON = 01,
	MS_M_BUTTON = 02,
	MS_R_BUTTON = 04
};

typedef struct input_event {
	enum dev_type_enum dev_type;
	union {
		struct {
			keyboard_mask_enum mask;
//			int scan_code;
			int vk_code;
			int ascii_code;
		} keyboard;
		struct {
		} joystick;
		struct {
			int xpos;
			int ypos;
			enum mouse_mask_enum mask;			
		} mouse;
	} dev;
} IN_EVENT;

class View {
private:
	int alreadyDrawing; // prevent recursive draws
	int state; // 0 = disabled, 1 = enabled
	int drawSelfFirst;
	int planarDepth; // smaller is farther back
	View *next_peerview;
	View *my_subviews;
	View *my_parent;
	friend inline void drawSubviews(View *);
	int (*eventHandleCallback)(IN_EVENT *);
protected:
	dimension my_dimension;
	int hasInputFocus;
	int wantsInputFocus;

	virtual void drawSelf(); // override this to change how we draw ourself...
	virtual int handleEvent(IN_EVENT *ev);
	virtual void handleFocusChange(int state);
	unsigned long int ev_mask;
	int do_mesg;
public:
	// constructors
	View(int x, int y, int w, int h);
	~View();
	View(dimension *dim);

	// chaining into the heirarchy
	void addSubview(View *);
	void removeSubview(View *);

	// enable or disable the view, or change it's depth...
	int curState();
	void setState(int state);
	int depth();
	void setDepth(int depth);

	// ask us to draw
 	void draw(); // call this to draw the view! 

	// input focus information
	int inputEvent(struct input_event *ev);
	void setInputFocus(int state);
	virtual void setEventCallback(int (*cb)(IN_EVENT *));
};


// TextureView
//
// this class will paint a view with a texture, for underlying bitmap textures
//
class TextureView : public View{
private:
protected:
	virtual void drawSelf();
public:
	TextureView(int x,int y,int w, int h);
};

// MultiView
//
// this class will allow switching between views by index. I'm
// going to use it to do a "tab-view" style thing...


#define MULTIVIEW_VIEW_NONE -1

class MultiView : public View {
private:
	View *viewList[15]; // 15 views max for right now
	View *curview;
	View *oldview;
	int curview_index;
	char viewName[15][20]; // 15 views, 20chrs max name
	int maxViews;
protected:
	virtual void drawSelf();
	virtual int handleEvent(struct input_event *ev);
	virtual void handleFocusChange(int state);
public:
	MultiView(int x, int y, int w, int h);
	int addView(View *a_view, char *name);
	
	int removeView(int index);

	int curView();
	int switchTo(int index);
	int nextView();

	// input focus information
};

class BufferedView : public View {
private:
	int dirty_count;
protected:
	// need a private surface to cache offscreen image
#if 0
	LPDIRECTDRAWSURFACE backingStore;
#else
	DRAWABLE backingStore; 
#endif
	virtual void drawSelf();
	void setDirty();
public:
	BufferedView(int x, int y, int w, int h);
	~BufferedView();

};

class ImageView : public BufferedView {
public:
	ImageView(int x, int y, int w, int h, char *imageName);
};

class HorizStatusBar : public BufferedView {
private:
	int maxVal;
	int curVal;

	// windows drawing stuff
	HPEN linepen;
	HBRUSH solidbrush;
	HBRUSH hatchbrush;

	void repaintSelf(); // paint onto the buffered view

protected:
public: 
	HorizStatusBar(int x, int y, int w, int h,int max);
        ~HorizStatusBar();
	void setValue(int val);
	int getValue();
	int getMaxValue();
	void setMaxValue(int val);
};

class TextView : public BufferedView {
private:
	HPEN linepen;
	void repaintSelf(); // paint into our buffered view..
	char curString[100]; // max chars = 100 for now
protected:
public:
	TextView(int x,int y, int w, int h);
	void addText(char *string);
	void clearText();
};

class HUDView : public BufferedView {
private:
	HPEN linepen;
	void repaintSelf(); // paint into our buffered view
protected:
public:
	HUDView(int x,int y, int w, int h);
};



#endif // VIEW_H
