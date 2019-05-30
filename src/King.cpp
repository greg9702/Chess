#include "King.h"
#include <cmath>

bool King::isPossible(char x_, char y_) {

  if (!isCorrect(x_, y_)) {
    return false;
  }

  if (this->board->getMatrix()
          .at(std::pair<char, char>(x_, y_))
          ->getOccupator() == nullptr) {
    return true;
  }
  if (this->board->getMatrix()
          .at(std::pair<char, char>(x_, y_))
          ->getOccupator()
          ->getColor() == this->col) {
    return false;
  }

  // TODO check if there is no check
  return true;
}

bool King::isCorrect(char x_, char y_) {
  std::pair<char, char> current_pos = this->square->getCoords();

  if ((abs(current_pos.first - x_) > 1) || (abs(current_pos.second - y_) > 1)) {
    return false;
  }

  return true;
}

King::King(color col_, Board *board_, Square *square_)
    : Piece(col_, board_, square_) {
  this->type = KING;
  first_move_made = false;
}

King::~King() {}

bool King::move(char x_, char y_, special_args add_opt) {
  if (add_opt == NONE) {
    if (Piece::move(x_, y_)) {
      first_move_made = true;
      return true;
    }
  }
  // castling
  else if (add_opt == SHORT_CASTLE || add_opt == LONG_CASTLE) {
    char my_x = this->getSquare()->getCoords().first;
    char my_y = this->getSquare()->getCoords().second;
    if (this->col == WHITE && !(my_x == 'e' && my_y == '1'))
      return false;
    if (this->col == BLACK && !(my_x == 'e' && my_y == '8'))
      return false;
    if (this->first_move_made)
      return false;
    auto my_rooks = this->board->findPieces(this->col, ROOK);
    if (add_opt == SHORT_CASTLE) {
      Piece *ok_rook = nullptr;
      for (auto &test_rook : my_rooks) {
        if (this->board->getPieceByCoord('h', my_y) == test_rook) {
          if (!(test_rook->isStarting()))
            return false;
          if (this->board->getPieceByCoord('f', my_y) != nullptr ||
              this->board->getPieceByCoord('g', my_y) != nullptr)
            return false;
          if (this->col == WHITE) {
            if (this->board->isCheck(WHITE, std::pair<char, char>('f', '1')) ||
                this->board->isCheck(WHITE, std::pair<char, char>('g', '1')) ||
                this->board->isCheck(WHITE, std::pair<char, char>('e', '1')))
              return false;
          }
          if (this->col == BLACK) {
            if (this->board->isCheck(BLACK, std::pair<char, char>('f', '8')) ||
                this->board->isCheck(BLACK, std::pair<char, char>('g', '8')) ||
                this->board->isCheck(BLACK, std::pair<char, char>('e', '8')))
              return false;
          }
          ok_rook = test_rook;
        }
      }
      if (ok_rook == nullptr)
        return false;
      this->square->setOccupator(nullptr);
      this->square = board->getMatrix().at(std::pair<char, char>('g', my_y));
      this->square->setOccupator(this);
      this->first_move_made = true;

      ok_rook->square->setOccupator(nullptr);
      ok_rook->square = board->getMatrix().at(std::pair<char, char>('f', my_y));
      ok_rook->square->setOccupator(ok_rook);
      ok_rook->first_move_made = true;

    } else if (add_opt == LONG_CASTLE) {
      Piece *ok_rook = nullptr;
      for (auto &test_rook : my_rooks) {
        if (this->board->getPieceByCoord('a', my_y) == test_rook) {
          if (!test_rook->isStarting())
            return false;
          if (this->board->getPieceByCoord('b', my_y) != nullptr ||
              this->board->getPieceByCoord('c', my_y) != nullptr ||
              this->board->getPieceByCoord('d', my_y) != nullptr)
            return false;
          if (this->col == WHITE) {
            if (this->board->isCheck(WHITE, std::pair<char, char>('c', '1')) ||
                this->board->isCheck(WHITE, std::pair<char, char>('d', '1')) ||
                this->board->isCheck(WHITE, std::pair<char, char>('e', '1')))
              return false;
          }
          if (this->col == BLACK) {
            if (this->board->isCheck(BLACK, std::pair<char, char>('c', '8')) ||
                this->board->isCheck(BLACK, std::pair<char, char>('d', '8')) ||
                this->board->isCheck(BLACK, std::pair<char, char>('e', '8')))
              return false;
          }
          ok_rook = test_rook;
        }
      }
      if (ok_rook == nullptr)
        return false;

      this->square->setOccupator(nullptr);
      this->square = board->getMatrix().at(std::pair<char, char>('c', my_y));
      this->square->setOccupator(this);
      this->first_move_made = true;

      ok_rook->square->setOccupator(nullptr);
      ok_rook->square = board->getMatrix().at(std::pair<char, char>('d', my_y));
      ok_rook->square->setOccupator(ok_rook);
      ok_rook->first_move_made = true;
    }
    return true;
  }
  return false;
}
