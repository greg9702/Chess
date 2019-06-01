#include "Bishop.h"

Bishop::Bishop(color col_, Board *board_, Square *square_)
    : Piece(col_, board_, square_) {
  this->type = BISHOP;
}

Bishop::~Bishop() {}

bool Bishop::isCorrect(char x_, char y_) {
  /**
   * Check if move is correct for Bishop type
   * @param x cord of new square on board
   * @param y cord of new square on board
   * @return true if it is correct move, false otherwise
   */

  std::pair<char, char> current_pos = this->square->getCoords();

  if (abs(y_ - current_pos.second) != abs(x_ - current_pos.first)) {
    return false;
  }
  return true;
}

bool Bishop::isPossible(char x_, char y_) {
  /**
   * Check if move is possible if we consider postion of other pieces on board
   * @param x cord of new square on board
   * @param x cord of new square on board
   * @return true if move is possbile, false otherwise
   */

  if (!isCorrect(x_, y_)) {
    return false;
  }
  std::pair<char, char> current_pos = this->square->getCoords();

  // now check if there are no other figures on his way
  for (int i = 1; i < abs(x_ - current_pos.first); i++) {
    if (current_pos.first > x_ &&
        current_pos.second > y_) { // figure move left down
      if (this->board->getMatrix()
              .at(std::pair<char, char>(current_pos.first - i,
                                        current_pos.second - i))
              ->getOccupator() != nullptr) {
        return false;
      }
    }
    if (current_pos.first > x_ &&
        current_pos.second < y_) { // figure move top left
      if (this->board->getMatrix()
              .at(std::pair<char, char>(current_pos.first - i,
                                        current_pos.second + i))
              ->getOccupator() != nullptr) {
        return false;
      }
    }
    if (current_pos.first < x_ &&
        current_pos.second > y_) { // figure move down right
      if (this->board->getMatrix()
              .at(std::pair<char, char>(current_pos.first + i,
                                        current_pos.second - i))
              ->getOccupator() != nullptr) {
        return false;
      }
    }
    if (current_pos.first < x_ &&
        current_pos.second < y_) { // figure move top right
      if (this->board->getMatrix()
              .at(std::pair<char, char>(current_pos.first + i,
                                        current_pos.second + i))
              ->getOccupator() != nullptr) {
        return false;
      }
    }
  }

  // check if last field is occupated by figure, if its your figure move is
  // invalid, if not it is correct
  if (this->board->getMatrix()
          .at(std::pair<char, char>(x_, y_))
          ->getOccupator() != nullptr) {
    if (this->board->getMatrix()
            .at(std::pair<char, char>(x_, y_))
            ->getOccupator()
            ->getColor() == this->col) {
      return false;
    }
  }
  return true;
}
