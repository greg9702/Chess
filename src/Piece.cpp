#include "Piece.h"
#include "Board.h"
#include "Square.h"

Piece::Piece(color col_, Board *board_, Square *square_) {
  /**
   * Constructor
   */

  this->board = board_;
  this->square = square_;
  this->col = col_;
  this->square->setOccupator(this);
  this->first_move_made = false;
}

Piece::~Piece() {
  /**
   * Destructor
   */
}

color Piece::getColor() { return this->col; }

Piece_type Piece::getType() {
  /**
   * Getter for type
   * @return type of piece
   */

  return this->type;
}

bool Piece::isCorrect(char x_, char y_) {
  /**
   * Check if proposed move is correct for this type of Piece
   * @return true if is correct, false otherwise
   */

  return true;
}

bool Piece::isPossible(char x_, char y_) {
  /**
   * Ckeck if proposed move is possible
   * @return true if is move is possible false otherwise
   */

  return true;
}

bool Piece::move(char x_, char y_, special_args add_opt) {
  /**
   * Move Piece to new position
   * @param x cord of new position
   * @param y cord of new position
   * @return true if Piece was moved sucesfully, false otherwise
   */

  if (x_ < 'a' || x_ > 'h' || y_ < '1' || y_ > '8')
    return false;

  if (!isPossible(x_, y_))
    return false;

  std::cout << "Figure to move: " << this->getSquare()->getCoords().first
            << this->getSquare()->getCoords().second << std::endl;

  this->square->setOccupator(nullptr);
  this->square = board->getMatrix().at(std::pair<char, char>(x_, y_));
  this->square->setOccupator(this);
  this->first_move_made = true;

  if (this->board->isCheck(this->col)) {
    this->board->setUndoFlag();
    return false;
  }

  // default no en-passant in next move (if there is, it's being set in
  // Pawn::move())
  for (char i = 'a'; i <= 'h'; ++i) {
    this->board->getMatrix()
        .at(std::pair<char, char>(i, '3'))
        ->setEnPassant(false);
    this->board->getMatrix()
        .at(std::pair<char, char>(i, '6'))
        ->setEnPassant(false);
  }

  return true;
}

Square *Piece::getSquare() {
  /**
   * Return pointer to square which pawn is occuping
   * @return pointer to square
   */

  return this->square;
}

bool Piece::isStarting() {
  /**
   * Some pieces have different move options, when they move for the 1st time
   * @return true if piece haven't moved yet, false otherwise
   */

  return !first_move_made;
}
