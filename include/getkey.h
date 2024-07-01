#pragma once

#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER) ||                 \
    defined(__MINGW32__) || defined(__MINGW64__) || defined(__CYGWIN__)

#include <conio.h>
#define cls "cls"
#define GETKEY _getch

#else

char getch_(int echo);

#define cls "clear"
#define GETKEY() getch_(0);

#endif