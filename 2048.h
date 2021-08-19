#ifndef YSJCLSLCX_H
#define YSJCLSLCX_H

#include <random>
#include <stdexcept>
#include <cassert>

class Grid2048{
public:
    Grid2048(int xIn=4, int yIn=4);

    Grid2048(const Grid2048&);

    Grid2048& operator= (const Grid2048&);

    ~Grid2048();

    int& operator() (int, int);

    int operator() (int, int) const;

    Grid2048& generateSquare();

    int* begin();

    int* end();

    int* begin() const;

    int* end() const;

    void move(int direction) noexcept;

    bool moveRight() noexcept;

    bool moveLeft() noexcept;

    bool moveDown() noexcept;

    bool moveUp() noexcept;

    unsigned int getScore() const;

    const int x, y;

    enum direction{
        LEFT = 1,
        RIGHT,
        UP,
        DOWN
    };

private:
    bool isLegalToMove(direction targetDirection) noexcept;

    unsigned int _score = 0;
    int* _table;
};

#endif // YSJCLSLCX_H
