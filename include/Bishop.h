#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
private:
    bool isCorrect(int x_, int y_) override;
    bool isPossible(int x_, int y_) override;

public:
    Bishop(color col_, Board* board_, Square* square_);
    ~Bishop();
    bool move(char x_, char y_) override ;
};

#endif
