#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece{
private:
    bool isPossible(int x_, int y_) override;
    bool isCorrect(int x_, int y_) override;
public:
    Knight(color col_, Board* board_, Square* square_);
    ~Knight();
    bool move(char x_, char y_) override ;
};

#endif
