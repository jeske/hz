// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

// Control.cpp
//
// This includes the control classes...
//

#include <dinput.h>
#include <stdio.h>
#include "Control.h"

unsigned int joy_present = 0;
unsigned int joystick_num;
JOYINFOEX joyinfo;
JOYCAPS   joycaps;
unsigned int joy_xcenter;
unsigned int joy_ycenter;
struct private_joyinfo_struct myjoyinfo;

void printJoyCapabilities(JOYCAPS *joyc) {
	printf("Joystick (Manuf ID: %d) (Product ID:%d) (Name: %s)\n",
		joyc->wMid,joyc->wPid,joyc->szPname);
	printf("[%d Buttons], [%d Axes]\n",joyc->wNumButtons,
		joyc->wNumAxes);

	// precompute the necessary data
    myjoyinfo.xcenter = joy_xcenter = (((long)joyc->wXmax + (long)joyc->wXmin) / (long)2);
	myjoyinfo.ycenter = joy_ycenter = (((long)joyc->wYmax + (long)joyc->wYmin) / (long)2);

	myjoyinfo.down_threshold = (((long)joy_ycenter + (long)joyc->wYmax) / 2);
	myjoyinfo.up_threshold = (((long)joy_ycenter + (long)joyc->wYmin) / 2);
	myjoyinfo.right_threshold = (((long)joy_xcenter + (long)joyc->wXmax) / 2);
	myjoyinfo.left_threshold = (((long)joy_xcenter + (long)joyc->wXmin) / 2);
	
	printf("X min:%d max:%d (computed center: %d) \n",
		joyc->wXmin,joyc->wXmax,joy_xcenter);
	printf("  left thresh: %u  right thresh: %u\n",
		myjoyinfo.left_threshold,myjoyinfo.right_threshold);
	printf("Y min:%d max:%d (computed center: %d) \n",
		joyc->wYmin,joyc->wYmax,joy_ycenter);
	printf("  down thresh: %u   up    thresh: %u\n",
		myjoyinfo.down_threshold,myjoyinfo.up_threshold);
	
}

extern "C" {
WINMMAPI MMRESULT WINAPI joyConfigChanged( DWORD dwFlags );
}

void initJoystick() {
	MMRESULT confres = joyConfigChanged(0);
	unsigned int numdevs = joyGetNumDevs();
	unsigned int loop;

	printf("joyGetNumDevs() returned (%u)\n",numdevs);

	joyinfo.dwSize = sizeof(JOYINFOEX);
	joyinfo.dwFlags = JOY_RETURNBUTTONS | JOY_RETURNX | 
						JOY_RETURNY | JOY_USEDEADZONE;

	for (loop=0;loop<numdevs;loop++) {
		printf("[Testing #%u] ",loop);
		switch(joyGetPosEx(loop,&joyinfo)) {
			default:
			case JOYERR_NOERROR:  // everything went well.
				joystick_num = loop;
				printf("Found Joystick #%d\n",joystick_num);	
				switch (joyGetDevCaps(loop,&joycaps,sizeof(JOYCAPS))) {
				case JOYERR_NOERROR:
					printf("capabilities retrieved\n");
					printJoyCapabilities(&joycaps);
					joy_present = 1;
					break;
				case MMSYSERR_INVALPARAM:
					printf("invalid parameter\n");
					break;
				case MMSYSERR_NODRIVER:
					printf("no driver\n");
					break;
				default:
					printf("unknown error\n");
					break;
				}
				break;
	
			case MMSYSERR_BADDEVICEID:
				printf("BadDeviceID\n");
				break;
			case MMSYSERR_INVALPARAM: 		
				printf("Invalid Parameter\n");
				break;
			case MMSYSERR_NODRIVER:
				printf("No driver\n");
				break;

			case JOYERR_UNPLUGGED:	 // try next device
				printf("unplugged...\n");
				break;
		}
		if (joy_present)
			return;
	}
	if (!joy_present) { // we didn't find one...
		printf("No joystick found!\n");
	}
}
