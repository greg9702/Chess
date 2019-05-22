#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece{
    bool isPossible(char x_, char y_) override;
    bool isCorrect(char x_, char y_) override;
public:
    Queen(color col_, Board* board_, Square* square_);
    ~Queen();
    bool move(char x_, char y_) override;
};

#endif
