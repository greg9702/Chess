#include "Knight.h"
#include "Board.h"
#include "Square.h"

Knight::Knight(color col_, Board *board_, Square *square_)
    : Piece(col_, board_, square_) {
  this->type = KNIGHT;
}

Knight::~Knight() {}

bool Knight::isPossible(char x_, char y_) {
  if (!(isCorrect(x_, y_))) {
    return false;
  }
  std::cout << "Is Correct() passed" << std::endl;
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

  std::pair<char, char> current_pos = this->square->getCoords();

  if (current_pos.first + 2 == x_ && current_pos.second + 1 == y_) {
    return true;
  }
  if (current_pos.first - 2 == x_ && current_pos.second + 1 == y_) {
    return true;
  }
  if (current_pos.first + 2 == x_ && current_pos.second - 1 == y_) {
    return true;
  }
  if (current_pos.first - 2 == x_ && current_pos.second - 1 == y_) {
    return true;
  }
  if (current_pos.first + 1 == x_ && current_pos.second + 2 == y_) {
    return true;
  }
  if (current_pos.first - 1 == x_ && current_pos.second + 2 == y_) {
    return true;
  }
  if (current_pos.first + 1 == x_ && current_pos.second - 2 == y_) {
    return true;
  }
  if (current_pos.first - 1 == x_ && current_pos.second - 2 == y_) {
    return true;
  }

  return false;
}
