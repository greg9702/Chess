#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece{
private:
    bool isPossible(char x_, char y_) override;
    bool isCorrect(char x_, char y_) override;
public:
    Knight(color col_, Board* board_, Square* square_);
    ~Knight();
    bool move(char x_, char y_) override ;
};

#endif
