// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

//
// i_net.cpp
//
// platform specific network code..
//
// you will notice that ***ALL*** of this code is ifdef(ed) out right now
//


// these are console commands which should get 'registered'

#ifdef REMOVE_DPLAY	
	{ "LIST_NETIF","List Net interface devices available", cmd_list_netif}, 
	{ "CONNECT_NETIF", "Connect with a net interface", cmd_connect_netif},
	{ "DPLAY_JOIN_GAME", "Join an existing Dplay game", cmd_join_dplay_game},
	{ "DPLAY_NEW_GAME", "Create new Dplay Game", cmd_create_dplay_game},
	{ "DPLAY_LIST_GAMES", "List the existing Dplay games", cmd_enumerate_dplay_games},
	{ "DPLAY_LIST_PLAYERS", "List the existing DPlay players", cmd_enumerate_dplay_players},
	{ "DPLAY_NEW_SERVER", "Create a new dplay server", cmd_new_server},
#endif


#ifdef REMOVE_DPLAY

int cmd_list_netif(char *, ConsoleView *myConsole) {
	struct DPlayDev_struct *walker = dplay_head;
	char s[100];
	int count = 0;

	while (walker) {
		sprintf(s,"(%02d) %s v%d.%d",walker->index, walker->name, walker->major_version, walker->minor_version);
		myConsole->addText(s);
		count++;
		walker = walker->next;
	}
	sprintf(s,"[%d devices]",count);
	myConsole->addText(s);
	return 0;
}

int dplay_interface = -1;
LPDIRECTPLAY2A DPlay_obj = NULL;
LPDIRECTPLAY2A DPlay_srv_obj = NULL;

int cmd_connect_netif(char *str, ConsoleView *myConsole) {
	struct DPlayDev_struct *walker = dplay_head;
	int index;
	LPDIRECTPLAY dPlay_tmp;

	HRESULT result;

	index = atoi(str);
	
	while (walker && (walker->index!=index)) {
			walker = walker->next;
	}

	if (walker) {
		// setup dplay!
		myConsole->addText("cmd_connect_netif: setting up dplay dev");
		myConsole->addText(walker->name);
		
		result = DirectPlayCreate(&(walker->guid),&dPlay_tmp, NULL);
		if (!FAILED(result)) {
			result = dPlay_tmp->QueryInterface(IID_IDirectPlay2A, (LPVOID *) &DPlay_obj);
			dPlay_tmp->Release();
			if (!FAILED(result)) {
					// we have a valid DPlay2 interface!
					myConsole->addText("Dplay2 dev create succeeded");
					// enumerate the interfaces
					cmd_enumerate_dplay_games("",myConsole);
					dplay_interface = index;
					return 0;
			} else {
				DPlay_obj = NULL;
			}
		}

		myConsole->addText("Dplay2 dev create failed!");
		
		return 1;
	} else {
		// invalid index..
		myConsole->addText("cmd_connect_netif: Invalid Index");
		return 1;
	}

}

GUID *firstgameGUID = NULL;

int cmd_join_dplay_game(char *str, ConsoleView *myConsole) {
	HRESULT result;
	DPSESSIONDESC2 sessionDesc;
	DPNAME dpName;
	DPID dpidPlayer; // playerID

	
	if (firstgameGUID) {
		// Join an existing session.
		ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
		sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
		sessionDesc.guidInstance = *firstgameGUID;
		
		result = DPlay_obj->Open(&sessionDesc, DPOPEN_JOIN);
		if (FAILED(result)) {
			myConsole->addText("Join game failed...");
			return 1;
		} 

		myConsole->addText("Join game worked..");
		// Fill out the name structure.
		ZeroMemory(&dpName, sizeof(DPNAME));
		dpName.dwSize = sizeof(DPNAME);
		dpName.lpszShortNameA = str;
		dpName.lpszLongNameA = NULL;

		{ char s[100];
		sprintf(s, "Player Name: %s",str);
		myConsole->addText(s);
		}
		
		// Create a player with this name.
		// lpDPInfo->hPlayerEvent
		// if you suppily something in the third field, it will signal this
		// "event" when something is received.. This is good for multithreaded
		// event handlers...
		result = DPlay_obj->CreatePlayer(&dpidPlayer, &dpName, NULL, NULL, 0, 0);
		if (FAILED(result)) {
			myConsole->addText("create player failed");
			return 1;
		}


		return 0;
	} else {
		myConsole->addText("Must Enumerate Games first...");
		return 1;
	}


}

int cmd_new_server(char *str, ConsoleView *myConsole) {
	struct DPlayDev_struct *walker = dplay_head;
	int index = dplay_interface;
	LPDIRECTPLAY dPlay_tmp;
	DPNAME dpName;
	DPSESSIONDESC2 sessionDesc;
	HRESULT result;
	DPID dpidPlayer; // really the server dpid
	char *gamename;

	// remove whitespace
	while (str && (*str==' ')) {
		str++;
	}

	// set the gamename
	if (*str) {
		gamename = str;
	} else {
		gamename = "[unnamed]";
	}

	// make sure we know what interface to use..
	if (index < 0) {
		myConsole->addText("No Interface selected.. use connect_netif");
		return 0;
	}
	

	// find the interface...
	while (walker && (walker->index!=index)) {
			walker = walker->next;
	}


	// if we found an interface...
	if (walker) {
		// setup dplay!
		myConsole->addText("cmd_connect_netif: setting up dplay server dev");
		myConsole->addText(walker->name);
		
		result = DirectPlayCreate(&(walker->guid),&dPlay_tmp, NULL);

		if (!FAILED(result)) {
			result = dPlay_tmp->QueryInterface(IID_IDirectPlay2A, (LPVOID *) &DPlay_srv_obj);
			dPlay_tmp->Release();
			if (!FAILED(result)) {
					// we have a valid DPlay2 interface!
					myConsole->addText("Dplay2 server dev create succeeded");

					// create a new game for the server
					if (!DPlay_srv_obj) {
						myConsole->addText("no DPlay server object");
						return 1;
					}

					// Host a new session.
					ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
					sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
					sessionDesc.dwFlags = DPSESSION_KEEPALIVE;
					sessionDesc.guidApplication = HZ_GUID;
					sessionDesc.dwMaxPlayers = 8;
					sessionDesc.lpszSessionNameA = gamename;

					result = DPlay_srv_obj->Open(&sessionDesc, DPOPEN_CREATE);
					
					if (FAILED(result)) {
						myConsole->addText("Dplay server game create failed..");
						return 0;
					}
					myConsole->addText("Dplay server game created...");

					// create a server player...

					ZeroMemory(&dpName, sizeof(DPNAME));
					dpName.dwSize = sizeof(DPNAME);
					dpName.lpszShortNameA = "_srvr";
					dpName.lpszLongNameA = "HZ Server v0.1";

					result = DPlay_srv_obj->CreatePlayer(&dpidPlayer, &dpName, NULL, NULL, 0, 0);
					if (FAILED(result)) {
						myConsole->addText("create server player failed");
						return 1;
					} else {
						myConsole->addText("create server player worked..");
					}

					// enumerate the interfaces
					cmd_enumerate_dplay_games("",myConsole);
					return 0;
			} else {
				DPlay_srv_obj = NULL;
			}
		} else {
				myConsole->addText("Dplay server dev create failed");
				return 0;
		}
		
	} else {
		myConsole->addText("Dplay2 dev create failed!");
		return 0;
	}
	return 0;
}


int cmd_create_dplay_game(char *str, ConsoleView *myConsole) {
	HRESULT result;
	DPSESSIONDESC2 sessionDesc;
	DPNAME dpName; 
	DPID dpidPlayer; // player ID

	if (!DPlay_obj) {
		myConsole->addText("no DPlay object created");
		return 1;
	}

	// Host a new session.
	ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
	sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
//	sessionDesc.dwFlags = DPSESSION_MIGRATEHOST | DPSESSION_KEEPALIVE;
	// we're not going to migrate, because we have a dedicated server...
    sessionDesc.dwFlags = DPSESSION_KEEPALIVE;
	sessionDesc.guidApplication = HZ_GUID;
	sessionDesc.dwMaxPlayers = 8;
	sessionDesc.lpszSessionNameA = "HZ";

	result = DPlay_obj->Open(&sessionDesc, DPOPEN_CREATE);

	if (!FAILED(result)) {
		myConsole->addText("Dplay game created...");

		// FIRST, create a server...

		// Fill out the name structure.
		ZeroMemory(&dpName, sizeof(DPNAME));
		dpName.dwSize = sizeof(DPNAME);
		dpName.lpszShortNameA = "_srvr";
		dpName.lpszLongNameA = "GameServer v0.1";

		{ char s[100];
		sprintf(s, "ServerName: (%s/%s)",dpName.lpszShortNameA,dpName.lpszLongNameA);
		myConsole->addText(s);
		}
		
		// Create a player with this name.
		// lpDPInfo->hPlayerEvent
		// if you suppily something in the third field, it will signal this
		// "event" when something is received.. This is good for multithreaded
		// event handlers...
		result = DPlay_obj->CreatePlayer(&dpidPlayer, &dpName, NULL, NULL, 0, 0);
		if (FAILED(result)) {
			myConsole->addText("create server player failed");
			return 1;
		}

		// Fill out the name structure.
		ZeroMemory(&dpName, sizeof(DPNAME));
		dpName.dwSize = sizeof(DPNAME);
		dpName.lpszShortNameA = str;
		dpName.lpszLongNameA = NULL;

		{ char s[100];
		sprintf(s, "Player Name: %s",str);
		myConsole->addText(s);
		}
		
		// Create a player with this name.
		// lpDPInfo->hPlayerEvent
		// if you suppily something in the third field, it will signal this
		// "event" when something is received.. This is good for multithreaded
		// event handlers...
		result = DPlay_obj->CreatePlayer(&dpidPlayer, &dpName, NULL, NULL, 0, 0);
		if (FAILED(result)) {
			myConsole->addText("create player failed");
			return 1;
		}
		return 0;
	} else {
		myConsole->addText("cmd_create_dplay_game: failed");
	}
	return 1;
}

BOOL PASCAL EnumSessionsCallback(LPCDPSESSIONDESC2 lpSessionDesc, LPDWORD lpdwTimeOut,
									 DWORD dwFlags, LPVOID lpContext) {
	HWND   hWnd = lpContext;
//	LPGUID lpGuid;
//	LONG   iIndex;
	char s[100];
	
	// Determine if the enumeration has timed out.
	if (dwFlags & DPESC_TIMEDOUT)
		return (FALSE);            // Do not try again

	if (!firstgameGUID) {
		firstgameGUID = (GUID *)malloc(sizeof(GUID));
		if (firstgameGUID) {
			*firstgameGUID = lpSessionDesc->guidInstance; // setup the GUID for the "first" session
		}
	}

	sprintf(s,"Game Session: %s (%d/%d players)",lpSessionDesc->lpszSessionNameA,
		lpSessionDesc->dwCurrentPlayers,
		lpSessionDesc->dwMaxPlayers);
	consoleView->addText(s);

	// Store the session name in the list.
//	iIndex = SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_ADDSTRING, (WPARAM) 0, (LPARAM) lpSessionDesc->lpszSessionNameA);
//	if (iIndex == CB_ERR)
//		goto FAILURE;
	
	// Make space for the session instance GUID.
//	lpGuid = (LPGUID) GlobalAllocPtr(GHND, sizeof(GUID));
//	if (lpGuid == NULL)
//		goto FAILURE;
	
	// Store the pointer to the GUID in the list.
//	*lpGuid = lpSessionDesc->guidInstance;
//	SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_SETITEMDATA, 
//		(WPARAM) iIndex, (LPARAM) lpGuid);
	
//FAILURE:
//    return (TRUE);
		return TRUE;
}
	


int cmd_enumerate_dplay_games(char *str, ConsoleView *myConsole) {
	HRESULT result;
	DPSESSIONDESC2 sessionDesc;

	// Search for this kind of session.
	ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
	sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
	sessionDesc.guidApplication = HZ_GUID;
	
	result = DPlay_obj->EnumSessions(&sessionDesc, 0, EnumSessionsCallback,	hWndMain, DPENUMSESSIONS_AVAILABLE);
	if (FAILED(result)) {
		myConsole->addText("enumerate sessions failed...");
		return 1;
	}

	myConsole->addText("Enumerate sessions worked..");
	return 0;
}

BOOL PASCAL EnumPlayersCB(DPID dpId,DWORD dwPlayerType, LPCDPNAME lpName,
								 DWORD dwFlags, LPVOID lpContext) {
	char s[100];

	sprintf(s,"Player: [%X] (%s) %s",dwPlayerType, lpName->lpszShortNameA, lpName->lpszLongNameA);
	consoleView->addText(s);

	return TRUE;
}



int cmd_enumerate_dplay_players(char *str, ConsoleView *myConsole) {
	HRESULT result;
	
	result = DPlay_obj->EnumPlayers(NULL,EnumPlayersCB, hWndMain, 0);
	if (FAILED(result)) {
		myConsole->addText("Enum Players Failed...");
		return 1;
	} else {
		myConsole->addText("Enum Players Worked...");
		return 0;
	}

}


#endif // REMOVE_DPLAY



// this stuff was pulled out of net.cpp

#ifdef REMOVE_DPLAY
struct DPlayDev_struct *dplay_head = NULL;
static int dplay_index_count = 0;

void addDplayDev(struct DPlayDev_struct *a_elem) {
	a_elem->next = dplay_head;
	dplay_head = a_elem;
}


BOOL FAR PASCAL DirectPlayEnumerateCallback(LPGUID lpSPGuid, LPTSTR lpszSPName, 
					DWORD dwMajorVersion, DWORD dwMinorVersion, LPVOID lpContext) {
	HWND    hWnd = lpContext;
// LRESULT iIndex;
// LPGUID  lpGuid;

	if (consoleView) {
		char s[100];
		struct DPlayDev_struct *newdev = (struct DPlayDev_struct *)malloc(sizeof(struct DPlayDev_struct));

		if (newdev) {

			sprintf(s,"DirectPlay Dev: (%02d) %s v%d.%d", dplay_index_count, lpszSPName, dwMajorVersion, dwMinorVersion);
			consoleView->addText(s);

			strncpy(newdev->name,lpszSPName,79);
			newdev->name[79] = 0;
			newdev->guid = *lpSPGuid;
			newdev->major_version = dwMajorVersion;
			newdev->minor_version = dwMinorVersion;
			newdev->index = dplay_index_count++;
			addDplayDev(newdev);
			
		} else {
			consoleView->addText("Out of memory adding DPlayDev");
		}
	} else {
		printf("DirectPlay Dev: %s v%d.%d\n", lpszSPName, dwMajorVersion, dwMinorVersion);
	}

/*
		// Store the service provider name in a combo box.
		iIndex = SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_ADDSTRING,
				0, (LPARAM) lpszSPName);
		if (iIndex == CB_ERR)
				goto FAILURE;

		// Make space for the application GUID.
		lpGuid = (LPGUID) GlobalAllocPtr(GHND, sizeof(GUID));
		if (lpGuid == NULL)
			goto FAILURE;

		// Store the pointer to the GUID in a combo box.
		*lpGuid = *lpSPGuid;
		SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_SETITEMDATA, 
			(WPARAM) iIndex, (LPARAM) lpGuid);


FAILURE:
*/
		return (TRUE);
}



void testNet(void) {
	DirectPlayEnumerate(DirectPlayEnumerateCallback, hWndMain);	
}

#endif // REMOVE_DPLAY


