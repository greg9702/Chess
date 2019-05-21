//
// Created by greg9702 on 5/21/19.
//

#include <Square.h>

Square::Square(char x_, char y_, Piece* piece_) {
    /**
     * Constructor
     * @param x cordinate of board square
     * @param y corinate of board square
     * @param Piece object - if piece stand on square, nullptr otherwise
     */

    //TODO check crectness of x and y asserts

    if (piece_ != nullptr) {
        this->occupator = piece_;
    }

    this->x = x_;
    this->y = y_;

}

Piece* Square::getOccupator() {
    /**
     * Return pointer to occupator Piece object
     * @return pointer to piece object if piece stand on this square nullptr otherwise
     */

    if (this->occupator != nullptr) {
        return this->occupator;
    }
    return nullptr;
}

void Square::setOccupator(Piece* occupator_) {
    /**
     * Set occupatro
     * @param pointer to occupator obj //TODO what about nullptr
     */
    this->occupator = occupator_;
}

Square::~Square() {
    /**
     * Destructor
     */
}

