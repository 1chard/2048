#ifndef MXPQMFAJFKD_H
#define MXPQMFAJFKD_H

#include "WindowGrid.h"
#include "ScoreWindow.h"
#include "window.h"

class Layout final{
public:
    Layout(const Grid2048& gridIn):
    grid(gridIn), mainWindow(gridIn), scoreWindow(gridIn)
    {
        align();
        update();
    }

    void align(){
        //prefer putting score at left
        if((4 * grid.y + 2) < getmaxy(stdscr) && (7 * grid.x + 14) < getmaxx(stdscr)){
            mvwin(mainWindow, window::grid::middleY(grid), window::grid::middleX(grid) - 7 );
            mvwin(scoreWindow, getmaxy(stdscr) / 2 - 5, getmaxx(stdscr) - 7 - window::grid::middleX(grid) / 2);

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
            clear();
            refresh();

            mainWindow.deleteWindow();
            scoreWindow.deleteWindow();

            int input;

            do{
                flash();
            }
            while(input = getch(), input != KEY_RESIZE);

            scoreWindow.scoreWindow = ScoreWindow::createWindow();
            mainWindow.gridWindow = window::grid::drawWindow(0, 0, mainWindow.baseGrid, stdscr);

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

#endif //MXPQMFAJFKD_H
