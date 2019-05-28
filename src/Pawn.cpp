#include "Pawn.h"
#include "Board.h"
#include "Square.h"
#include <cmath>
#include <Knight.h>
#include <Bishop.h>
#include <Rook.h>
#include <Queen.h>

Pawn::Pawn(color col_, Board *board_, Square *square_)
    : Piece(col_, board_, square_) {
  this->type = PAWN;
  this->first_move_made = false;
}

Pawn::~Pawn() {
    /*
  std::cout << "Deleted PAWN OF POSITION: "
            << this->getSquare()->getCoords().first
            << this->getSquare()->getCoords().second << std::endl;
    */
}

bool Pawn::isCorrect(char x_, char y_) {
  int my_x = this->square->getCoords().first;
  int my_y = this->square->getCoords().second;

  if (abs(x_ - my_x) <= 1) {
    if (this->col == WHITE) {
      if ((y_ - my_y) == 1)
        return true;
      if (((!(this->first_move_made)) && (x_ == my_x) && ((y_ - my_y) == 2)))
        return true;
    } else {
      if (-(y_ - my_y) == 1)
        return true;
      if (((!(this->first_move_made)) && (x_ == my_x) && (-(y_ - my_y) == 2)))
        return true;
    }
  }

  return false;
}

bool Pawn::isPossible(char x_, char y_) {
  if (!isCorrect(x_, y_))
    return false;
  int my_x = this->square->getCoords().first;
  int my_y = this->square->getCoords().second;

  // simple move, check if the road is empty
  char offset;
  if (this->col == WHITE)
    offset = 1;
  else
    offset = -1;
  if (x_ == my_x) {
    if (my_y + offset >= '1' && my_y + offset <= '8' &&
        this->board->getPieceByCoord(my_x, my_y + offset))
      return false;
    if (this->board->getPieceByCoord(x_, y_) != nullptr)
      return false;
  } else {
      if (this->board->getMatrix().at(std::pair<char, char>(x_, y_))->getEnPassant()) {
          return true;
      }
      if (this->board->getPieceByCoord(x_, y_) == nullptr ||
          this->board->getPieceByCoord(x_, y_)->getColor() == col)
      return false;
  }
  return true;
}

bool Pawn::move(char x_, char y_,special_args add_opt) {
    if (add_opt == NONE && !((this->col == WHITE && y_ == '8') || (this->col == BLACK && y_ == '1'))) {
        if (x_ != this->square->getCoords().first) {
            if (this->board->getMatrix().at(std::pair<char, char>(x_, y_))->getEnPassant()) {
                if (this->col == WHITE)
                    this->board->getMatrix().at(std::pair<char, char>(x_, y_ - 1))->setOccupator(nullptr);
                else
                    this->board->getMatrix().at(std::pair<char, char>(x_, y_ + 1))->setOccupator(nullptr);
            }
        }
        char old_y_ = this->getSquare()->getCoords().second;
        if (Piece::move(x_, y_)) {
            // en-passant settings
            int offset = -1;    // offset when white
            if (this->col == BLACK)
                offset = 1;     //o offset when black
            if (abs(old_y_ - y_) == 2)
                this->board->getMatrix().at(std::pair<char,char>(x_,y_+offset))->setEnPassant(true);
            std::cout << "After move: " << this->board->getMatrix().at(std::pair<char,char>('f','6'))->getEnPassant() << std::endl;
            return true;
            }
    }

    else if (add_opt != NONE && ((this->col == WHITE && this->getSquare()->getCoords().second == '7') || (this->col == BLACK && this->getSquare()->getCoords().second == '2'))){
        if (Piece::move(x_,y_)){
            switch (add_opt){
                case PROM_N:
                    this->board->addNewPiece(new Knight(this->col, this->board, this->getSquare()));
                    break;
                case PROM_B:
                    this->board->addNewPiece(new Bishop(this->col, this->board, this->getSquare()));
                    break;
                case PROM_R:
                    this->board->addNewPiece(new Rook(this->col, this->board, this->getSquare()));
                    break;
                case PROM_Q:
                    this->board->addNewPiece(new Queen(this->col, this->board, this->getSquare()));
                    break;
            }
            return true;
        }
    }
    return false;

}
