// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

// Control.h
//
//

#ifndef CONTROL_H
#define CONTROL_H

struct private_joyinfo_struct {
	unsigned int xcenter;
	unsigned int ycenter;
	unsigned int up_threshold;
	unsigned int down_threshold;
	unsigned int left_threshold;
	unsigned int right_threshold;
};


extern struct private_joyinfo_struct myjoyinfo;
extern unsigned int joy_present;
extern unsigned int joystick_num;
extern JOYINFOEX joyinfo;
extern JOYCAPS   joycaps;
extern unsigned int joy_xcenter;
extern unsigned int joy_ycenter;

void initJoystick();

#endif // CONTROL_H
