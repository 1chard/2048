#ifndef WINDOWGRIDFD_H
#define WINDOWGRIDFD_H

#include "window.h"

class Layout;

class WindowGrid final{
public:
    WindowGrid(const Grid2048& grid, WINDOW* window = stdscr) noexcept:
        baseGrid(grid), gridWindow(window::grid::drawWindow(0, 0, grid, window))
    {

    }

    ~WindowGrid(){
        deleteWindow();
    }

    friend class Layout;

    operator WINDOW* () noexcept{
        return gridWindow;
    }

    WINDOW** refer() noexcept{
        return &gridWindow;
    }

    WindowGrid& align(int* ptr) noexcept{
        window::grid::align(&gridWindow, baseGrid, ptr);

        return *this;
    }

    WindowGrid& redraw() noexcept{
        window::grid::redraw(*this, baseGrid);
        wrefresh(*this);

        return *this;
    }

    WindowGrid& update(){
        window::grid::update(gridWindow, baseGrid);

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
    void deleteWindow() noexcept{
        if(gridWindow){
            delwin(gridWindow);
            gridWindow = NULL;
        }
    }

    const Grid2048& baseGrid;
    WINDOW* gridWindow;
};

#endif // WINDOWGRIDFD_H
