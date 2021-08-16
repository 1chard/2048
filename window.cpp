#include "window.h"
#define NULL __null //idk why qt creator is saying NULL is undefined

int returnOverall = 0;

void drawGridBorder(WINDOW*, const Grid2048&);
void drawValues(WINDOW*, const Grid2048&);

void updateWindow(WINDOW* window, const Grid2048& grid){
    drawValues(window, grid);
    wrefresh(window);
}

WINDOW* drawWindow(const Grid2048& grid){
    WINDOW* toReturn;
    //    delwin(gameWindow); //safe
    toReturn = newwin(1 + (4 * grid.y), 1 + (7 * grid.x), 2, (getmaxx(stdscr) - (7 * grid.x))/ 2);
    drawGridBorder(toReturn, grid);
    updateWindow(toReturn, grid);

    return toReturn;
}

void moveWindow(WINDOW* window, const Grid2048& grid){
    mvwin(window, 2, (getmaxx(stdscr) - (7 * grid.x))/ 2);

    wclear(window);
    wclear(stdscr);

    wrefresh(stdscr);

    drawGridBorder(window, grid);
    drawValues(window, grid);
    wrefresh(window);
}

void drawGridBorder(WINDOW* window, const Grid2048& gridTarget){
    wattron(window, COLOR_PAIR(P_BLUE) | A_BOLD);
    //first create left border
    {

        mvwaddch(window, 0, 0, ACS_ULCORNER);

        int i=0;
        for(; i < (4 * gridTarget.y); ++i){
            if(i % 4 != 3)
                mvwaddch(window, i + 1, 0, ACS_VLINE);
            else
                mvwaddch(window, i + 1, 0, ACS_LTEE);
        }

        mvwaddch(window, i, 0, ACS_LLCORNER);
    }

    {

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

    wattroff(window, COLOR_PAIR(P_BLUE) | A_BOLD);
}

void clearValue(WINDOW* window, int y, int x){
    mvwprintw(window, 2 + (y * 4), 2 + (x * 7), "    ");
}

void drawValues(WINDOW* window, const Grid2048& grid){
    for(int y=0; y < grid.y; ++y){
        for(int x=0; x < grid.x; ++x){
            clearValue(window, y, x);

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
                wattron(window, COLOR_PAIR(P_BLUE) | A_BOLD);
                mvwprintw(window, 2 + (y * 4), 2 + (x * 7), "%d", grid(y, x));
                wattroff(window, COLOR_PAIR(P_BLUE) | A_BOLD);
                break;
            }
        }
    }
}
