#ifndef FAKMCXQMRQ_H
#define FAKMCXQMRQ_H

#include "window.h"

class Layout;

class ScoreWindow final{
public:
    ScoreWindow(const Grid2048& grid, int y = 0, int x = 0):
    baseGrid(grid), scoreWindow(createWindow(y, x))
    {
        wrefresh(scoreWindow);
        update();
    }

    ~ScoreWindow(){
        deleteWindow();
    }

    friend class Layout;

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

    static WINDOW* createWindow(int y = 0, int x = 0) noexcept{
        return newwin(6, 10, y, x);
    }

private:

    void deleteWindow() noexcept{
        if(scoreWindow){
            delwin(scoreWindow);
            scoreWindow = NULL;
        }
    }

    const Grid2048& baseGrid;
    WINDOW* scoreWindow = NULL;
};

#endif //FAKMCXQMRQ_H
