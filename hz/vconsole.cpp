// HZ Engine Source
// Copyright (C) 1998 by David W. Jeske


// VConsole.cpp
//
// this is very tied to windows, we need to come up with a general way to 
// make this work on multiple platforms. Or perhaps I just need to make
// an abstract Console class, and implement a video based console for windows
// and leave the whole implementation to be done on another platform.



#include <lua.h> // Lua language lib!

#ifdef OS_WIN
#include <ddraw.h>
#include <winuser.h> // VK_ codes
#include "DrawHndl.h"
#include "hndlmgr.h" // manage persistant GDI handles
#endif
#include "i_system.h" // for CleanupAndExit()

#include <string.h>

#include "donuts.h" // for lpDD
#include "view.h"
#include "main.h" // consoleView

#include "vconsole.h"
#include "i_video.h"

#include "osdep.h"






// this is probably broken, at least it looks broken to me...

int ConsoleData::getLineStartReverse(int count) {
	int line_start = -1;
	int curpos = head_ptr;
	int skiplast=1;

	while ((curpos != tail_ptr) && (count)) {
		curpos = bufWrap(curpos-1);
		if ((!skiplast) && (data[curpos] == 0)) {
			count--;
			if (count == 0) {
				return line_start;
			} 
		} 

		skiplast = 0;
		line_start = curpos;
	}

	if (count == 1) {
		return line_start;
	} else {
		return -1;
	}
}

// returns length, -1 signals no such line

int ConsoleData::getLineReverse(char *s, int max_len, int line_count) {
	int buf_ptr = getLineStartReverse(line_count);
	int cur_len = 0;

	if (buf_ptr < 0) {
		return -1;
	}

	while ((buf_ptr != head_ptr) && (max_len > 1)) {
		if (s) {
			*s = data[buf_ptr];
			s++; max_len--;
		}
		if (data[buf_ptr] == 0) {
			/* end of this line */
			return cur_len;
		} else {
			cur_len++;
		}
		buf_ptr = bufWrap(buf_ptr + 1);
	}

	*s = 0;
	return (cur_len);
}

int ConsoleData::numLines() {
	return (cur_numlines);
}

ConsoleData::ConsoleData(int starting_scrollback_size) {
	/* initialize variables */
	this->data = NULL;
	this->data_size = 0;
	this->cur_numlines = 0;

	this->setScrollbackSize(starting_scrollback_size);
}

ConsoleData::~ConsoleData() {
	/* initialize variables */
	this->data = NULL;
	this->data_size = 0;
}

void ConsoleData::setScrollbackSize(int size) {
	/* we should transfer over the old data */
	if (this->data) {
		free(this->data);
	}
	
	if (this->data = (char *)malloc(sizeof(char) * size) ) {
		this->data_size = size;
		this->head_ptr = 0;
		this->tail_ptr = 0;
	} else {
		this->data_size = 0; /* failed to allocate */
	}
	
}

void ConsoleData::gobbleLine(void) {
	int last_char_lf = 0;

	while ( (tail_ptr != head_ptr) && (!last_char_lf)) {
		if (data[tail_ptr] == 0) {
			last_char_lf = 1;
			cur_numlines--;
		}
		tail_ptr = bufWrap(tail_ptr + 1);
	}

}

void ConsoleData::addString(const char *s) {
	while (s && *s) {
		this->addChar(*s);
		s++;
	}
}

void ConsoleData::addText(const char *s) {
	this->addString(s);
	this->addChar('\n');
}

int ConsoleData::spaceInBuf(void) {
	return (data_size - charsInBuf() - 1);
}

int ConsoleData::charsInBuf(void) {
	if (head_ptr >= tail_ptr) {
		return (head_ptr - tail_ptr);
	} else {
		return (data_size - (tail_ptr - head_ptr));
	}
}

int ConsoleData::bufWrap(int loc) {
	while (loc >= this->data_size) {
		loc -= this->data_size;
	}

	while (loc < 0) {
		loc += this->data_size;
	}
	return loc;
}

void ConsoleData::addChar(char c) {

	if (c == '\r') { 
		/* don't insert CR */
		return;
	} else if (c == '\n') {
		/* insert newlines as string terminators */
		c = 0;
		cur_numlines++;
	}

	if (spaceInBuf() < 1) {
		this->gobbleLine();
	}
	this->data[this->head_ptr] = c;
	this->head_ptr = bufWrap(this->head_ptr + 1);
	this->data[this->head_ptr] = 0; /* guarantee a string terminator */

}

// ConsoleView
//
// Text console view... see the header for more information
//

ConsoleView::ConsoleView(int x,int y,int w,int h) : BufferedView(x,y,w,h) {
	// this should take into account the size of the screen
	// and stuff like that, but for now we'll just make it big...
	int width_chars = 80;
	int height_chars = 80;
	int buf_size = (width_chars * (height_chars * 2)) * sizeof(char);

	conTest = new ConsoleData(30);
	myData  = new ConsoleData(20000);

        isRunningLua = 0;
	needFullPaint = 0;
	inputRowHeight = 0;
	consoleViewDisabled = 0;
	wantsInputFocus = 1;
	scrollback_lines = 0;
	curPrompt = "> ";  // set the default prompt string
	consoleHandler = NULL; // nullify the callback..


#if 0
	hndlMgr->addHandle(linepen =  CreatePen(PS_SOLID,0,RGB(255,255,0)));
	hndlMgr->addHandle(blackpen = CreatePen(PS_SOLID,0,RGB(0,0,0)));
	hndlMgr->addHandle(blackbrush = CreateSolidBrush(RGB(0,0,0)));
	
	if (!linepen || !blackpen || !blackbrush) {
		CleanupAndExit("Couldn't CreatePen() in ConsoleView::ConsoleView()");
	}
#endif

	


	// allocate the bufferspace..
	inputMaxLen = 512;
	if ((inputString = (char *)malloc(inputMaxLen)) == NULL) {
		CleanupAndExit("Couldn't allocate input buffer!");
	}
	curInputPos = 0;
	strcpy(inputString,curPrompt);
	oldPromptLen = curInputPos = strlen(inputString);

	if ((myBuffer.start = (char *)malloc(buf_size)) == NULL)  {
		CleanupAndExit("Couldn't allocate text buffer!");
	}
	myBuffer.end = myBuffer.start + buf_size;
	myBuffer.head = myBuffer.tail = myBuffer.start;

	
	computeSizes();
	clear();
	repaint();
}

void ConsoleView::runningLua(int state) {
  this->isRunningLua = state;
}




ConsoleView::~ConsoleView() {
	
#if 0
	DeleteObject(blackbrush);
	DeleteObject(blackpen);
	DeleteObject(linepen);
#endif

	free(inputString);
	free(myBuffer.start);


	printf("ConsoleView descructor ran!\n");

}



void ConsoleView::clear() {
#ifdef OS_WIN_FIXING
	DDBLTFX     ddbltfx;
    HRESULT     ddrval;


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
#else
	I_ClearDrawable (&backingStore, 0, 0, my_dimension.width, 
	    my_dimension.height);
#endif

}

void ConsoleView::repaint() {
	static int num_paints_outstanding = 0;

	if (hasInputFocus) {
		if (num_paints_outstanding++ == 0) {
			needFullPaint = TRUE;
			DrawDisplayList();
		} else {
			if (num_paints_outstanding > 10) {
				num_paints_outstanding = 0;
			}
		}
	} else {
		num_paints_outstanding = 0;
	}
}

#ifndef MAX
#define MAX(x,y) (x > y ? x : y)
#endif
#ifndef MIN
#define MIN(x,y) (x > y ? y : x)
#endif


int ConsoleView::handleEvent(IN_EVENT *ev) {
	int inchar;

	if (ev->dev_type == DT_KEYBOARD) {
		if (ev->dev.keyboard.mask & KM_ASCII_KEY) {
			inchar = ev->dev.keyboard.ascii_code;
			// we might want to filter nasty ASCII characters here...

			switch (inchar) {
				case 13:
				case 10: // he hit return
					// process the input string!

					addText(inputString);
					
					inputString[0] = 0;
					// this will return 1 if it handled it...
					this->runningLua(1);
					consoleHandler(this,inputString + oldPromptLen);
					this->runningLua(0);

					// reset it now..
					// we might want to store it in a "history"
					curInputPos = 0;
					strcpy(inputString,curPrompt);
					oldPromptLen = curInputPos = strlen(inputString);
					break;

				case 27: // ESC -> switch to the main menu... this will
						 // probably be done at a level above us...
					break;
				case 8:
				case 127: // backspace
					if (curInputPos > oldPromptLen) {
						inputString[--curInputPos] = 0;
					}
					break;
				default:
					if (curInputPos < (inputMaxLen - 1)) {
						// add the character to the end of the input string
						inputString[curInputPos++] = inchar;
						inputString[curInputPos] = 0; // null terminate
					} else {
						// beep or something!
					}
					break;
			}
			
			this->paintInputRow();
		} else if (ev->dev.keyboard.mask & KM_KEYDOWN) {
			switch (ev->dev.keyboard.vk_code) {
					case VK_PRIOR: /* scrollback! */
								scrollback_lines = MIN(myData->numLines() - 5, 
								scrollback_lines + 5);
							break;
					case VK_NEXT: /* scroll forward! */
								scrollback_lines = MAX(0,scrollback_lines - 5);
							break;
					case VK_END: /* goto bottom! */
							scrollback_lines = 0;
							break;
					case VK_HOME: /* goto top */
							scrollback_lines = myData->numLines() - 5;
							break;

			}

		}
	}
	return 1;
}

void ConsoleView::handleFocusChange(int state) {
	if (state) {
		// probably want to do something like display the cursor
		setDirty();
		drawSelf();
		needFullPaint = TRUE;
		paintInputRow();

	} else {
		// probably want to take the cursor away, or make it hollow...
	}
}

void ConsoleView::drawSelf() {
	if (needFullPaint) {
		paintInputRow();
	}

	BufferedView::drawSelf();
}

void ConsoleView::paintInputRow() {
	// we need to paint the input data, and if the number of lines
	// involved changed, then we need to calculate the new size and
	// repaint the rest of the view...
	SIZE lineSize;
	int numlines = 0;
	int linebreaks[10]; // max number of linebreaks on input is going to be 10!
	int total_len_left = strlen(inputString);
	int curlen = total_len_left;
	int curlen_space; // used to find a space before "curlen" if possible
	int total_height = 0;
	int curpos = 0;
	int draw_lines = 0;
	int draw_cur_y = 0;

	if (I_GetDrawContext (&backingStore)) {
		// we need to split up the input line into as many lines as it needs
		// to display properly...
		
		do {

			// find a line which will fit...
			do {
				I_GetTextExtent(&backingStore,inputString + curpos,curlen,&lineSize);	

				if (lineSize.cx > (int)my_dimension.width) {
					curlen--;
				}
			} while (lineSize.cx > (int)my_dimension.width);

			if (total_len_left - curlen) {
				// try to see if we can word break easily...
				curlen_space = curlen;
				do {
					if (inputString[curpos + curlen_space] == ' ') {
						// found a space! good place to wordbreak
						curlen = curlen_space;
					} else {
						// no space, keep looking a bit
						curlen_space--;
						
						if (((curlen - curlen_space) > 15) || (curlen_space < 0)) {
							// stop looking...
							curlen_space = curlen;
						}
					}
				} while (curlen != curlen_space);
			}

			// make a note of this break.
			if (numlines < 10) {
				linebreaks[numlines++] = curlen;
				total_len_left -= curlen;
				curpos += curlen;
				curlen = total_len_left;
				total_height += lineSize.cy + 2;
			}

		} while (total_len_left > 0);

		if (total_height != inputRowHeight) {
			// the row height changed!!!
			inputRowHeight = total_height;
			needFullPaint = TRUE;
		}
		// we need to clear the region we are going to draw to...
		I_ClearDrawable (&backingStore, 0,my_dimension.height - inputRowHeight,
			my_dimension.width,my_dimension.height);

		curpos = 0;
		draw_lines = 0;
		draw_cur_y = my_dimension.height - inputRowHeight;
		while (draw_lines < numlines) {
			curlen = linebreaks[draw_lines];
    		I_GetTextExtent (&backingStore, inputString + curpos, curlen,
				&lineSize);	

			I_TextOut(&backingStore,0,draw_cur_y,inputString + curpos, curlen);
			draw_cur_y += lineSize.cy + 2;
			curpos += curlen;
			draw_lines++;
		}

            if (!this->isRunningLua) {
		// draw a cursor!

		I_FillRectangle (&backingStore, lineSize.cx + 2, 
		     	         my_dimension.height - lineSize.cy + 2, 
				 lineSize.cx + 10, my_dimension.height - 2);
            }
		
		/* now we need to draw the lines above that */

	    if (needFullPaint == TRUE) {
			// we need to clear the region we are going to draw to...
			I_ClearDrawable(&backingStore, 0,0,	my_dimension.width,
				my_dimension.height - inputRowHeight);
	
			I_SetFGColor (&backingStore, 255, 255, 0);
	
			/* just draw the last line of the buffer */
	
			draw_cur_y = my_dimension.height-inputRowHeight;
			{
				int buf_line_count = scrollback_lines + 1;

                                if (this->isRunningLua) {
                                        char *s = "...running!";
                                        int slen = strlen(s);
 					I_GetTextExtent(&backingStore,s,slen,&lineSize);
					I_TextOut(&backingStore,
						my_dimension.width - lineSize.cx - 10,
						draw_cur_y-lineSize.cy,s,slen);
					draw_cur_y -= lineSize.cy;
                                }

				if (scrollback_lines) {
					char s[200];
					int slen;

					sprintf(s,"%d/%d",scrollback_lines,myData->numLines());
					slen = strlen(s);
					I_GetTextExtent(&backingStore,s,slen,&lineSize);
					I_TextOut(&backingStore,
						my_dimension.width - lineSize.cx - 10,
						draw_cur_y-lineSize.cy,s,slen);
					draw_cur_y -= lineSize.cy;
				}

				while (draw_cur_y > 0) {
					char s[200];
					int slen;
		
					slen = myData->getLineReverse(s,200,buf_line_count++);
					if (slen == -1) {
						strcpy(s,"<null>");
						slen = strlen(s);
					}
		
					I_GetTextExtent(&backingStore,s,slen,&lineSize);	
					if ((draw_cur_y - lineSize.cy) > 0) {
						I_TextOut(&backingStore,0,draw_cur_y-lineSize.cy,s, slen);
					}
	
					draw_cur_y -= lineSize.cy;
	
				}
			}

		} 

		I_ReleaseDrawContext (&backingStore);
	}

	this->setDirty();
}

void ConsoleView::computeSizes() {
	textHeight = 0;
	activeLineStartY = (my_dimension.height - 60);
}

void ConsoleView::addText(const char *str) {
	myData->addString(str);
	myData->addChar('\n');
	repaint();
}

void ConsoleView::addString(const char *str) {
	myData->addString(str);
	repaint();
};


void ConsoleView::addChar(char c) {
	myData->addChar(c);
	repaint();
}

void ConsoleView::setConsoleHandler(int (*cb)(ConsoleView *,char *)) {
	consoleHandler = cb;
}


#include <stdio.h>
#include <stdarg.h>

static char big_string[1500]; // big string!

void logToFile(char *big_string) {
	static FILE *f = NULL;

	if (!f) {
		f = fopen("STDOUT.LOG","w+");
		if (!f) {
			return; // damn, we're fucked!
		}
	}

	fputs(big_string,f);
	fflush(f);
}

// int current_debug_level = 5000;
int current_debug_level = 1;


void dbgMsg(DEBUG_LEVEL dbg_level, const char *fmt, ...) {
	va_list ap;

	if (dbg_level > current_debug_level) {
		return;
	}

	va_start(ap, fmt);
	vsprintf(big_string, fmt, ap);
	va_end(ap);

	if (consoleView) {
		consoleView->addText(big_string);
	}
	logToFile(big_string);
}


extern "C" {
	int printf(const char *fmt, ...) {
		va_list ap;
		
		va_start(ap, fmt);
		vsprintf(big_string, fmt, ap);
		va_end(ap);

		logToFile(big_string);

		if (consoleView) {
			consoleView->addString(big_string);
		}
		return 0;
	}
}

