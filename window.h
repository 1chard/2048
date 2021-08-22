#ifndef DJKAPERMCXZ_H
#define DJKAPERMCXZ_H

#include "lib2048/2048.h"
#include <ncurses/curses.h>

WINDOW* drawWindow(const Grid2048&, WINDOW* baseWindow = stdscr);
void moveWindow(WINDOW**, const Grid2048&, int*);
void updateWindow(WINDOW*, const Grid2048&);

class WindowGrid final{
public:
    WindowGrid(const Grid2048& grid, WINDOW* window = stdscr) noexcept:
    baseGrid(grid), gridWindow(drawWindow(grid, window))
    {

    }

    ~WindowGrid(){
        delwin(gridWindow);
    }

    operator WINDOW* () noexcept{
        return gridWindow;
    }

    WindowGrid& move(int* ptr) noexcept{
        moveWindow(&gridWindow, baseGrid, ptr);

        return *this;
    }

    static void init_colors(short bgcolor = COLOR_BLACK) noexcept{
        init_pair(P_GREEN, COLOR_GREEN, bgcolor);
        init_pair(P_YELLOW, COLOR_YELLOW, bgcolor);
        init_pair(P_MAGENTA, COLOR_MAGENTA, bgcolor);
        init_pair(P_RED, COLOR_RED, bgcolor);
        init_pair(P_BLUE, COLOR_BLUE, bgcolor);
        init_pair(P_CYAN, COLOR_CYAN, bgcolor);
        init_pair(P_WHITE, COLOR_WHITE, bgcolor);
        init_pair(P_BLACK, COLOR_BLACK, bgcolor);
    }

    enum ColorsPair{
        P_RED = 1,
        P_GREEN,
        P_BLUE,
        P_MAGENTA,
        P_YELLOW,
        P_CYAN,
        P_WHITE,
        P_BLACK
    };

    friend void delwin(WindowGrid& window) noexcept{
        window.~WindowGrid();
    }

private:
    const Grid2048& baseGrid;
    WINDOW* gridWindow;
};


#endif // DJKAPERMCXZ_H
