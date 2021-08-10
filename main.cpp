#include "2048.h"
#include "window.h"
#include <thread>
#include <csignal>

int main(){
    {
        int result = std::atexit( []() -> void{
            //delwin(gameWindow);
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

    drawWindow(grid);
    //gameWindow = newwin(1 + (4 * grid.y), 1 + (7 * grid.x), 2, 2);

    init_color(COLOR_ORANGE, 1000, 600, 0);
    init_color(COLOR_LIGHTBLUE, 500, 1000, 1000);
    init_color(COLOR_DARKBLUE, 0, 0, 600);

    init_pair(P_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(P_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(P_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(P_RED, COLOR_RED, COLOR_BLACK);
    init_pair(P_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(P_ORANGE, COLOR_ORANGE, COLOR_BLACK);
    init_pair(P_LIGHTBLUE, COLOR_LIGHTBLUE, COLOR_BLACK);
    init_pair(P_DARKBLUE, COLOR_DARKBLUE, COLOR_BLACK);

    wrefresh(stdscr);


    drawWindow(grid);

    grid.generateSquare();
    grid.generateSquare();

    mvaddstr(0, 5, "Score:");
    mvprintw(1, 6, "%d", grid.getScore());

    updateWindow(grid);


    int input;
    //main loop
    while(true){
        input = getch();



        mvprintw(1, 1, "%d", input);

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
            moveWindow(grid);
            continue;
        case 10:
            pauseWindow();
        default:
            //try again
            continue;
        }


        mvprintw(1, 6, "%d", grid.getScore());
        updateWindow(grid);
    }

}
