#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include "getch.h"

static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

char getchNoBuff()
{
  char ch;
  initTermios(0);
  fd_set rfds;
  struct timeval tv;
  int retval;
	
  FD_ZERO(&rfds);
  FD_SET(0, &rfds);
		
  tv.tv_sec = 0;
  tv.tv_usec = 100000;	
  retval = select(2, &rfds, NULL, NULL, &tv);

  if (retval) {
    ch = getchar();
  }
  else
  {
    ch = '\0'; 
  }
  FD_CLR(0, &rfds);
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

