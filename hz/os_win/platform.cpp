// Platform.cpp
// 
// other platform specific stuff... see DrawHndl.cpp for
// the drawing related stuff...

// why do these need to be here? get rid of them
#include "..\Donuts.h"
#include "..\Game.h"
#include "..\View.h"
#include "..\Main.h"

#include "i_system.h" // i_time_ms();

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>

/*
 * MainWndproc
 *
 * Callback for all Windows messages
 */
long FAR PASCAL MainWndproc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC         hdc;
	IN_EVENT	ev;

    switch( message )
    {
    case WM_ACTIVATEAPP:
        bIsActive = (BOOL) wParam;
        if( bIsActive )
        {
            // bMouseVisible = FALSE;
            lastTickCount = i_time_ms();
            bSpecialEffects = FALSE;
        }
        else
        {
            bMouseVisible = TRUE;
        }
        break;

    case WM_CREATE:
        break;
	case WM_MBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MOUSEMOVE:
		if (realScreenView) {
			unsigned long int mask = 0;
			WPARAM fwKeys = wParam;        // key flags 
			unsigned short int xPos = LOWORD(lParam);  // horizontal position of cursor 
			unsigned short int yPos = HIWORD(lParam);  // vertical position of cursor 
			dbgMsg(c_excessive,"Mouse moved (%d,%d)",xPos,yPos);

			ev.dev_type = DT_MOUSE;
			ev.dev.mouse.xpos = xPos;
			ev.dev.mouse.ypos = yPos;
						
			if (fwKeys & MK_LBUTTON) {
				mask |= MS_L_BUTTON;
			} 
			if (fwKeys & MK_MBUTTON) {
				mask |= MS_M_BUTTON;
			}
			if (fwKeys & MK_RBUTTON) {
				mask |= MS_R_BUTTON;
			}
			ev.dev.mouse.mask =  (enum mouse_mask_enum) mask;

			realScreenView->inputEvent(&ev);

		}
		break;

    case WM_SETCURSOR:

        if( !bMouseVisible )
        {
            SetCursor(NULL);
        }
        else
        {
            SetCursor(LoadCursor( NULL, IDC_ARROW ));
        }
        return TRUE;

	case WM_CHAR:

		if (realScreenView) {
			static int count = 0;
			if (count) {
 				ev.dev_type = DT_KEYBOARD;
				ev.dev.keyboard.mask = (enum keyboard_mask_enum)(KM_ASCII_KEY);
				ev.dev.keyboard.ascii_code = wParam; // need to convert to ascii
				realScreenView->inputEvent(&ev);
			} else count++;
		}
		break;

    case WM_KEYDOWN:

		// if there is a screen, then pass the key
		if (realScreenView) {
 				ev.dev_type = DT_KEYBOARD;
				ev.dev.keyboard.mask = (enum keyboard_mask_enum)(KM_KEYDOWN);
				ev.dev.keyboard.vk_code = wParam;
				realScreenView->inputEvent(&ev);
		}

		switch (wParam) {
			case VK_RETURN:
				if( ProgramState == PS_SPLASH ) {
					ProgramState = PS_BEGINREST;
					DrawDisplayList();
					setup_game();
				}
				break;
			case VK_ESCAPE:
			case VK_F12:
				PostMessage( hWnd, WM_CLOSE, 0, 0 );
				return 0;
		}
        break;


    case WM_KEYUP:

		// if there is a screen, then pass the key
		if (realScreenView) {
				ev.dev_type = DT_KEYBOARD;
				ev.dev.keyboard.mask = KM_KEYUP;
				ev.dev.keyboard.vk_code = wParam;
				realScreenView->inputEvent(&ev);
		}
        break;

    case WM_ERASEBKGND:
        return 1;

    case WM_PAINT:
        hdc = BeginPaint( hWnd, &ps );
        EndPaint( hWnd, &ps );
		// return 1;
        return 0;

    case WM_DESTROY:
        lastInput=0;
        DestroyGame();
        PostQuitMessage( 0 );
        break;

    default:
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);

} /* MainWndproc */