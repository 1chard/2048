#ifndef YSJCLSLCX_H
#define YSJCLSLCX_H

#include <ncurses/curses.h>
#include <string>
#include <iostream>
#include <random>

template<typename T>
T pow(T initialNumber, unsigned int quantity){
    T toReturn = 1;

    for(unsigned int i = 1; i <= quantity; ++i)
        toReturn *= initialNumber;

    return toReturn;
}

class Grid2048{
public:
    Grid2048(int xIn=4, int yIn=4);

    ~Grid2048();

    int& operator() (int y, int x);

    int operator() (int y, int x) const;

    int operator[] (int oldschool) const;

    Grid2048& createGridItem();

    int* begin();

    int* end();

    void moveRight();

    void moveLeft();

    void moveDown();

    void moveUp();

    unsigned int getScore() const;

    const int x, y;

private:
    unsigned int score;
    int* table;
};

#endif // YSJCLSLCX_H
