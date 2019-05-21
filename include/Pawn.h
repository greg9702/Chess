#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece{
private:
    bool isCorrect(int x_, int y_) override;
    bool isPossible(int x_, int y_) override;
public:
    Pawn(color col_, Board* board_, Square* square_);
    ~Pawn();
    bool move(char x_, char y_) override ;
};

#endif
