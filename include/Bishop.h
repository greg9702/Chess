#ifndef BISHOP_H
#define BISHOP_H

#include "Board.h"
#include "Piece.h"
#include "Square.h"
#include <iostream>

class Bishop : public Piece {
private:
  bool isCorrect(char x_, char y_) override;

public:
  bool isPossible(char x_, char y_) override;
  Bishop(color col_, Board *board_, Square *square_);
  ~Bishop();
};

#endif
