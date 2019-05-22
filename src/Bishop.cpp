#include "Bishop.h"


Bishop::Bishop(color col_, Board* board_, Square* square_) : Piece (col_, board_, square_) {
    this->type = BISHOP;
}

Bishop::~Bishop() {

}

bool Bishop::isCorrect(int x_, int y_) {
    return false;
}

bool Bishop::isPossible(int x_, int y_) {
    return false;
}

bool Bishop::move(char x_, char y_) {
    return false;
}
