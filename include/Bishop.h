#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
private:
    bool isCorrect() override;
    bool isPossible() override;
public:
    Bishop(color col_, std::shared_ptr<Board> board_, std::shared_ptr<Square> square_);
    ~Bishop();
    bool move(char x_, char y_) override ;
};

#endif
