// HZ Engine Source
// Copyright (C) 1998 by David W. Jeske

// ConsoleView
// 
// This will provide our console input and output.
// The bottom line will always be the "input" line with a prompt. When
// the user finishes entering something, it will add that input to the text
// above and process it...
//
// you will be able to "addText" and "addIcon". A carriage return in the text,
// or reaching the end of the line will cause it to scroll up and begin the
// next line.
//
// it might be nice if we could turn paging on and off.... and it would be
// a nice whiz bang if we could turn on and off "smooth scrolling" since it
// will be _really_ easy to do the way we are storing this...

#ifndef HZ_VCONSOLE_H
#define HZ_VCONSOLE_H

#include "view.h"

// console storage class

class ConsoleData {
private:
	char *data;
	int data_size;
	int head_ptr, tail_ptr;
	int cur_numlines;
	void gobbleLine(void);
	int spaceInBuf(void);
	int charsInBuf(void);
	int bufWrap(int);
	int getLineStartReverse(int count);
public:
	void addText(char *s);		// adds a LF at the end
	void addString(char *s);	// no LF
	void addChar(char c);		// just a char...
	int numLines();
	int getLineReverse(char *s, int max_len, int line_count);
	void setScrollbackSize(int size);
	ConsoleData();
	ConsoleData(int starting_scrollback_size);
	~ConsoleData();

};

class ConsoleView : public BufferedView {
private:
//	HPEN linepen;
//	HPEN blackpen;
//	HBRUSH blackbrush;
	int activeLineStartY;
	int textHeight;
	char *curPrompt;
	int oldPromptLen;
	
	int needFullPaint;

	// the current keyboard input line
	int inputRowHeight;
	int curInputPos;
	int inputMaxLen;
        int isRunningLua;
	char *inputString;

	int scrollback_lines;

	// most of the "data"
	struct {
		char *start;
		char *end;
		char *head;
		char *tail;
	} myBuffer;

	void computeSizes(); // compute sizes of my private regions
	void repaint();
	void paintInputRow(); // paint the bottom (input) row
	int (*consoleHandler)(ConsoleView *,char *);
	ConsoleData *myData;
protected:
	virtual void drawSelf(void);
	virtual int handleEvent(struct input_event *ev);
	virtual void handleFocusChange(int state);
public:
	int consoleViewDisabled;
	ConsoleData *conTest;

	ConsoleView(int x,int y, int w, int h);
	~ConsoleView();

        void runningLua(int state);
	void setConsoleHandler(int (*cb)(ConsoleView *,char *));
	void addText(char *string);		// adds a newline
	void addString(char *string);	// no newline
	void addChar(char c);			// just a character
	void clear();
};


typedef enum {
	game_info = 0,
	game_warnings,
	game_error,
	l_info,
	l_warnings,
	l_error,
	c_info,
	c_warnings,
	c_error,
	l_excessive = 700,
	c_excessive = 701
} DEBUG_LEVEL;

void dbgMsg(DEBUG_LEVEL dbg_level, const char *fmt, ...);

#endif /* HZ_VCONSOLE_H */
