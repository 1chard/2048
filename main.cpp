#include "2048.h"
#include "window.h"
#include <csignal>
#include <iostream>

int main(){
    static Grid2048 grid;
    static WINDOW* gameWindow;

    {
        int result = std::atexit( []() -> void{
            delwin(gameWindow);
            endwin();
        });

        if(result){
            std::cout << "Error: internal error.\n";
            std::terminate();
        }
    }

    std::signal(SIGINT, [](int) -> void{
        std::exit(returnOverall);
    });

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, true);
    start_color();

    init_pair(P_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(P_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(P_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(P_RED, COLOR_RED, COLOR_BLACK);
    init_pair(P_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(P_CYAN, COLOR_CYAN, COLOR_BLACK);

    wrefresh(stdscr);

    grid.generateSquare().generateSquare();

    mvaddstr(0, 5, "Score:");
    mvprintw(1, 6, "%d", grid.getScore());

    gameWindow = drawWindow(grid);

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
            moveWindow(&gameWindow, grid, &input);
            goto redoWithoutGetch;
        default:
            //try again
            continue;
        }

        mvprintw(1, 6, "%d", grid.getScore());
        updateWindow(gameWindow, grid);
    }
}
