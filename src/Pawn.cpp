#include <cmath>
#include "Board.h"
#include "Pawn.h"
#include "Square.h"

Pawn::Pawn(color col_, Board* board_, Square* square_) : Piece (col_, board_, square_) {
    this->type = PAWN;
    this->first_move_made = false;
}

Pawn::~Pawn() {

}

bool Pawn::isCorrect(char x_, char y_) {
    int my_x = this->square->getCoords().first;
    int my_y = this->square->getCoords().second;

    if (abs(x_ - my_x) <= 1){
       if ((y_ - my_y) == 1)
           return true;
       if (((!(this->first_move_made)) && (x_ == my_x) && ((y_ - my_y) == 2)))
           return true;
    }
    return false;
}

bool Pawn::isPossible(char x_, char y_) {
    int my_x = this->square->getCoords().first;
    int my_y = this->square->getCoords().second;

    //simple move, check if the road is empty
    if (x_ == my_x){
        if (this->board->getPieceByCoord(my_x+1,my_y+1))
            return false;
        if (this->board->getPieceByCoord(x_,y_) != nullptr)
            return false;
    }
    else{
        if (this->board->getPieceByCoord(x_,y_) == nullptr || this->board->getPieceByCoord(x_,y_)->getColor() == type)
            return false;
    }
    return true;
}

bool Pawn::move(char x_, char y_) {
    return Piece::move(x_,y_);
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
