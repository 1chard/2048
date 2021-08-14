#include "2048.h"
#include <ctime>

Grid2048::Grid2048(int xIn, int yIn):
    _x(xIn), _y(yIn) //check if not 9 tiles wide, note it would allow 1*9 grids
{
    if((_x * _y) < 9)
        throw std::runtime_error("not enough space for a game");

    _table = new int[_x * _y];
}

Grid2048::~Grid2048(){
    delete[] _table;
}

int &Grid2048::operator()(int y, int x){
    if( (x < 0) || (y < 0) || (x >= _x) || (y >= _y))
        throw std::runtime_error("Not a value index");

    return _table[(y * _x) + x - 1];
}

int Grid2048::operator()(int y, int x) const{
    if( (x < 0) || (y < 0) || (x >= _x) || (y >= _y))
        throw std::runtime_error("Not a value index");

    return _table[(y * _x) + x - 1];
}

int Grid2048::operator[](int oldschool) const{
    if(oldschool < 0 || oldschool >= (_x * _y) )
        throw std::runtime_error("Not a value index");

    return _table[oldschool];
}

Grid2048& Grid2048::generateSquare(){
    static std::mt19937 mt{ (std::mt19937::result_type)std::time(0)};

    std::uniform_int_distribution<> gridPosition(0, (_x * _y) - 1);
    std::uniform_int_distribution<> chanceOfBe4(0, 99); //1%
    int randNumber = gridPosition(mt);
    int copy = randNumber;

    do{
        randNumber++;
        if(randNumber == _x * _y){
            randNumber = -1;
            continue;
        }

        if(_table[randNumber] == 0){
            _table[randNumber] = ((chanceOfBe4(mt))? 2 : 4);
            return *this;
        }
    }
    while(randNumber != copy);

    throw std::runtime_error("cant write a square, game over");
}

int *Grid2048::begin(){
    return _table;
}

int *Grid2048::end(){
    return (_table + (_x * _y));
}

void Grid2048::move(int direction){
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

bool Grid2048::moveLeft() noexcept{
    try{

        //move everything left
        for(int yi=0; yi < _y; ++yi){
            for(int xi=0; xi < (_x - 1); ++xi){
                if((operator()(yi, xi) == 0) && (operator()(yi, xi + 1) > 0)){
                    operator()(yi, xi) = operator()(yi, xi + 1);
                    operator()(yi, xi + 1) = 0;
                    xi = -1;//note, this move back to beggining of line
                }
            }
        }

        //sum squares
        for(int yi=0; yi < _y; ++yi){
            for(int xi=0; xi < (_x - 1); ++xi){
            if(operator()(yi, xi) == operator()(yi, xi + 1)){
                operator()(yi, xi) *= 2;
                operator()(yi, xi + 1) = 0;
                _score += operator()(yi, xi);

                //move everything left if there is a square sum
                for(int i=(xi + 1); i < (_x - 1); ++i){
                    if((operator()(yi, i) == 0) && (operator()(yi, i + 1) > 0)){
                        operator()(yi, i) = operator()(yi, i + 1);
                        operator()(yi, i + 1) = 0;
                    }
                }
            }
        }
    }

    return true;

    }
    catch(...){
        assert(false && "should never happen");
    }
}

bool Grid2048::moveDown() noexcept{
    try{

    //move down
    for(int xi=0; xi < _x; xi++){
        for(int yi=0; yi < (_y - 1); yi++){
            if((operator()(yi, xi) > 0) && (operator()(yi + 1, xi) == 0)){
                operator()(yi + 1, xi) = operator()(yi, xi);
                operator()(yi, xi) = 0;
                yi = -1;
            }
        }
    }

    for(int xi=0; xi < _y; ++xi){
        for(int yi=(_y - 1); yi > 0; --yi){
            if(operator()(yi, xi) == operator()(yi - 1, xi)){
                operator()(yi, xi) *= 2;
                operator()(yi - 1, xi) = 0;
                _score += operator()(yi, xi);
                //move everything down if there is a square sum, runs inverse
                for(int i=(yi - 1); i >= 0; --i){
                    if((operator()(i, xi) > 0) && (operator()(i + 1, xi) == 0)){
                        operator()(i + 1, xi) = operator()(i, xi);
                        operator()(i, xi) = 0;
                    }
                }
            }
        }
    }

    return true;

    }
    catch(...){
        assert(false && "should never happen");
    }
}

bool Grid2048::moveRight() noexcept{
    try{

    //move everything right
    for(int yi=0; yi < _y; ++yi){
        for(int xi=0; xi < (_x - 1); ++xi){
            if((operator()(yi, xi) > 0) && (operator()(yi, xi + 1) == 0)){
                operator()(yi, xi + 1) = operator()(yi, xi);
                operator()(yi, xi) = 0;
                xi = -1; //note, this move back to beggining of line
            }
        }
    }

    //sum squares
    for(int yi=0; yi < _y; ++yi){
        for(int xi=(_x - 1); xi > 0; --xi){
            if(operator()(yi, xi) == operator()(yi, xi - 1)){
                operator()(yi, xi) *= 2;
                operator()(yi, xi - 1) = 0;
                _score += operator()(yi, xi);
                //move everything right if there is a square sum, runs inverse
                for(int i=(xi - 1); i >= 0; --i){
                    if((operator()(yi, i) > 0) && (operator()(yi, i + 1) == 0)){
                        operator()(yi, i + 1) = operator()(yi, i);
                        operator()(yi, i) = 0;
                    }
                }
            }
        }
    }

    return true;

    }
    catch(...){
        assert(false && "should never happen");
    }
}

bool Grid2048::moveUp() noexcept{
    try{

    //move everything up
    for(int xi=0; xi < _x; ++xi){
        for(int yi=0; yi < (_y - 1); ++yi){
            if((operator()(yi + 1, xi) > 0) && (operator()(yi, xi) == 0)){
                operator()(yi, xi) = operator()(yi + 1, xi);
                operator()(yi + 1, xi) = 0;
                yi = -1; //note, this move back to beggining of line
            }
        }
    }

    //sum squares
    for(int xi=0; xi < _x; ++xi){
        for(int yi=0; yi < (_y - 1); ++yi){
            if(operator()(yi, xi) == operator()(yi + 1, xi)){
                operator()(yi, xi) *= 2;
                operator()(yi + 1, xi) = 0;
                _score += operator()(yi, xi);
                //move everything up if there is a square sum
                for(int i=(yi + 1); i < (_y - 1); ++i){
                    if((operator()(i + 1, xi) > 0) && (operator()(i, xi) == 0)){
                        operator()(i, xi) = operator()(i + 1, xi);
                        operator()(i + 1, xi) = 0;
                    }
                }
            }
        }
    }

    return true;

    }
    catch(...){
        assert(false && "should never happen");
    }
}

unsigned int Grid2048::getScore() const{
    return _score;
}
