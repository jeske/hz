#ifdef REMOVE_CRAP
    DWORD       input = lastInput;
    BOOL        an_event = FALSE;
	double dest_dir; // 0-39 direction values
	unsigned int control_centered = 0;
	unsigned int joy_centered = 1;
	Sprite *new_obj;



	if (joy_present && joyGetPosEx(joystick_num,&joyinfo) != JOYERR_NOERROR) {
		// joystick error!!!
		
	}

    if( bTest )
    {
        input |= (KEY_RIGHT | KEY_FIRE);
    }
    lastTickCount = thisTickCount;

    if (showDelay)
    {
        showDelay -= (int)tickDiff;
        if (showDelay < 0)
        {
            showDelay = 0;
            lastShield = FALSE;
            // initShip( FALSE );
        }
    }


    
    if (an_event)
    {
#ifdef USE_DSOUND
        if(bWantSound) {
            playPanned(hsoShipBounce, &DL);
        }
#endif
        an_event = FALSE;
    }

    if ((an_event = (showDelay || ((input & KEY_SHIELD) == KEY_SHIELD))) !=
        lastShield)
    {
        if (an_event && !showDelay)
                {
#ifdef USE_DSOUND
                if(bWantSound)
                {
                    SndObjPlay(hsoShieldBuzz, DSBPLAY_LOOPING);
                        }
#endif
                    bPlayBuzz = TRUE;
                }
        else
                {
#ifdef USE_DSOUND
                if(bWantSound)
                {
                SndObjStop(hsoShieldBuzz);
                        }
#endif
                bPlayBuzz = FALSE;
            }
        lastShield = an_event;
    }
    if (an_event)
    {
        input &= ~(KEY_FIRE);
    }

	if (joy_present && (joyinfo.dwButtons & JOY_BUTTON2)) { // screen flip
		if (!button_down) {
			// they just pressed it, so do a screen flip
			mainTabView->nextView();
			button_down = 1;
		} 
	} else {
		if (button_down) {
			// they just let it go, so do a screen flip
			mainTabView->nextView();
			button_down = 0;
		}
	}

    if ((input & KEY_FIRE) || (joy_present && (joyinfo.dwButtons & JOY_BUTTON1)))
    {

        if( !showDelay )
        {
            // add a bullet to the scene
            score--;
            if(score < 0)
                score = 0;

#ifdef USE_DSOUND
                if(bWantSound) 
                SndObjPlay(hsoFireBullet, 0);
                }
#endif

				if ((joy_present) && (!(joyinfo.dwButtons & JOY_BUTTON1))) {
					SpriteType *type = findSpriteType("donut");
					
					if (type) {
						consoleView->addText("adding SpriteType [donut]");
						new_obj = new Sprite(defaultSpriteList, type , 
								-1.0,-1.0,-1.0,-1.0);
					}
					g_num_donuts++;
				}

				if ((joy_present) && (joyinfo.dwButtons & JOY_BUTTON1)) {
					SpriteType *type;
					type = findSpriteType("donut");
					if (type) {
						consoleView->addText("adding SpriteType sprite");
						new_obj = new Sprite(defaultSpriteList, type , -1,-1,-1,-1);
					} else {
						consoleView->addText("no Dude SpriteType!");
					}
				}


        }
    }

    an_event = FALSE;


	// Process joystick input

	if (joy_present) { // if there is a joystick, process the joystick input
		joy_centered = 0;
		// printf("dwXpos: %u   dwYpos: %u\n",joyinfo.dwXpos,joyinfo.dwYpos);

		if (joyinfo.dwXpos > myjoyinfo.right_threshold) {
			//right
			if (joyinfo.dwYpos < myjoyinfo.up_threshold) {
				//up (up/right)
				dest_dir = 5;
			} else if (joyinfo.dwYpos > myjoyinfo.down_threshold) {
				// down (down/right)
				dest_dir = 15;
			} else {
				// plain right
				dest_dir = 10;
			}
		} else if (joyinfo.dwXpos < myjoyinfo.left_threshold) {
			//left
			if (joyinfo.dwYpos < myjoyinfo.up_threshold) {
				//up (up/left)
				dest_dir = 35;
			} else if (joyinfo.dwYpos > myjoyinfo.down_threshold) {
				// down (down/left)
				dest_dir = 25;
			} else {
				// plain left
				dest_dir = 30;
			}
		} else {
			if (joyinfo.dwYpos < myjoyinfo.up_threshold) {
				// up (plain up)
				dest_dir = 0;
			} else if (joyinfo.dwYpos > myjoyinfo.down_threshold) {
				// down (plain down)
				dest_dir = 20;
			} else {
				joy_centered = 1;
			}

		}

		
	}


	// old stuff below

    if (an_event != lastThrust)
    {
        if (an_event)
        {
            input &= ~KEY_STOP;
#ifdef USE_DSOUND
            if(bWantSound)
            {
                SndObjStop(hsoSkidToStop);
                SndObjPlay(hsoEngineRev, DSBPLAY_LOOPING);
                        }
#endif
            bPlayRev = TRUE;
        }
        else
        {
#ifdef USE_DSOUND
        if(bWantSound)
        {
            SndObjStop(hsoEngineRev);
                }
#endif
            bPlayRev = FALSE;
        }

        lastThrust = an_event;
    }

    if( input & KEY_STOP )
    {
#ifdef USE_DSOUND
        if(bWantSound)
        {
                if (DL.velx || DL.vely)
                    playPanned(hsoSkidToStop, &DL);
                }
#endif

}
#endif    