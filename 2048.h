#ifndef YSJCLSLCX_H
#define YSJCLSLCX_H

#include <random>
#include <stdexcept>
#include <cassert>

class Grid2048{
public:
    Grid2048(int xIn=4, int yIn=4);

    ~Grid2048();

    int& operator() (int, int);

    int operator() (int, int) const;

    int operator[] (int oldschool) const;

    Grid2048& generateSquare();

    int* begin();

    int* end();

    void move(int direction);

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
    unsigned int _score = 0;
    int* _table;
};

#endif // YSJCLSLCX_H
