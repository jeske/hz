// HZ Engine Source
// Copyright (C) 1999 by David W. Jeske

//
// i_system.cpp
//
// system dependent general stuff
//

#include <string.h>

#include "i_system.h"
#include "i_video.h"
#include "..\VConsole.h"
#include "hndlmgr.h"
#include "..\donuts.h" // bMouseVisable
#include "..\main.h" // realScreenView (which we shouldn't be deleting here anyhow)

unsigned long int i_time_ms() {
	return (timeGetTime());
}


const char *i_fix_path(const char *fix_path) {
  char *next_chr = (char *)fix_path;
  
  while (next_chr = strchr(next_chr,'/')) {
    *next_chr = '\\'; // convert to backslash
    next_chr++;       // advance
  }
  return fix_path;
}
  
int CleanupAndExit( char *err)
{
	dbgMsg(c_info,"CleanupAndExit:");
	
	delete hndlMgr;
	hndlMgr = 0;

//	should_die = 1;

    // make the cursor visible
    SetCursor(LoadCursor( NULL, IDC_ARROW ));
    bMouseVisible = TRUE;

    if( lpFrontBuffer != NULL )
        lpFrontBuffer->Release();

    if( lpSplashPalette != NULL )
        lpSplashPalette->Release();

    if( lpDD != NULL )
        lpDD->Release();


#if 0
	if( lpTile00 != NULL )
		lpTile00->Release();

	if( lpTile01 != NULL )
		lpTile01->Release();

	if( lpTile02 != NULL )
		lpTile02->Release();

#endif

	if (realScreenView) {
		delete realScreenView;
	}

    //
    // warn user if there is one
    //

    if( !bStress )
    {
        MessageBox( hWndMain, err, "ERROR", MB_OK );
    }
	exit(1);
    //return FALSE; // exit(1);  !!!FIX!!!
	return FALSE;
}





//
//
///////////////////
//
// CRAP BELOW
//
//
///////////////////
//
//




#ifdef REMOVEPIPE
DWORD ThreadFunc(LPDWORD lpdwParam) { 
    // printf("ThreadFunc:  thread parameter=%d\n", *lpdwParam); 
	char buf[4097];
	unsigned long int bytes_read;
	int bResult;


	while (!consoleView) {
	Sleep(400);
	}
	Sleep(400);
	consoleView->addText("I/O thread active");

	while (!should_die) {

		if (input_pipe) {
			// attempt a synchronous read operation 
			bResult = ReadFile(input_pipe, buf, 4096, &bytes_read, NULL) ; 
			// check for eof 
			if (bResult &&  (bytes_read == 0)) { 
				// we're at the end of the file 
				consoleView->addText("at EOF");
			} else {
				sprintf(buf,"Got [%d] characters",bytes_read);
				consoleView->addText(buf);
			}
		} else {
			consoleView->addText("Null PIPE!");
		}
		
		// if ((bytes_read = _read(input_pipe_fd, buf, 4096)) <= 0) {
// 			sprintf(buf,"Error [%d] reading pipe",bytes_read);
//			consoleView->addText(buf);
 //		} else {
 //			sprintf(buf, "Got [%d] characters", bytes_read);
 //			consoleView->addText(buf);
//		}
		

		Sleep(400);
	}

    return 0; 
} 

enum PIPES { READ = 0 , WRITE = 1};

#endif

#ifdef REMOVEPIPE
void init_pipe() {

//	int pipefds[2];

	return;

	printf("Initpipe (stdio)\n");
	fflush(stdout);
	fprintf(stderr,"Initpipe (stderr)\n");
	fflush(stderr);

//	if (_pipe(pipefds,4096,O_BINARY) != -1) {
		// it worked!
		// create a reader thread and shove stdio into it

		// do the crappy named pipe stuff too...
		input_pipe = CreateNamedPipe("\\\\.\\pipe\\mystdout", PIPE_ACCESS_INBOUND , 0, 2, 
			2048, 2048, 100, 0);

		SECURITY_ATTRIBUTES saPipe;
			/*	set up a NULL DACL in our pipe security descriptor to allow anyone to
				connect to the pipe server */
		saPipe.lpSecurityDescriptor =
			(PSECURITY_DESCRIPTOR) malloc(SECURITY_DESCRIPTOR_MIN_LENGTH);
		InitializeSecurityDescriptor(saPipe.lpSecurityDescriptor,
			SECURITY_DESCRIPTOR_REVISION);
		SetSecurityDescriptorDacl(saPipe.lpSecurityDescriptor, TRUE, (PACL) NULL,
			FALSE);
		saPipe.nLength = sizeof(saPipe);
		saPipe.bInheritHandle = TRUE;

		input_pipe = CreateNamedPipe("\\\\.\\pipe\\hzout", PIPE_ACCESS_DUPLEX, 
			PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 0, 0, 
			60000, &saPipe);

		if (!input_pipe) {
			fprintf(stdout,"shit, named pipe didn't create!\n");
			fflush(stdout);
		} else {
			fprintf(stdout,"Hey, it worked...\n");
			fflush(stdout);
		}

		
//		freopen("\\\\.\\pipe\\hzout","w",stdout);





//		real_stdio = _dup(1); // move stdio
//		if (real_stdio < 0) {
//			// damn, it failed... just make it stderr
//			real_stdio = 2;
//		}

//		real_stderr = _dup(2); // move stderr
//		if (real_stderr < 0) {
//			real_stderr = 2;
//		}

//		if (_dup2(pipefds[WRITE],1) == -1) {
//			// dup2 failed, so forget this whole redirect
//			// thing...
//			return;
//		}
//		if (_dup2(pipefds[WRITE],2) == -1) {
//			// oops, we couldn't put it on stderr
//		}
//		FILE *stdout_sav = stdout;
//		if (((FILE *)stdout = _fdopen(1,"a")) == NULL) {
//			stdout = stdout_sav;
//		} else {
//			fclose(stdout_sav);
//		}
//
//		// create the reader thread...
//		input_pipe_fd = pipefds[READ];



		DWORD dwThreadId, dwThrdParam = 1; 
		HANDLE hThread; 
		hThread = CreateThread( 
			NULL,                        /* no security attributes        */ 
			0,                           /* use default stack size        */ 
			(LPTHREAD_START_ROUTINE) ThreadFunc, /* thread function       */ 
			&dwThrdParam,                /* argument to thread function   */ 
			0,                           /* use default creation flags    */ 
			&dwThreadId);                /* returns the thread identifier */ 
 
		/* Check the return value for success. */ 
 
		if (hThread == NULL) {
			// iothread couldn't create... ohh well...
			// we should put back stdio now..
			fprintf(stderr, "IOThread failed to create...\n");
			fflush(stderr);
		}

//	} else {
//		// oops, it failed
//	}


}

#endif
