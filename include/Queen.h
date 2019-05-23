#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include <cmath>

class Queen : public Piece{
    bool isCorrect(char x_, char y_) override;
public:
    bool isPossible(char x_, char y_) override;
    Queen(color col_, Board* board_, Square* square_);
    ~Queen();
};

#endif
