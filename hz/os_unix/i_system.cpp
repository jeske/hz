// HZ Engine Source
// Copyright (C) 1999 by Brandon C. Long


//
// i_system.cpp
//
// system dependent general stuff
//

#include "i_system.h"
#include <sys/time.h>
#include "i_console.h"
#include <stdlib.h>

// do nothing on unix!

const char *i_fix_path(const char *a_path) {
  return (a_path);
}

// return the system time in ms

unsigned long int i_time_ms() {
  static struct timeval last;
  struct timeval current;
  static unsigned long int last_ms = 0;

  gettimeofday(&current, NULL);
  if (last.tv_sec != 0)
  {
    last_ms += (current.tv_sec - last.tv_sec) * 1000 + 
      (current.tv_usec - last.tv_usec) / 1000;
  } 
  last = current;
  return last_ms;
}


int CleanupAndExit( char *err)
{
  I_Message ("CleanupAndExit: %s\n", err);

  exit(1);
}

void i_convert_path (char *path)
{
  char *c;

  c = path;

  while (*c)
  {
    if (*c == '\\')
      *c = '/';
    c++;
  }
}



#if 0

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



}

#endif
#endif
