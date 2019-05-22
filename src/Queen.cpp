#include "Queen.h"


Queen::Queen(color col_, Board* board_, Square* square_) : Piece(col_, board_, square_) {
    this->type = QUEEN;
}

Queen::~Queen() {

}


bool Queen::isPossible(char x_, char y_) {
    return false;
}

bool Queen::isCorrect(char x_, char y_) {
    return false;
}
