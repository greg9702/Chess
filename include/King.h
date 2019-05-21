#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece{
    bool isCorrect() override;
    bool isPossible() override;

public:
    King();
    ~King();
    bool move(char x_, char y_) override ;

};

#endif
