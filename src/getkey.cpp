#include "../include/getkey.h"

#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER) ||                 \
    defined(__MINGW32__) || defined(__MINGW64__) || defined(__CYGWIN__)
#include <conio.h>
#define cls "cls"
#define GETKEY _getch
#else

#include <stdio.h>
#include <termios.h>

struct termios old, current;

void initTermios(int echo) {
	tcgetattr(0, &old);
	current = old;
	current.c_lflag &= ~ICANON;
	if (echo) {
		current.c_lflag |= ECHO; /* set echo mode */
	}
	else {
		current.c_lflag &= ~ECHO;
	}
	tcsetattr(0, TCSANOW, &current);
}

void resetTermios(void) { tcsetattr(0, TCSANOW, &old); }

char getch_(int echo) {
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}

#endif