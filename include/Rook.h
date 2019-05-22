#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece{
private:
    bool isCorrect(int x_, int y_) override;
    bool isPossible(int x_, int y_) override;
public:
    Rook(color col_, Board* board_, Square* square_);
    ~Rook();
    bool move(char x, char y_) override;
};

#endif
