#include "King.h"
#include <cmath>


bool King::isPossible(char x_, char y_) {

    if (!isCorrect(x_, y_)) {
        return false;
    }

    if (board->getMatrix().at(std::pair<char, char>(x_, y_))->getOccupator()->getColor() == this->col) {
        return false;
    } else {
        //TODO capture enemy figure
    }

    //TODO check if there is no check
    return true;
}

bool King::isCorrect(char x_, char y_) {
    std::pair<char, char> current_pos = this->square->getCoords();

    if (abs(current_pos.first - x_) > 1 || abs(current_pos.second - y_) > 1 ) {
        return false;
    }

    return true;
}

King::King(color col_, Board* board_, Square* square_) : Piece (col_, board_, square_) {
    this->type = KING;
}

King::~King() {

}
