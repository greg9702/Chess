#include "Piece.h"
#include "Square.h"

Piece::Piece(color col_, Board* board_, Square* square_) {
    /**
     * Constructor
     */

     this->board = board_;
     this->square = square_;
     this->col = col_;
     this->square->setOccupator(this);
}

Piece::~Piece() {
    /**
    * Destructor
    */
}

color Piece::getColor() {
    return this->col;
}

Piece_type Piece::getType() {
    return this->type;
}

