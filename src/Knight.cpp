#include <cmath>
#include <iostream>
#include "Knight.h"
#include "Square.h"
#include "Board.h"


Knight::Knight(color col_, Board* board_, Square* square_) : Piece(col_, board_, square_){
    this->type = KNIGHT;
}

Knight::~Knight() {

}

bool Knight::isCorrect(char x_, char y_) {
    char my_x = this->square->getCoords().first;
    char my_y = this->square->getCoords().second;

    if (abs(my_x - x_) == 2 && abs(my_y - y_) == 1)
        return true;
    if (abs(my_x - x_) == 1 && abs(my_y - y_) == 2)
        return true;
    return false;
}

bool Knight::isPossible(char x_, char y_) {
    if (!isCorrect(x_,y_))
        return false;
    std::cout << "isCorrect() passed.\n";
    if (this->board->getPieceByCoord(x_,y_) != nullptr && this->board->getPieceByCoord(x_,y_)->getColor() == this->col)
        return false;
    return true;
}
