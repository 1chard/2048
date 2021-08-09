#include "2048.h"

Grid2048::Grid2048(int xIn, int yIn):
    x(xIn), y(yIn) //check if not 9 tiles wide, note it would allow 1*9 grids
{
    if((x * y) < 9)
        throw std::runtime_error("not enough space for a game");

    table = new int[x * y];
}

Grid2048::~Grid2048(){
    try{
        delete table;
    }
    catch(...){
        std::cout << 122;
    }
}

int &Grid2048::operator()(int y, int x){
    if( (x < 0) || (y < 0) || (x >= this->x) || (y >= this->y))
        throw std::runtime_error("Not a value index");

    return table[(y * this->x) + x - 1];
}

int Grid2048::operator()(int y, int x) const{
    if( (x < 0) || (y < 0) || (x >= this->x) || (y >= this->y))
        throw std::runtime_error("Not a value index");

    return table[(y * this->x) + x - 1];
}

int Grid2048::operator[](int oldschool) const{
    if(oldschool < 0 || oldschool >= (x * y) )
        throw std::runtime_error("Not a value index");

    return table[oldschool];
}

Grid2048 &Grid2048::createGridItem(){
    static std::random_device rd;
    static std::mt19937 mt{rd()};

    std::uniform_int_distribution<> gridPosition(0, (x * y) - 1);
    std::uniform_int_distribution<> chanceOfBe4(0, 99); //1%

    int randNumber = gridPosition(mt);
    if(table[randNumber] > 0){
        int copy = randNumber;

        do{
            randNumber++;
            if(randNumber == x * y)
                randNumber = -1;

            if(table[randNumber] == 0){
                table[randNumber] = ((chanceOfBe4(mt))? 2 : 4);
                return *this;
            }

        }
        while(randNumber != copy);

        throw std::runtime_error("cant write a square, game over");
    }
    else
        table[randNumber] = ((chanceOfBe4(mt))? 2 : 4);

    return *this;
}

int *Grid2048::begin(){
    return table;
}

int *Grid2048::end(){
    return (table + (x * y));
}

void Grid2048::moveLeft(){

    //move everything left
    for(int yi=0; yi < y; ++yi){
        for(int xi=1; xi < x; ++xi){
            if((operator()(yi, xi) > 0) && (operator()(yi, xi - 1) == 0)){
                operator()(yi, xi - 1) = operator()(yi, xi);
                operator()(yi, xi) = 0;
                xi = 0; //note, this move back to beggining of line
            }
        }
    }

    //sum squares
    for(int yi=0; yi < y; ++yi){
        for(int xi=0; xi < (x - 1); ++xi){
            if(operator()(yi, xi) == operator()(yi, xi + 1)){
                operator()(yi, xi) *= 2;
                operator()(yi, xi + 1) = 0;
                score += operator()(yi, xi);
                xi++; //this is an optization


            }
        }
    }

    //move everything left again
    for(int yi=0; yi < y; ++yi){
        for(int xi=1; xi < x; ++xi){
            if((operator()(yi, xi) > 0) && (operator()(yi, xi - 1) == 0)){
                operator()(yi, xi - 1) = operator()(yi, xi);
                operator()(yi, xi) = 0;
                xi = 1; //note, this move back to beggining of line
            }
        }
    }
}

void Grid2048::moveDown(){
    //move down
    for(int xi=0; xi < x; xi++){
        for(int yi=1; yi < y; yi++){
            if((operator()(yi - 1, xi) > 0) && (operator()(yi, xi) == 0)){
                operator()(yi, xi) = operator()(yi - 1, xi);
                operator()(yi - 1, xi) = 0;
                yi = 0;
            }
        }
    }

    for(int xi=0; xi < y; ++xi){
        for(int yi=(y - 1); yi > 0; --yi){
            if(operator()(yi, xi) == operator()(yi - 1, xi)){
                operator()(yi, xi) *= 2;
                operator()(yi - 1, xi) = 0;
                score += operator()(yi, xi);
            }
        }
    }

    for(int xi=0; xi < x; xi++){
        for(int yi=1; yi < y; yi++){
            if((operator()(yi - 1, xi) > 0) && (operator()(yi, xi) == 0)){
                operator()(yi, xi) = operator()(yi - 1, xi);
                operator()(yi - 1, xi) = 0;
                yi = 0;
            }
        }
    }
}

void Grid2048::moveRight(){
    //move everything right
    for(int yi=0; yi < y; ++yi){
        for(int xi=0; xi < (x - 1); ++xi){
            if((operator()(yi, xi) > 0) && (operator()(yi, xi + 1) == 0)){
                operator()(yi, xi + 1) = operator()(yi, xi);
                operator()(yi, xi) = 0;
                xi = -1; //note, this move back to beggining of line
            }
        }
    }

    //sum squares
    for(int yi=0; yi < y; ++yi){
        for(int xi=(x - 1); xi > 0; --xi){
            if(operator()(yi, xi) == operator()(yi, xi - 1)){
                operator()(yi, xi) *= 2;
                operator()(yi, xi - 1) = 0;
                score += operator()(yi, xi);
            }
        }
    }


    //move everything right again
    for(int yi=0; yi < y; ++yi){
        for(int xi=0; xi < (x - 1); ++xi){
            if((operator()(yi, xi) > 0) && (operator()(yi, xi + 1) == 0)){
                operator()(yi, xi + 1) = operator()(yi, xi);
                operator()(yi, xi) = 0;
                xi = -1; //note, this move back to beggining of line
            }
        }
    }
}

void Grid2048::moveUp(){

    //move everything up
    for(int xi=0; xi < x; ++xi){
        for(int yi=1; yi < y; ++yi){
            if((operator()(yi, xi) > 0) && (operator()(yi - 1, xi) == 0)){
                operator()(yi - 1, xi) = operator()(yi, xi);
                operator()(yi, xi) = 0;
                yi = 0; //note, this move back to beggining of line
            }
        }
    }

    //sum squares
    for(int xi=0; xi < x; ++xi){
        for(int yi=0; yi < (y - 1); ++yi){
            if(operator()(yi, xi) == operator()(yi + 1, xi)){
                operator()(yi, xi) *= 2;
                operator()(yi + 1, xi) = 0;
                score += operator()(yi, xi);
                yi++; //this is an optization

            }
        }
    }

    for(int xi=0; xi < x; ++xi){
        for(int yi=1; yi < y; ++yi){
            if((operator()(yi, xi) > 0) && (operator()(yi - 1, xi) == 0)){
                operator()(yi - 1, xi) = operator()(yi, xi);
                operator()(yi, xi) = 0;
                xi = 0; //note, this move back to beggining of line
            }
        }
    }
}

unsigned int Grid2048::getScore() const{
    return score;
}
