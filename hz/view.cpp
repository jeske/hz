// View.cpp
//
// This is the code for the generic View class, it has to be given
// a size and a location on the screen when it's created. So you
// can only decide whether to draw it or not (i.e. tile/tab views)
// you can't move it... at least not yet...
//
//
// View.cpp/VConsole.cpp: a view painting heirarchy class structure, my goals
//     for this were to make it fast, and static. So the views precompute their      
//     screen coordinates at "instantiate" time. There are generic things like       
//     a MultiView (for the pane switching in a tab view type setup), a "power
//     bar" and a text "ConsoleView".

#include <string.h>
  
#include <lua.h> // Lua language lib!

#ifdef OS_WIN
#include "DrawHndl.h"
#include "hndlmgr.h" // manage persistant GDI handles
#endif
#include "i_video.h" // make this go away!!!
#include "i_draw.h"
#include "i_system.h" // for CleanupAndExit()

#include "donuts.h" // for lpDD
#include "view.h"
#include "main.h" // consoleView

#include "osdep.h"

View::~View() {
	// take apart the view...
	View *temp;

	while (my_subviews) {

		temp = my_subviews;

		this->removeSubview(temp);
		delete temp;
	}

}

View::View(int x, int y, int w, int h) {
	my_dimension.x = x;
	my_dimension.y = y;
	my_dimension.width = w;
	my_dimension.height = h;
	drawSelfFirst = 1;
	my_subviews = NULL;
	next_peerview = NULL;
	my_parent = NULL;
	state = 1;
	planarDepth = 0;
	wantsInputFocus = 1;
	hasInputFocus = 0;
	alreadyDrawing = 0;
	eventHandleCallback = NULL;
}

View::View(dimension *dim) {
	my_dimension = *dim;
	drawSelfFirst = 1;
	my_subviews = NULL;
	next_peerview = NULL;
	my_parent = NULL;
	wantsInputFocus = 1;
	hasInputFocus = 0;
	state = 1;
	eventHandleCallback = NULL;
}


int View::handleEvent(IN_EVENT *ev) {
	int retval = 0; // did we handle the event?

	if (eventHandleCallback) {
		retval = eventHandleCallback(ev);
	}
	return retval;
}

void View::setEventCallback(int (*cb)(IN_EVENT *)) {
	eventHandleCallback = cb;
}

int View::inputEvent(struct input_event *ev) {
	View *walker = my_subviews;
	int retval = 0;


	retval = this->handleEvent(ev);
	while (walker && (!retval)) {
		retval = walker->inputEvent(ev);
		walker = walker->next_peerview;
	}
	return retval;
}

void View::handleFocusChange(int state) {
}

void View::setInputFocus(int state) {
	this->hasInputFocus = (state && this->wantsInputFocus);
	View *walker = my_subviews;
	this->state = state;

	this->handleFocusChange(state);
	while (walker) {
		walker->setInputFocus(state);
		walker = walker->next_peerview;
	}
}

inline void drawSubviews(View *walker) {

	while (walker) {
		walker->draw();
		walker = walker->next_peerview;
	}
}

void View::draw() {
	// make sure we are not already in a draw loop!

	if (alreadyDrawing) {
		return;
	}

	alreadyDrawing = 1;
	
	// we need to know if we should draw ourself first or last..
	if (state) {
		// if we are enabled
		if (drawSelfFirst) {
			drawSelf();
			drawSubviews(this->my_subviews);
		} else {
			drawSelf();
			drawSubviews(this->my_subviews);
		}
	}
	alreadyDrawing = 0;
}

void View::drawSelf() {

}


// View::addSubview(View *a_view)
// 
// this should add in a specified order, dependent on the drawing
// mode we're in... If we are doing transparent blits, they should be
// smallest planarDepth to largest, and if we are doing colorkey blits
// they should be largest to smallest..

void View::addSubview(View *a_view) {
	View *walker,*temp, *ins_loc;
	int smallestToLargest = 1;

	if (a_view == NULL) {
		// this shouldn't happen, but we'll be extra carefull...
		return;
	}

	
	// if they are adding in more than one subview in a chain, we really
	// need to add each one individually... 

	while ((temp = a_view->next_peerview) != NULL) {
		a_view->next_peerview = NULL; // terminate this one
		this->addSubview(a_view);     // and resubmit
		a_view = temp; // and now do the next one...
	}

	if (a_view->my_parent) {
		// They already have a parent...
		// do we need to support multiple parents?
		// if we do, then we'll need to figure this out later.

		a_view->my_parent->removeSubview(a_view);

		// for now, you could just create a "mirrorView" which would
		// allow you to chain a view into multiple places.
	}
	
	a_view->my_parent = this; // set the parent;

	if (a_view->wantsInputFocus) {
		wantsInputFocus = TRUE; // we now want the input focus too!
	}

	// now we're left with only one view to add... either because
	// it's the last one in the list, or it was the only one handed to
	// this function...

	if (my_subviews == NULL) {
		// this is easy, it's the first one...
		my_subviews = a_view; 
	} else {
		// first we need to find out where it's going to go in the list
		// according to it's planarDepth.
		
		if (
			(smallestToLargest ?
				(my_subviews->planarDepth > a_view->planarDepth) :
			    (my_subviews->planarDepth < a_view->planarDepth)
		    )
		   ) {
			// it needs to go at the head of the list...
			a_view->next_peerview = my_subviews;
			my_subviews = a_view;
		} else {
			// it dosn't go at the beginning... so..
			
			ins_loc = my_subviews;
			walker = my_subviews->next_peerview;

			while (walker && 
					(smallestToLargest ? 
						(walker->planarDepth < a_view->planarDepth) : 
						(walker->planarDepth > a_view->planarDepth)
					)
				  ){
				ins_loc = walker;
				walker = walker->next_peerview;
			}

			// now we have a spot to put it...
			a_view->next_peerview = walker;
			ins_loc->next_peerview = a_view;
		}
	}
}

void View::removeSubview(View *a_view) {

	if (a_view == NULL) {
		// This shouldn't happen...
		return;
	}

	a_view->my_parent = NULL;

	if (my_subviews == a_view) {  // first subview??
		my_subviews = a_view->next_peerview;
		a_view->next_peerview = NULL;
	} else {  
		View *last_view = my_subviews;
		View *walker = last_view->next_peerview;
		// not the first subview... find it first
		
		while (walker) {
			if (walker == a_view) {
				last_view->next_peerview = walker->next_peerview;
				walker->next_peerview = NULL;
				return; // we're done!
			}

			// check next_view;
			last_view = walker;
			walker = walker->next_peerview;
		}
	}
}

void View::setState(int st) {
	state = st;
}

int View::curState() {
	return (state);
}

int View::depth() {
	return (planarDepth);
}

void View::setDepth(int depth) {
	planarDepth = depth;

	// we should have a "parent" and be able to do something like:
	// this->parent->reDepthMe();  so that this will take effect
}

// MultiView
// 
// This class will allow switching between multiple views
//


MultiView::MultiView(int x,int y, int w, int h) : View(x,y,w,h) {
	maxViews = 15;
	curview = NULL;
	curview_index = MULTIVIEW_VIEW_NONE;

	wantsInputFocus = TRUE;
	for (int i=0;i<maxViews;i++) {
		viewList[i] = NULL;
	}
}

int MultiView::curView() {
	// return the index of the current view;
	return (curview_index);
}


int MultiView::handleEvent(struct input_event *ev) {
	int retval;

	if (curview) {
		retval =  (curview->inputEvent(ev));
	} else {
		retval = 0;
	}
	
	return (retval);
}


// returns zero on success, and something else if there was an 
// error switching

int MultiView::switchTo(int index) {
	if ((index < 0) || (index >= maxViews)) {
		return -1; // out of range
	}

	if (viewList[index] == NULL) {
		return -1; // invalid view
	}

	// we're okay, so switch

	// first take away the old input focus
	if (curview) {
		curview->setInputFocus(FALSE);
	}

	curview = viewList[index];
	curview_index = index;
	// curview->setInputFocus(hasInputFocus);
	curview->setInputFocus(TRUE);
	return 0;

}

void MultiView::handleFocusChange(int state) {
	if (curview) {
		curview->setInputFocus(state);
	} 
}

// return the index the view was placed in or -1 if there
// was nowhere to put it...

int MultiView::addView(View *a_view, char *name) {
	// we're not going to do anything with the name yet.
	int iter = 0;

	// first, find an index

	while (iter < maxViews) {		
		if (viewList[iter] == NULL) {
			// there is room to put it here!!!

			viewList[iter] = a_view;
			// put the name in the name list here

			// if there is no current view, we should
			// make this the current view...
			if (!curview) {
				curview = a_view;
				curview_index = iter;
				curview->setInputFocus(TRUE);
			}
			return (iter);
		}
		iter++;
	}

	// I guess we didn't find a place to put it
	return (-1);
}


// return 0 if successfull... error if not...

int MultiView::removeView(int index) {
	if ((index < 0) || (index >= maxViews)) {
		return -1; // out of range
	}

	if (viewList[index] == NULL) {
		return -1; // invalid view
	}

	if (curview_index == index) {
		// wow, he's trying to remove the current
		// view so we should probably do something..
		// for now we'll just disable all views
		curview->setInputFocus(FALSE);
		curview = NULL;
		curview_index = -1;
	}

	viewList[index] = NULL;
	return (0);
}

void MultiView::drawSelf() {
	if (curview) {
		curview->draw();
	}
}


// return -1 if there is no view to show, otherwise return the
// new index number

int MultiView::nextView() {
	if (!curview) {
		return (-1);
	} 
	
	curview->setInputFocus(FALSE);
	do {
		if ((++curview_index) > maxViews) {
			curview_index = 0;
		}
		curview = viewList[curview_index];
	} while (!curview);
	
	// curview->setInputFocus(hasInputFocus);
	curview->setInputFocus(TRUE);

	return (curview_index);
}

// BufferedView
//
// This is view which paints into an offscreen buffer...
// this will be used for things which don't change very often..
//

BufferedView::BufferedView(int x,int y,int w, int h) : View(x,y,w,h) {
	RECT src;
	src.left = x;
	src.top = y;
	src.right = x + w;
	src.bottom = y + h;

	I_CreateDrawable (&src, "bufferedview", &backingStore);
	dirty_count = 0;
}

BufferedView::~BufferedView() {
	I_FreeDrawable (&backingStore);
}

void BufferedView::setDirty() {
	dirty_count = 2; // this should be the number of "double buffers" there are
}

void BufferedView::drawSelf() {
	RECT src;
	HRESULT ddrval;

	src.left = my_dimension.x;
	src.top = my_dimension.y;
	src.right = src.left + my_dimension.width-1;
	src.bottom = src.top + my_dimension.height-1;

#if 0

	//if (dirty_count) {
		//dirty_count--;
		// flush the offscreen backstore to the screen...
		ddrval = lpBackBuffer->BltFast(my_dimension.x, my_dimension.y, 
			backingStore, &src,  dwTransType);
		
		switch (ddrval) {
		case DD_OK: 
			break;
		case DDERR_SURFACELOST:
            if( !RestoreSurfaces() )
                return;
        case DDERR_WASSTILLDRAWING:
			return;
        }
#else
	// if (this->backingStore.image->name != NULL)
	  I_doBlit (&(src), this->backingStore.image);
#endif

	//}
}

// HorizStatusBar
//
// this will make a horizontal bar, for things like a health bar...
//

HorizStatusBar::HorizStatusBar(int x,int y,int w,int h,int max) :
		BufferedView(x,y,w,h) {

#ifdef OS_WIN_FIXING
    hndlMgr->addHandle(linepen    =  CreatePen(PS_SOLID,0,RGB(255,255,0)));
	hndlMgr->addHandle(solidbrush = CreateSolidBrush(RGB(255,255,0)));
	hndlMgr->addHandle(hatchbrush = CreateHatchBrush(HS_DIAGCROSS,RGB(255,255,0)));
#endif

	if (max > 0) {
		maxVal = max;
	} else {
		maxVal = 0;
	}
	curVal = maxVal >> 1;
	repaintSelf();
}

HorizStatusBar::~HorizStatusBar() {
#ifdef OS_WIN_FIXING
	DeleteObject(linepen);
	DeleteObject(solidbrush);
	DeleteObject(hatchbrush);
#endif
}

void HorizStatusBar::setValue(int val) {
	if (val > maxVal) {
		curVal = maxVal;
	} else {
		if (val < 0) {
			curVal = 0;
		} else {
			curVal = val;
		}
	}
	repaintSelf();

}

int HorizStatusBar::getValue() {
	return (curVal);
}

int HorizStatusBar::getMaxValue() {
	return (maxVal);
}
void HorizStatusBar::setMaxValue(int val) {
	if (val > 0) {
		maxVal = val;
	} else {
		maxVal = 0;
	}

	if (curVal > maxVal) {
		curVal = maxVal;
	}
	repaintSelf();
}

void HorizStatusBar::repaintSelf() {
	int maxPaintX = my_dimension.width-1;
	int paintY = my_dimension.height-1;
	int curPaintX;
    HRESULT     ddrval;
	DWORD		barColor = 10; // this should be in the class!!!
#ifdef OS_WIN_FIXING
    DDBLTFX     ddbltfx;
	HDC hdc;
#endif

	//  = ((curVal / maxVal) * maxPaintX)-2
		
	if (curVal) {
		if (maxVal) {
			curPaintX = (int)((double)(maxPaintX - 2) * (double) curVal / (double)maxVal) + 1;
		} else {
			curPaintX = maxPaintX;
		}
	} else {
		curPaintX = 0;
	}
	
	// paint self into buffered view...
	// we should just figure out how big we are and paint silly rectangles...


	// Erase the background
#ifdef OS_WIN_FIXING
	ddbltfx.dwSize = sizeof( ddbltfx );
	ddbltfx.dwFillColor = dwFillColor;
	while( 1 )
	{
		ddrval = backingStore->Blt(NULL, NULL,
				 NULL, DDBLT_COLORFILL, &ddbltfx );

		if( ddrval == DD_OK )
		{
			break;
		}
		if( ddrval == DDERR_SURFACELOST )
		{
			if( !RestoreSurfaces() )
				return;
		}
		if( ddrval != DDERR_WASSTILLDRAWING )
		{
			return;
		}
	}

	if (backingStore->GetDC(&hdc) == DD_OK) {
		SelectObject(hdc,linepen);

		// SetBkColor(hdc,RGB(0,0,255));
		// SetTextColor(hdc,RGB(255,255,0));
		// TextOut(hdc,0,0,"Hey",lstrlen("Hey"));

		// first, draw rectangle "box" around whole view...


		// MoveToEx(hdc,0,0,NULL);
		// LineTo(hdc,my_dimension.width,0);

		MoveToEx(hdc,0,0,NULL);
		LineTo(hdc,maxPaintX,0);
		LineTo(hdc,maxPaintX,paintY);
		LineTo(hdc,0,paintY);
		LineTo(hdc,0,0);

		// MoveToEx(hdc,5,5,NULL);
		// LineTo(hdc,my_dimension.width,my_dimension.height);
		// LineTo(hdc,my_dimension.width,my_dimension.height);
		// LineTo(hdc,0,my_dimension.height);
		// LineTo(hdc,0,0);
	
		// MoveToEx(hdc,my_dimension.width-1,0,NULL);
		// LineTo(hdc,my_dimension.width-1,my_dimension.height-1);
		// second, fill in the "filled" portion according to "curVal"
		SetBkColor(hdc,RGB(0,0,0));
		SelectObject(hdc,solidbrush);

		if (curPaintX) {
			Rectangle(hdc, 2,2,curPaintX,paintY-1);
		}

		// third, fill "unused half" to a hatch pattern...

		// SelectObject(hdc,hatchbrush);
		// Rectangle(hdc,curPaintX,0,maxPaintX,paintY);

		// release context...
		backingStore->ReleaseDC(hdc);
	}
#else
	if (I_GetDrawContext (&backingStore)) {

	  I_ClearDrawable (&backingStore, 0, 0, my_dimension.width, 
	      my_dimension.height);

	  I_DrawLine (&backingStore, 0, 0, maxPaintX, 0);
	  I_DrawLine (&backingStore, maxPaintX, 0, maxPaintX, paintY);
	  I_DrawLine (&backingStore, maxPaintX, paintY, 0, paintY);
	  I_DrawLine (&backingStore, 0, paintY, 0, 0);

	  if (curPaintX) {
	    I_FillRectangle (&backingStore, 2, 2, curPaintX, paintY-1);
	  }

	  // release context...
	  I_ReleaseDrawContext (&backingStore);
	}

#endif

	// tell BufferedView we are dirty...
	this->setDirty();
}


// TextView
//
// this will make a text view for things like a text console...
//

TextView::TextView(int x,int y,int w,int h) :
		BufferedView(x,y,w,h) 
{
#ifdef OS_WIN_FIXED
    linepen=  CreatePen(PS_SOLID,0,RGB(255,255,0));
#endif
	curString[0] = 0;
	repaintSelf();
}


void TextView::repaintSelf() {
	int maxPaintX = my_dimension.width-2;
	int paintY = my_dimension.height-2;
    HRESULT     ddrval;
#ifdef OS_WIN_FIXED
    DDBLTFX     ddbltfx;
	HDC hdc;

	
	// paint self into buffered view...
	// we should just figure out how big we are and paint silly rectangles...

	// Erase the background
	ddbltfx.dwSize = sizeof( ddbltfx );
	ddbltfx.dwFillColor = dwFillColor;
	while( 1 )
	{
		ddrval = backingStore->Blt(NULL, NULL,
				 NULL, DDBLT_COLORFILL, &ddbltfx );

		if( ddrval == DD_OK )
		{
			break;
		}
		if( ddrval == DDERR_SURFACELOST )
		{
			if( !RestoreSurfaces() )
				return;
		}
		if( ddrval != DDERR_WASSTILLDRAWING )
		{
			return;
		}
	}

	if (backingStore->GetDC(&hdc) == DD_OK) {
		SelectObject(hdc,linepen);

		//SetBkColor(hdc,RGB(0,0,255));
		SetBkMode(hdc, TRANSPARENT); 
		SetTextColor(hdc,RGB(255,255,0));
		TextOut(hdc,0,0,curString,lstrlen(curString));

		// first, draw rectangle "box" around whole view...


		// MoveToEx(hdc,0,0,NULL);
		// LineTo(hdc,my_dimension.width,0);

		MoveToEx(hdc,0,0,NULL);
		LineTo(hdc,maxPaintX,0);
		LineTo(hdc,maxPaintX,paintY);
		LineTo(hdc,0,paintY);
		LineTo(hdc,0,0);

		// release context...
		backingStore->ReleaseDC(hdc);
	}
#else
	if (I_GetDrawContext (&backingStore)) {

	  I_SetFGColor (&backingStore, 255, 255, 0);
	  I_TextOut (&backingStore, 0, 0, curString, strlen (curString));
	  I_DrawLine (&backingStore, 0, 0, maxPaintX, 0);
	  I_DrawLine (&backingStore, maxPaintX, 0, maxPaintX, paintY);
	  I_DrawLine (&backingStore, maxPaintX, paintY, 0, paintY);
	  I_DrawLine (&backingStore, 0, paintY, 0, 0);

	  // release context...
	  I_ReleaseDrawContext (&backingStore);
	}
#endif

	// tell BufferedView we are dirty...
	this->setDirty();
}

void TextView::addText(char *str) {
	int len = strlen(str);

	if (len >= 100) {
		strncpy(curString,str,99);
		curString[99]=0;
	} else {
		strcpy(curString,str);
	}
	repaintSelf();
}

void TextView::clearText() {
	curString[0] = 0;
	repaintSelf();
}

// *******************************
// class ImageView : BufferedView

ImageView::ImageView(int x, int y, int w, int h, char *imageName) : 
						BufferedView(x,y,w,h) {
#if 0
	HRESULT     ddrval;
    HBITMAP     hbm;

    // set the palette before loading the splash screen
    // lpFrontBuffer->SetPalette(lpSplashPalette );

	hbm = (HBITMAP)LoadImage(NULL, imageName, 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );

    if ( NULL == hbm ) {
		if (consoleView) {
			consoleView->addText("Failed loading Image...");
		}
        return;
	}

    // if the surface is lost, DDCopyBitmap will fail and the surface will
    // be restored in FlipScreen.
    ddrval = DDCopyBitmap( backingStore, hbm, 0, 0, 0, 0 );

    DeleteObject( hbm );
#else
    I_loadImage (this->backingStore.image, imageName, 1);
#endif
}


// *******************************
// class HUDView

HUDView::HUDView(int x, int y, int w, int h) : BufferedView(x,y,w,h) {
#ifdef OS_WIN_FIXING
	linepen =  CreatePen(PS_SOLID,0,RGB(255,255,0));
#endif
	repaintSelf();
}

void HUDView::repaintSelf() {
	int maxPaintX = my_dimension.width-2;
	int paintY = my_dimension.height-2;
    HRESULT     ddrval;
#ifdef OS_WIN_FIXED
    DDBLTFX     ddbltfx;
	HDC hdc;

	
	// paint self into buffered view...
	// we should just figure out how big we are and paint silly rectangles...

	// Erase the background
	ddbltfx.dwSize = sizeof( ddbltfx );
	ddbltfx.dwFillColor = dwFillColor;
	while( 1 )
	{
		ddrval = backingStore->Blt(NULL, NULL,
				 NULL, DDBLT_COLORFILL, &ddbltfx );

		if( ddrval == DD_OK )
		{
			break;
		}
		if( ddrval == DDERR_SURFACELOST )
		{
			if( !RestoreSurfaces() )
				return;
		}
		if( ddrval != DDERR_WASSTILLDRAWING )
		{
			return;
		}
	}

	if (backingStore->GetDC(&hdc) == DD_OK) {
		SelectObject(hdc,linepen);

		//SetBkColor(hdc,RGB(0,0,255));
		// SetBkMode(hdc, TRANSPARENT); 
		// SetTextColor(hdc,RGB(255,255,0));
		// TextOut(hdc,0,0,curString,lstrlen(curString));

		// first, draw rectangle "box" around whole view...


		// MoveToEx(hdc,0,0,NULL);
		// LineTo(hdc,my_dimension.width,0);

		MoveToEx(hdc,4,0,NULL);
		LineTo(hdc,0,0);
		LineTo(hdc,0,paintY);
		LineTo(hdc,4,paintY);

		MoveToEx(hdc,maxPaintX-4,0,NULL);
		LineTo(hdc,maxPaintX,0);
		LineTo(hdc,maxPaintX,paintY);
		LineTo(hdc,maxPaintX-4,paintY);

		// release context...
		backingStore->ReleaseDC(hdc);
	}
#else
	if (I_GetDrawContext (&backingStore)) {

	  I_SetFGColor (&backingStore, 255, 255, 0);
	  I_DrawLine (&backingStore, 4, 0, 0, 0);
	  I_DrawLine (&backingStore, 0, 0, 0, paintY);
	  I_DrawLine (&backingStore, 0, paintY, 4, paintY);
	  I_DrawLine (&backingStore, maxPaintX-4, 0, maxPaintX, 0);
	  I_DrawLine (&backingStore, maxPaintX, 0, maxPaintX, paintY);
	  I_DrawLine (&backingStore, maxPaintX, paintY, maxPaintX-4, paintY);

	  // release context...
	  I_ReleaseDrawContext (&backingStore);
	}
#endif


	// tell BufferedView we are dirty...
	this->setDirty();
}




// ****************************
// TextureView
//

TextureView::TextureView(int x,int y,int w,int h) : View(x,y,w,h) {
}

void TextureView::drawSelf() {

	/*
	RECT dest;
	RECT src;

	DDBLTFX     ddbltfx;
    HRESULT     ddrval;


	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.lpDDSPattern = lpShip;

	// Erase the background

	src.right = (src.left = 0) + 24;
	src.bottom = (src.top = 0) + 24;

	dest.right  = (dest.left = my_dimension.x) + my_dimension.width;
	dest.bottom = (dest.top = my_dimension.y) + my_dimension.height;

	ddrval = lpBackBuffer->Blt(&dest,NULL,NULL,DDBLT_DDFX,&ddbltfx);

  */
}


