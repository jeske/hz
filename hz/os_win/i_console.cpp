// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske


#include "i_console.h"
#include "vconsole.h"
#include "i_video.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

int I_Error (char *fmt, ...)
{
  va_list ap;

  fprintf (stderr, "-E- ");
  va_start (ap, fmt);

  vfprintf (stderr, fmt, ap);

  va_end (ap);
  fprintf (stderr, "\n");
}

int I_Perror (char *fmt, ...)
{
  va_list ap;
  char s[256];
  char *p = strerror (errno);

  va_start (ap, fmt);

  vsprintf (s, fmt, ap);

  va_end (ap);

  I_Error ("%s: %s (errno = %d)", s, p ? p : "unknown error", errno);
}

int I_Message (char *fmt, ...)
{
  va_list ap;

  va_start (ap, fmt);

  vfprintf (stderr, fmt, ap);

  va_end (ap);
}

#if 0
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

//  if (backingStore->GetDC(&hdc) == DD_OK) {
//    SelectObject(hdc,linepen);

    // we need to split up the input line into as many lines as it needs
    // to display properly...


    do {

      // find a line which will fit...
      do {
//	GetTextExtentPoint32(hdc,inputString + curpos,curlen,&lineSize);	
        I_GetTextExtent (&backingStore, inputString + curpos, curlen, 
	    &lineSize);

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
    //		SetBkColor(hdc,RGB(0,0,0));
#if 0 
    SetBkMode(hdc,OPAQUE);

    SelectObject(hdc,blackbrush); // the "inside" of the rectangle
    SelectObject(hdc,blackpen);   // the "outline" of the rectangle..
    Rectangle(hdc, 0,my_dimension.height - inputRowHeight,
	my_dimension.width,my_dimension.height);

    SetBkColor(hdc,RGB(0,0,0));
    SetBkMode(hdc,TRANSPARENT);

    SetTextColor(hdc,RGB(255,255,0));
#else
    I_ClearDrawable (&backingStore, 0, my_dimension.height - inputRowHeight,
	my_dimension.width, my_dimension.height);
    I_SetFGColor (&backingStore, 255, 255, 0);
#endif
    curpos = 0;
    draw_lines = 0;
    draw_cur_y = my_dimension.height - inputRowHeight;
    while (draw_lines < numlines) {
      curlen = linebreaks[draw_lines];
//      GetTextExtentPoint32(hdc,inputString + curpos,curlen,&lineSize);	
      I_GetTextExtent (&backingStore, inputString + curpos, curlen, &lineSize);	

//      TextOut(hdc,0,draw_cur_y,inputString + curpos, curlen);
      I_TextOut(&backingStore, 0, draw_cur_y, inputString + curpos, curlen);
      draw_cur_y += lineSize.cy + 2;
      curpos += curlen;
      draw_lines++;
    }

    // draw a cursor!
#if 0
    SelectObject(hdc,linepen);
    SetBkMode(hdc,
	TRANSPARENT);
    Rectangle(hdc, lineSize.cx + 2, my_dimension.height - 12,
	lineSize.cx + 10, my_dimension.height - 5);
#else
    I_SetFGColor (&backingStore, 255, 255, lineSize.cx);
    I_FillRectangle (&backingStore, lineSize.cx + 2, 
	my_dimension.height - lineSize.cy + 2,
	lineSize.cx + 10, my_dimension.height - 2);
#endif

    /* now we need to draw the lines above that */

    if (needFullPaint == TRUE) {
#if 0
      // we need to clear the region we are going to draw to...
      //		SetBkColor(hdc,RGB(0,0,0));
      SetBkMode(hdc,OPAQUE);

      SelectObject(hdc,blackbrush); // the "inside" of the rectangle
      SelectObject(hdc,blackpen);   // the "outline" of the rectangle..
      Rectangle(hdc, 0,0,
	  my_dimension.width,my_dimension.height - inputRowHeight);

      SetBkColor(hdc,RGB(0,0,0));
      SetBkMode(hdc,TRANSPARENT);

      SetTextColor(hdc,RGB(255,255,0));
#else
    I_ClearDrawable (&backingStore, 0, 0,
	my_dimension.width, my_dimension.height - inputRowHeight);
    I_SetFGColor (&backingStore, 255, 255, 0);

#endif

      /* just draw the last line of the buffer */

      draw_cur_y = my_dimension.height-inputRowHeight;
      {
	int buf_line_count = scrollback_lines + 1;


	if (scrollback_lines) {
	  char s[200];
	  int slen;

	  sprintf(s,"%d/%d",scrollback_lines,myData->numLines());
	  slen = strlen(s);
//	  GetTextExtentPoint32(hdc,s,slen,&lineSize);
	  I_GetTextExtent(&backingStore, s, slen, &lineSize);
//	  TextOut(hdc,my_dimension.width - lineSize.cx - 10,
//	      draw_cur_y-lineSize.cy,s,slen);
	  I_TextOut(&backingStore, my_dimension.width - lineSize.cx - 10, 
	      draw_cur_y-lineSize.cy, s, slen);
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

//	  GetTextExtentPoint32(hdc,s,slen,&lineSize);	
	  I_GetTextExtent(&backingStore, s, slen, &lineSize);	
	  if ((draw_cur_y - lineSize.cy) > 0) {
	 //   TextOut(hdc,0,draw_cur_y-lineSize.cy,s, slen);
	    I_TextOut(&backingStore, 0, draw_cur_y-lineSize.cy, s, slen);
	  }

	  draw_cur_y -= lineSize.cy;

	}
      }

    } 

//    backingStore->ReleaseDC(hdc);
//  }

  this->setDirty();

}
#endif
