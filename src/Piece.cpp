#include "Piece.h"
#include "Square.h"

Piece::Piece(color col_, std::shared_ptr<Board> & board_, std::shared_ptr<Square> & square_) {
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

