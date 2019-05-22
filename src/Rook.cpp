#include "Rook.h"
#include "Square.h"
#include "Board.h"

Rook::Rook(color col_, Board* board_, Square* square_) : Piece (col_, board_, square_) {
    this->type = ROOK;
}

Rook::~Rook() {

}

bool Rook::isCorrect(char x_, char y_) {
    return ((x_ == this->square->getCoords().first) != (y_ == this->square->getCoords().second));
}

bool Rook::isPossible(char x_, char y_) {
    if (!this->isCorrect(x_,y_))
        return false;
    if (this->board->getPieceByCoord(x_,y_) != nullptr && this->board->getPieceByCoord(x_,y_)->getColor() == this->col)
       return false;
    //horizontal movement
    if (x_ == this->square->getCoords().first){
        std::cout << "XD";
        char target = this->square->getCoords().second;
        // beg, fin - range of squares to check if there is something
        char beg = target > y_ ? y_+1 : target+1;
        char fin = target > y_ ? target-1 : beg-1;
        for (char i = beg; i<fin; ++i){
            if (this->board->getPieceByCoord(x_,i) != nullptr)
                return false;
        }
    }
    //vertical movement
    if (y_ == this->square->getCoords().second){
        char target = this->square->getCoords().first;
        char beg = target > y_ ? y_+1 : target+1;
        char fin = target > y_ ? target-1 : beg-1;
        for (char i = beg; i<fin; ++i){
            if (this->board->getPieceByCoord(i,y_) != nullptr)
                return false;
        }
    }
    //vertical moving
    return true;
}