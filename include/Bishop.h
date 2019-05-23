#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include <iostream>
#include "Square.h"
#include "Board.h"

class Bishop : public Piece {
private:
    bool isCorrect(char x_, char y_) override;
public:
    bool isPossible(char x_, char y_) override;
    Bishop(color col_, Board* board_, Square* square_);
    ~Bishop();
};

#endif
