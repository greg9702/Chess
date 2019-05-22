#include "Knight.h"


Knight::Knight(color col_, Board* board_, Square* square_) : Piece(col_, board_, square_){
    this->type = KNIGHT;
}

Knight::~Knight() {

}

bool Knight::isPossible(int x_, int y_) {
    return false;
}

bool Knight::isCorrect(int x_, int y_) {
    return false;
}

bool Knight::move(char x_, char y_) {
    return false;
}
