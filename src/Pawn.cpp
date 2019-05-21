#include "Pawn.h"

Pawn::Pawn(color col_, Board* board_, Square* square_) : Piece (col_, board_, square_) {
    this->type = PAWN;
}

Pawn::~Pawn() {

}

bool Pawn::isCorrect() {
    return false;
}

bool Pawn::isPossible() {
    return false;
}

bool Pawn::move(char x_, char y_) {
    return false;
}
