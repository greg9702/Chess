#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece{
private:
    bool isCorrect() override;
    bool isPossible() override;
public:
    Pawn(color col_, Board* board_, Square* square_);
    ~Pawn();
    bool move(char x_, char y_) override ;
};

#endif
