#include "lib2048/2048.h"
#include "window.h"
#include <csignal>
#include <iostream>

int returnOverall;

int main(){

    static Grid2048 grid;

    {
        int result = std::atexit( []() -> void{
            //delwin(gameWindow);
            endwin();
        });

        if(result){
            std::cout << "Error: internal error.\n";
            std::abort();
        }
    }

    std::signal(SIGINT, [](int) -> void{
        std::exit(returnOverall);
    });

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nonl();
    keypad(stdscr, true);
    start_color();
    set_escdelay(100);

    refresh();
    WindowGrid::init_colors();

    grid.generateSquare().generateSquare();
    static WindowGrid gameWindow(grid);

    mvaddstr(0, 5, "Score:");
    mvprintw(1, 6, "%d", grid.getScore());


    int input;
    //main loop
    while(true){
        if(grid.hasLost()){
            mvaddstr(0, 0, "GAME OVER, PRESS TO EXIT");

            getch();

            return 0;
        }

        input = getch();

redoWithoutGetch:;

        switch (input) {
        case KEY_LEFT:
            grid.move(Grid2048::LEFT);
            break;
        case KEY_RIGHT:
            grid.move(Grid2048::RIGHT);
            break;
        case KEY_UP:
            grid.move(Grid2048::UP);
            break;
        case KEY_DOWN:
            grid.move(Grid2048::DOWN);
            break;
        case KEY_RESIZE:
            gameWindow.move(&input);
            goto redoWithoutGetch;
        case 27:
            clear();
            refresh();
            mvprintw(getmaxy(stdscr) / 2, getmaxx(stdscr) / 2, "PAUSE");

            while(input = getch(), input != 27);

            gameWindow.move(&input);
            goto redoWithoutGetch;

        default:
            //try again
            continue;
        }

        mvprintw(1, 6, "%d", grid.getScore());
        updateWindow(gameWindow, grid);
    }
}
