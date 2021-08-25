#ifndef DJKAPERMCXZ_H
#define DJKAPERMCXZ_H

#include "lib2048/2048.h"
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

class WindowGrid final{
public:
    WindowGrid(const Grid2048& grid, WINDOW* window = stdscr) noexcept:
        baseGrid(grid), gridWindow(window::grid::drawWindow(0, 0, grid, window))
    {

    }

    ~WindowGrid(){
        delwin(gridWindow);
    }

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
    const Grid2048& baseGrid;
    WINDOW* gridWindow;
};

class ScoreWindow final{
public:
    ScoreWindow(const Grid2048& grid, int y, int x):
    baseGrid(grid), scoreWindow(newwin(6, 10, y, x))
    {
        wrefresh(scoreWindow);
        update();
    }

    operator WINDOW* () noexcept{
        return scoreWindow;
    }

    WINDOW** refer() noexcept{
        return &scoreWindow;
    }

    void update(){
        mvwprintw(scoreWindow, 2, 2, "Score", baseGrid.getScore());
        mvwprintw(scoreWindow, 3, 3, "%d", baseGrid.getScore());
        wrefresh(scoreWindow);
    }

    void redraw(){
        box(*this, 0, 0);
        update();
    }

private:
    const Grid2048& baseGrid;
    WINDOW* scoreWindow;
};

class Layout final{
public:
    Layout(const Grid2048& gridIn):
    grid(gridIn), mainWindow(gridIn), scoreWindow(gridIn, 0, 0)
    {
        align();
        update();
    }

    void align(){
        //prefer putting score at left
        if((4 * grid.y + 2) < getmaxy(stdscr) && (7 * grid.x + 14) < getmaxx(stdscr)){
            mvwin(mainWindow, window::grid::middleY(grid)
                               , window::grid::middleX(grid) - 7 );
            mvwin(scoreWindow, getmaxy(stdscr) / 2 - 5
                               , getmaxx(stdscr) - 7 - window::grid::middleX(grid) / 2);

            redraw();
        }
        //if possible, draw on top instead
        else if((4 * grid.y + 6) < getmaxy(stdscr) && (7 * grid.x + 3) < getmaxx(stdscr)){
            mvwin(mainWindow, window::grid::middleY(grid) + 3
                               , window::grid::middleX(grid));
            mvwin(scoreWindow, window::grid::middleY(grid) - 3
                               , getmaxx(stdscr) / 2 - 5);

            redraw();
        }
        else{
            int input;

            do{
                clear();
                flash();
            }
            while(input = getch(), input != KEY_RESIZE);

            align();
        }
    }

    Layout& update(){
        mainWindow.update();
        scoreWindow.update();

        wrefresh(*scoreWindow.refer());
        wrefresh(*mainWindow.refer());

        return *this;
    }

    Layout& redraw(){
        clear();
        refresh();

        mainWindow.redraw();
        scoreWindow.redraw();

        wrefresh(*scoreWindow.refer());
        wrefresh(*mainWindow.refer());

        return *this;
    }

private:
    const Grid2048& grid;
    WindowGrid mainWindow;
    ScoreWindow scoreWindow;
};

#endif // DJKAPERMCXZ_H
