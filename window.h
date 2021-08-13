#include "2048.h"

#ifndef DJKAPERMCXZ_H
#define DJKAPERMCXZ_H

extern int returnOverall;
extern WINDOW* gameWindow;

enum ColorsPair{
    P_RED = 1,
    P_GREEN,
    P_BLUE,
    P_MAGENTA,
    P_YELLOW,
    P_ORANGE,
    P_LIGHTBLUE,
    P_DARKBLUE
};
enum ColorsExtra{
    COLOR_ORANGE = 127,
    COLOR_LIGHTBLUE,
    COLOR_DARKBLUE
};

WINDOW* drawWindow(const Grid2048&);
void moveWindow(WINDOW*, const Grid2048&);
void updateWindow(WINDOW*, const Grid2048&);

#endif // DJKAPERMCXZ_H
