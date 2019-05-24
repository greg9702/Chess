#include "Knight.h"
#include "Board.h"
#include "Square.h"
#include <cmath>
#include <iostream>

Knight::Knight(color col_, Board *board_, Square *square_)
    : Piece(col_, board_, square_) {
  this->type = KNIGHT;
}

Knight::~Knight() {}

bool Knight::isPossible(char x_, char y_) {
  if (!(isCorrect(x_, y_))) {
    return false;
  }
  if ((this->board->getPieceByCoord(x_, y_) != nullptr) &&
      (this->board->getMatrix()
           .at(std::pair<char, char>(x_, y_))
           ->getOccupator()
           ->getColor() == this->col)) {
    return false;
  }

  return true;
}

bool Knight::isCorrect(char x_, char y_) {
  char my_x = this->square->getCoords().first;
  char my_y = this->square->getCoords().second;

  if (abs(my_x - x_) == 2 && abs(my_y - y_) == 1)
    return true;
  if (abs(my_x - x_) == 1 && abs(my_y - y_) == 2)
    return true;
  return false;
}
