#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
private:
    bool isCorrect(char x_, char y_) override;
    bool isPossible(char x_, char y_) override;

public:
    Bishop(color col_, Board* board_, Square* square_);
    ~Bishop();
};

#endif
