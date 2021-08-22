#ifndef LAMCSARQNS_H
#define LAMCSARQNS_H

#include <string>
#include <curses.h>

struct MenuItem{
    int y, x;
    std::string name;
    void* (*action)(...);
};

class Menu{
public:
    Menu(WINDOW* window = stdscr){

    }

private:
    int positionY, positionX;
    int y, x;
};

#endif // LAMCSARQNS_H
