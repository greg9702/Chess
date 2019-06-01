#ifndef KING_H
#define KING_H

#include "Board.h"
#include "Piece.h"
#include "Square.h"

class King : public Piece {
  bool isCorrect(char x_, char y_) override;

public:
  bool isPossible(char x_, char y_) override;
  bool move(char x_, char y_, special_args add_opt = NONE) override;
  King(color col_, Board *board_, Square *square_);
  ~King();
};

#endif
