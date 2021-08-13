#ifndef YSJCLSLCX_H
#define YSJCLSLCX_H

#include <ncurses/curses.h>
#include <string>
#include <iostream>
#include <random>
#include <cstring>
#include <exception>

class Grid2048{
public:
    Grid2048(int xIn=4, int yIn=4);

    ~Grid2048();

    int& operator() (int y, int x);

    int operator() (int y, int x) const;

    int operator[] (int oldschool) const;

    Grid2048& generateSquare();

    int* begin();

    int* end();

    void move(int direction){
        bool hasMoved;

        switch (direction) {
        case LEFT:
            hasMoved = moveLeft();
            break;

        case RIGHT:
            hasMoved = moveRight();
            break;

        case UP:
            hasMoved = moveUp();
            break;

        case DOWN:
            hasMoved = moveDown();
            break;

        default:
            throw std::runtime_error("unknown move option");
        }

        generateSquare();
    }

    bool moveRight() noexcept;

    bool moveLeft() noexcept;

    bool moveDown() noexcept;

    bool moveUp() noexcept;

    unsigned int getScore() const;

    const int x, y;

    enum direction{
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

private:
    unsigned int score = 0;
    int* table;
};

#endif // YSJCLSLCX_H
