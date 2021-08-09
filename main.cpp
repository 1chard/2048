#include "2048.h"
#include <thread>
#include <csignal>

int returnOverall = 0;
Grid2048 grid;
WINDOW* gameWindow;

void createGridBorder(WINDOW*, const Grid2048&);
void printValuesOnGrid(WINDOW*, const Grid2048&);
enum ColorsPair{
    P_RED = 1,
    P_GREEN,
    P_BLUE,
    P_MAGENTA,
    P_YELLOW,
    P_ORANGE,
    P_LIGHTBLUE,
    P_DARKBLUE
};
enum ColorsExtra{
    COLOR_ORANGE = 127,
    COLOR_LIGHTBLUE,
    COLOR_DARKBLUE
};

int main(){
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

    gameWindow = newwin(1 + (4 * grid.y), 2 + (7 * grid.x), 2, 2);

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

    wattron(gameWindow, COLOR_PAIR(P_BLUE) | A_BOLD);
    createGridBorder(gameWindow, grid);
    wattroff(gameWindow, COLOR_PAIR(P_BLUE) | A_BOLD);

    grid.createGridItem();
    grid.createGridItem();

    mvaddstr(0, 5, "Score:");
    mvprintw(1, 6, "%d", grid.getScore());

    printValuesOnGrid(gameWindow, grid);
    wrefresh(gameWindow);

    int input;

GOTOwaitForCorrectOutput:;

    //main loop
    while(true){
        input = getch();

        switch (input) {
        case KEY_LEFT:
            grid.moveLeft();
            break;
        case KEY_RIGHT:
            grid.moveRight();
            break;
        case KEY_UP:
            grid.moveUp();
            break;
        case KEY_DOWN:
            grid.moveDown();
            break;
        default:
            goto GOTOwaitForCorrectOutput;
        }


        mvprintw(1, 6, "%d", grid.getScore());
        grid.createGridItem();

        printValuesOnGrid(gameWindow, grid);

        //refresh();
        wrefresh(gameWindow);
    }

}

void createGridBorder(WINDOW* window, const Grid2048& gridTarget){
    //first create left border
    {
        waddch(window, ACS_ULCORNER);

        int i=0;
        for(; i < (4 * gridTarget.y); ++i){
            if(i % 4 != 3)
                mvwaddch(window, i + 1, 0, ACS_VLINE);
            else
                mvwaddch(window, i + 1, 0, ACS_LTEE);
        }

        mvwaddch(window, i, 0, ACS_LLCORNER);
    }

    //then upper border
    {
        //for(int Xi=0; Xi < gridTarget.x; Xi++)
        //mvwaddstr(window, 0, 1 + (7 * Xi), "------*");

        int i=0;
        for(; i < (7 * gridTarget.x); i++){
            if(i % 7 != 6)
                mvwaddch(window, 0, i + 1, ACS_HLINE);
            else
                mvwaddch(window, 0, i + 1, ACS_TTEE);
        }

        mvwaddch(window, 0, i, ACS_URCORNER);
    }

    //then the rest
    {
        int Yi=0, Xi=0;

        for(; Yi < gridTarget.y; Yi++){
            for(; Xi < gridTarget.x; Xi++){
                mvwaddch(window, 1 + (4 * Yi), 7 + (7 * Xi), ACS_VLINE);
                mvwaddch(window, 2 + (4 * Yi), 7 + (7 * Xi), ACS_VLINE);
                mvwaddch(window, 3 + (4 * Yi), 7 + (7 * Xi), ACS_VLINE);

                for(int i=0; i < 6; i++)
                    mvwaddch(window, 4 + (4 * Yi), 1 + (7 * Xi) + i, ACS_HLINE);

                mvwaddch(window, 4 + (4 * Yi), 7 + (7 * Xi), ACS_PLUS);

            }

            mvwaddch(window, 4 + (4 * Yi), (Xi * 7), ACS_RTEE);
            Xi = 0;
        }

        for(Xi = 1; Xi < gridTarget.x; Xi++){
            mvwaddch(window, (4 * Yi), (Xi * 7), ACS_BTEE);
        }

        mvwaddch(window, (4 * Yi), (Xi * 7), ACS_LRCORNER);
    }
}

void clearGridPosition(WINDOW* window, int y, int x){
    mvwprintw(window, 2 + (y * 4), 2 + (x * 7), "    ");
}

void printValuesOnGrid(WINDOW* window, const Grid2048& grid){
    for(int y=0; y < grid.y; ++y){
        for(int x=0; x < grid.x; ++x){
            clearGridPosition(window, y, x);

            switch (grid(y, x)) {
            case 0: //just break
                break;
            case 2:
                mvwprintw(window, 2 + (y * 4), 3 + (x * 7), "2");
                break;
            case 4:
                wattron(window, COLOR_PAIR(P_YELLOW));
                mvwprintw(window, 2 + (y * 4), 3 + (x * 7), "4");
                wattroff(window, COLOR_PAIR(P_YELLOW));
                break;
            case 8:
                wattron(window, COLOR_PAIR(P_ORANGE));
                mvwprintw(window, 2 + (y * 4), 3 + (x * 7), "8");
                wattroff(window, COLOR_PAIR(P_ORANGE));
                break;
            case 16:
                wattron(window, COLOR_PAIR(P_RED));
                mvwprintw(window, 2 + (y * 4), 3 + (x * 7), "16");
                wattroff(window, COLOR_PAIR(P_RED));
                break;
            case 32:
                wattron(window, COLOR_PAIR(P_MAGENTA));
                mvwprintw(window, 2 + (y * 4), 3 + (x * 7), "32");
                wattroff(window, COLOR_PAIR(P_MAGENTA));
                break;
            case 64:
                wattron(window, COLOR_PAIR(P_DARKBLUE));
                mvwprintw(window, 2 + (y * 4), 3 + (x * 7), "64");
                wattroff(window, COLOR_PAIR(P_DARKBLUE));
                break;
            case 128:
                wattron(window, COLOR_PAIR(P_LIGHTBLUE));
                mvwprintw(window, 2 + (y * 4), 2 + (x * 7), "128");
                wattroff(window, COLOR_PAIR(P_LIGHTBLUE));
                break;
            case 256:
                wattron(window, COLOR_PAIR(P_YELLOW) | A_BOLD);
                mvwprintw(window, 2 + (y * 4), 2 + (x * 7), "256");
                wattroff(window, COLOR_PAIR(P_YELLOW) | A_BOLD);
                break;
            case 512:
                wattron(window, COLOR_PAIR(P_ORANGE) | A_BOLD);
                mvwprintw(window, 2 + (y * 4), 2 + (x * 7), "512");
                wattroff(window, COLOR_PAIR(P_ORANGE) | A_BOLD);
                break;
            case 1024:
                wattron(window, COLOR_PAIR(P_RED) | A_BOLD);
                mvwprintw(window, 2 + (y * 4), 2 + (x * 7), "1024");
                wattroff(window, COLOR_PAIR(P_RED) | A_BOLD);
                break;
            case 2048:
                wattron(window, COLOR_PAIR(P_MAGENTA) | A_BOLD);
                mvwaddch(window, 2 + (y * 4), 2 + (x * 7), '2');
                wattroff(window, COLOR_PAIR(P_MAGENTA));

                wattron(window, COLOR_PAIR(P_LIGHTBLUE) | A_BOLD);
                mvwaddch(window, 2 + (y * 4), 3 + (x * 7), '0');
                wattroff(window, COLOR_PAIR(P_LIGHTBLUE));

                wattron(window, COLOR_PAIR(P_GREEN) | A_BOLD);
                mvwaddch(window, 2 + (y * 4), 4 + (x * 7), '4');
                wattroff(window, COLOR_PAIR(P_GREEN));

                wattron(window, COLOR_PAIR(P_ORANGE) | A_BOLD);
                mvwaddch(window, 2 + (y * 4), 5 + (x * 7), '8');
                wattroff(window, COLOR_PAIR(P_ORANGE) | A_BOLD);

                break;
            default:

                break;
            }
        }
    }
}
