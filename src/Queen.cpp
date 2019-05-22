#include "Queen.h"


Queen::Queen(color col_, Board* board_, Square* square_) : Piece(col_, board_, square_) {
    this->type = QUEEN;
}

Queen::~Queen() {

}

bool Queen::move(char x_, char y_) {
    return false;
}

bool Queen::isPossible(int x_, int y_) {
    return false;
}

bool Queen::isCorrect(int x_, int y_) {
    return false;
}
