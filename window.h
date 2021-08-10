#include "2048.h"

#ifndef DJKAPERMCXZ_H
#define DJKAPERMCXZ_H

extern int returnOverall;
extern Grid2048 grid;
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

void drawWindow(const Grid2048&);
void moveWindow(const Grid2048&);
void updateWindow(const Grid2048&);
void pauseWindow(void);

const int KEY_ESC = 278;

#endif // DJKAPERMCXZ_H
