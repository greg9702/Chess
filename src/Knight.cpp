#include "Knight.h"


Knight::Knight(color col_, Board* board_, Square* square_) : Piece(col_, board_, square_){
    this->type = KNIGHT;
}

Knight::~Knight() {

}

bool Knight::isPossible(char x_, char y__) {
    return false;
}

bool Knight::isCorrect(char x_, char y_) {
    return false;
}

bool Knight::move(char x_, char y_) {
    return false;
}
