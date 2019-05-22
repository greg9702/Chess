#include "Rook.h"

Rook::Rook(color col_, Board* board_, Square* square_) : Piece (col_, board_, square_) {
    this->type = ROOK;
}

Rook::~Rook() {

}

bool Rook::isCorrect(char x_, char y_) {
    return false;
}

bool Rook::isPossible(char x_, char y_) {
    return false;
}

bool Rook::move(char x_, char y_) {
    if (!isPossible(x_,y_))
        return false;
    //board->
    return true;
}
