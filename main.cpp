#include "lib2048/2048.h"
#include "window.h"
#include "menu.h"
#include <csignal>
#include <iostream>

int returnOverall;

int main(){



    {
        int result = std::atexit( []() -> void{
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

    static Grid2048 grid;

    grid.generateSquare().generateSquare();

    static Layout layout(grid);

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
        case 27:
            clear();
            refresh();

            mvprintw(getmaxy(stdscr) / 2, getmaxx(stdscr) / 2, "PAUSE");

            while(input = getch(), input != 27);
        case KEY_RESIZE:
            layout.align();
        default:
            //try again
            continue;
        }

        layout.update();
    }
}
