#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece{
private:
    bool isCorrect() override;
    bool isPossible() override;
public:
    Rook();
    ~Rook();
    bool move(char x, char y_) override;
};

#endif
