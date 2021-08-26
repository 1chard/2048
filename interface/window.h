#ifndef DJKAPERMSSS_H
#define DJKAPERMSSS_H

#include "../lib2048/2048.h"
#include <curses.h>

namespace window{
    void moveWindow(WINDOW**, int, int);

    namespace grid{
        WINDOW* drawWindow(int y, int x, const Grid2048&, WINDOW* baseWindow = stdscr);
        void align(WINDOW**, const Grid2048&, int*);
        void redraw(WINDOW* window, const Grid2048& grid);

        void update(WINDOW*, const Grid2048&);
        int middleY(const Grid2048&);
        int middleX(const Grid2048&);
    } //grid
} //window

#endif // DJKAPERMSSS_H
