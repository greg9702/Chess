#include <King.h>

bool King::isPossible(char x_, char y_) {
    return false;
}

bool King::isCorrect(char x_, char y_) {
    return false;
}

King::King(color col_, Board* board_, Square* square_) : Piece (col_, board_, square_) {
    this->type = KING;
}

King::~King() {

}
