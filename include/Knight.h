#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece{
private:
    bool isPossible() override;
    bool isCorrect() override;
public:
    Knight(color col_, Board* board_, Square* square_);
    ~Knight();
    bool move(char x_, char y_) override ;
};

#endif
