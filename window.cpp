#include "window.h"

namespace window{

    void attrmvwaddstr(attr_t attr, WINDOW* window, int y, int x, const char* ptr){
        wattr_on(window, attr, NULL);
        mvwaddstr(window, y, x, ptr);
        wattr_off(window, attr, NULL);
    }

    void moveWindow(WINDOW** windowPtr, int beginY, int beginX){
        if( beginY + getmaxy(*windowPtr) > getmaxy(stdscr) || beginX + getmaxx(*windowPtr) > getmaxx(stdscr))
            throw std::runtime_error("moveWindow would move window outside stdscr");
        else
            mvwin(*windowPtr, beginX, beginY);
    }

    namespace grid{
        void drawGridBorder(WINDOW*, const Grid2048&);
        void drawValues(WINDOW*, const Grid2048&);

        void redraw(WINDOW* window, const Grid2048& grid){
            drawGridBorder(window, grid);
            drawValues(window, grid);
            update(window, grid);
        }

        int middleX(const Grid2048& grid){
            return (getmaxx(stdscr) - (7 * grid.x))/ 2;
        }

        int middleY(const Grid2048& grid){
            return (getmaxy(stdscr) - (4 * grid.x))/ 2;
        }

        void update(WINDOW* window, const Grid2048& grid){
            drawValues(window, grid);
            wrefresh(window);
        }

        WINDOW* drawWindow(int y, int x, const Grid2048& grid, WINDOW* baseWindow){
            WINDOW* toReturn;
            toReturn = newwin(1 + (4 * grid.y), 1 + (7 * grid.x), y, x);
            drawGridBorder(toReturn, grid);
            update(toReturn, grid);

            return toReturn;
        }

        void align(WINDOW** windowPtr, const Grid2048& grid, int* inputPtr){
            if(inputPtr == NULL)
                throw std::runtime_error("null pointer as third argument");

            do{
                if( (4 * grid.y + 4) < getmaxy(stdscr) && (7 * grid.x + 4) < getmaxx(stdscr) ){
                    if(*windowPtr != NULL)
                        mvwin(*windowPtr, middleY(grid), middleX(grid));
                    else
                        *windowPtr = drawWindow(middleY(grid), middleX(grid), grid);
                }
                else{
                    if(*windowPtr == NULL){
                        clear();
                        printw("Please resize window with at least %d wide long and %d height long", (7 * grid.x + 4) + 1, (4 * grid.y + 4) + 1);
                    }
                    else{
                        clear();
                        printw("Please resize window with at least %d wide long and %d height long", (7 * grid.x + 4) + 1, (4 * grid.y + 4) + 1);
                        delwin(*windowPtr);
                        *windowPtr = NULL;
                    }
                    continue;
                }

                wclear(*windowPtr);
                wclear(stdscr);

                wrefresh(stdscr);

                drawGridBorder(*windowPtr, grid);
                drawValues(*windowPtr, grid);
                wrefresh(*windowPtr);
            }
            while(*inputPtr = getch(), *inputPtr == KEY_RESIZE);

        }

        void drawGridBorder(WINDOW* window, const Grid2048& gridTarget){
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
                        mvwaddstr(window, 2 + (y * 4), 3 + (x * 7), "2");
                        break;
                    case 4:
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_YELLOW), window, 2 + (y * 4), 3 + (x * 7), "4");
                        break;
                    case 8:
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_RED), window, 2 + (y * 4), 3 + (x * 7), "8");
                        break;
                    case 16:
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_MAGENTA), window, 2 + (y * 4), 3 + (x * 7), "16");
                        break;
                    case 32:
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_BLUE), window, 2 + (y * 4), 3 + (x * 7), "32");
                        break;
                    case 64:
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_CYAN), window, 2 + (y * 4), 3 + (x * 7), "64");
                        break;
                    case 128:
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_GREEN), window, 2 + (y * 4), 2 + (x * 7), "128");
                        break;
                    case 256:
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_YELLOW) | A_BOLD , window, 2 + (y * 4), 2 + (x * 7), "256");
                        break;
                    case 512:
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_RED) | A_BOLD , window, 2 + (y * 4), 2 + (x * 7), "512");
                        break;
                    case 1024:
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_MAGENTA) | A_BOLD , window, 2 + (y * 4), 2 + (x * 7), "1024");
                        break;
                    case 2048:
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_RED) | A_BOLD , window, 2 + (y * 4), 2 + (x * 7), "2");
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_MAGENTA) | A_BOLD , window, 2 + (y * 4), 3 + (x * 7), "0");
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_CYAN) | A_BOLD , window, 2 + (y * 4), 4 + (x * 7), "4");
                        attrmvwaddstr(COLOR_PAIR(WindowGrid::P_GREEN) | A_BOLD , window, 2 + (y * 4), 5 + (x * 7), "8");
                        break;
                    default:
                        wattron(window, COLOR_PAIR(WindowGrid::P_CYAN) | A_BOLD);
                        mvwprintw(window, 2 + (y * 4), 2 + (x * 7), "%d", grid(y, x));
                        wattroff(window, COLOR_PAIR(WindowGrid::P_CYAN) | A_BOLD);
                        break;
                    }
                }
            }
        }

    }
}
