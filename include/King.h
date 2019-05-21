#ifndef KING_H
#define KING_H

#include <memory>
#include "Piece.h"

class King : public Piece{
    bool isCorrect() override;
    bool isPossible() override;

public:
    King(color col_, std::shared_ptr<Board> board_, std::shared_ptr<Square> square_);
    ~King();
    bool move(char x_, char y_) override ;

};

#endif
