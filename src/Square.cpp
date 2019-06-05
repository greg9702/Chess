//
// Created by greg9702 on 5/21/19.
//

#include <Square.h>
#include <assert.h>

Square::Square(char x_, char y_) {
  /**
   * Constructor
   * @param x cordinate of board square
   * @param y corinate of board square
   * @param Piece object - if piece stand on square, nullptr otherwise
   */

  assert((x_ >= (int)'a' && x_ <= (int)'h') ||
         (x_ >= (int)'A' && x_ <= (int)'H'));
  assert(y_ >= (int)'1' && y_ <= (int)'8');

  this->occupator = nullptr;

  if (((x_ - 'a') + (y_ - '1')) % 2 == 0)
    this->col = BLACK;
  else
    this->col = WHITE;

  this->en_passant_flag = false;

  this->x = x_;
  this->y = y_;
}

Piece *Square::getOccupator() {
  /**
   * Return pointer to occupator Piece object
   * @return pointer to piece object if piece stand on this square nullptr
   * otherwise
   */

  return this->occupator;
}

void Square::setOccupator(Piece *occupator_) {
  /**
   * Set occupatr
   * @param pointer to occupator obj //TODO what about nullptr
   */

  this->occupator = occupator_;
}

Square::~Square() {
  /**
   * Destructor
   */
}

std::pair<char, char> Square::getCoords() {
  /**
   * Return cords x and y of square as pair
   * @return pair<char, char> of cords <x,y>
   */

  return std::pair<char, char>(this->x, this->y);
}

color Square::getColor() {
  /**
   * Getter for square color
   * @return enum color type
   */

  return this->col;
}

void Square::setEnPassant(bool en_pass) {
  /**
   * Setter for En passant flag
   * @param en passant boolean
   */

  this->en_passant_flag = en_pass;
}

bool Square::getEnPassant() {
  /**
   * Getter for en passant flag
   * @return boolean en passant flag
   */

  return this->en_passant_flag;
}
