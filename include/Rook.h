#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece{
private:
    bool isCorrect() override;
    bool isPossible() override;
public:
    Rook(color col_, std::shared_ptr<Board> board_, std::shared_ptr<Square> square_);
    ~Rook();
    bool move(char x, char y_) override;
};

#endif
