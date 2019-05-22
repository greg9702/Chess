#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece{
    bool isCorrect(char x_, char y_) override;
    bool isPossible(char x_, char y_) override;

public:
    King(color col_, Board* board_, Square* square_);
    ~King();

};

#endif
