#include "Rook.h"

Rook::Rook(color col_, Board* board_, Square* square_) : Piece (col_, board_, square_) {
    this->type = ROOK;
}

Rook::~Rook() {

}

bool Rook::isCorrect() {
    return false;
}

bool Rook::isPossible() {
    return false;
}

bool Rook::move(char x, char y_) {
    return false;
}
