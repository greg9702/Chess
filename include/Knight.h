#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
private:
  bool isCorrect(char x_, char y_) override;

public:
  bool isPossible(char x_, char y_) override;
  Knight(color col_, Board *board_, Square *square_);
  ~Knight();
};

#endif
