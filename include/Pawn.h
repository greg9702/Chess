#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece{
private:
    bool isCorrect(char x_, char y_) override;
public:
    bool isPossible(char x_, char y_) override;
    Pawn(color col_, Board* board_, Square* square_);
    ~Pawn();
    bool move(char x_, char y_,special_args add_opt) override ;
};

#endif
