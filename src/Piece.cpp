#include <Piece.h>

Piece::Piece(color col_, Board* board_, Square* square_) {
    /**
     * Constructor
     */
     this->board = board_;
     this->square = square_;
     this->col = col;
}

Piece::~Piece() {
    /**
    * Destructor
    */
}

