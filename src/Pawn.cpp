#include "Pawn.h"

Pawn::Pawn(color col_, Board* board_, Square* square_) : Piece (col_, board_, square_) {
    this->type = PAWN;
    this->first_move_made = false;
}

Pawn::~Pawn() {

}

bool Pawn::isCorrect(int x_, int y_) {

    return false;
}

bool Pawn::isPossible(int x_, int y_) {
    return false;
}

bool Pawn::move(char x_, char y_) {

    //TODO this is how it will be in final version
//    if (!(isCorrect(x_, y_)) || !(isPossible(x_, y_))) {
//        return false;
//    }
    // now to test only isCorrect()
    if (!(isCorrect(x_, y_))) {
        
    }
}

bool Pawn::isStarting() {
    /**
     *
     */
    return first_move_made;
}
