#include "Rook.h"
#include "Board.h"
#include "Square.h"

Rook::Rook(color col_, Board *board_, Square *square_)
    : Piece(col_, board_, square_) {
  /**
   * Constructor
   */

  this->type = ROOK;
}

Rook::~Rook() {
  /**
   * Destructor
   */
}

bool Rook::isCorrect(char x_, char y_) {
  /**
   * Check if move to new position is correct for Rook type
   * @param x cord of new position
   * @param y cord of new position
   * @return true if it is correct, false otherwise
   */

  return ((x_ == this->square->getCoords().first) !=
          (y_ == this->square->getCoords().second));
}

bool Rook::isPossible(char x_, char y_) {
  /**
   * Check if move to new position is possible
   * @param x cord of new position
   * @param y cord of new position
   * @return true if it is possible, false otherwise
   */

  if (!this->isCorrect(x_, y_))
    return false;
  if (this->board->getPieceByCoord(x_, y_) != nullptr &&
      this->board->getPieceByCoord(x_, y_)->getColor() == this->col)
    return false;

  if (this->board->getPieceByCoord(x_, y_) != nullptr &&
      this->board->getPieceByCoord(x_, y_)->getColor() == this->col)
    return false;
  // vertical movement
  if (x_ == this->square->getCoords().first) {
    char target = this->square->getCoords().second;
    char beg = target > y_ ? y_ + 1 : target + 1;
    char fin = target > y_ ? target : y_;
    for (char i = beg; i < fin; ++i) {
      if (this->board->getPieceByCoord(x_, i) != nullptr)
        return false;
    }
  }

  // horizontal movement
  if (y_ == this->square->getCoords().second) {
    char target = this->square->getCoords().first;
    char beg = target > x_ ? x_ + 1 : target + 1;
    char fin = target > x_ ? target : x_;
    for (char i = beg; i < fin; ++i) {
      if (this->board->getPieceByCoord(i, y_) != nullptr)
        return false;
    }
  }
  return true;
}