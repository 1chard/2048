#ifndef DJKAPERMCXZ_H
#define DJKAPERMCXZ_H

#include "lib2048/2048.h"
#include <ncurses/curses.h>

extern int returnOverall;

enum ColorsPair{
    P_RED = 1,
    P_GREEN,
    P_BLUE,
    P_MAGENTA,
    P_YELLOW,
    P_CYAN
};

WINDOW* drawWindow(const Grid2048&);
void moveWindow(WINDOW**, const Grid2048&, int*);
void updateWindow(WINDOW*, const Grid2048&);

#endif // DJKAPERMCXZ_H
