#include "Board.h"
#include <Bishop.h>
#include <King.h>
#include <Knight.h>
#include <Pawn.h>
#include <Queen.h>
#include <Rook.h>
#include <assert.h>

Board::Board() {
  /**
   * Parameterless constructor, initializes table with all pieces
   */
  turn = WHITE;
  game_s = NORMAL;
  // create matrix
  for (char tmp_y = '1'; tmp_y <= '8'; ++tmp_y) {
    for (char tmp_x = 'a'; tmp_x <= 'h'; ++tmp_x) {
      matrix.insert(std::pair<std::pair<char, char>, Square *>(
          std::make_pair(tmp_x, tmp_y), new Square(tmp_x, tmp_y)));
    }
  }
  // create pieces

    piecesOnBoard.push_back(
        new Pawn(WHITE, this, matrix.at(std::make_pair('a', '5'))));
    piecesOnBoard.push_back(
        new Pawn(BLACK, this, matrix.at(std::make_pair('h', '5'))));

}

Board::~Board() {
  /**
   * Destructor
   */
  std::cout << "Board destructor" << std::endl;
  for (auto it = piecesOnBoard.begin(); it != piecesOnBoard.end(); ++it)
    delete *it;
  for (auto &mp : matrix) {
    delete mp.second;
  }
}

bool Board::isCheck() {
  /**
   * Checks if there was check.
   * @return true if there was check, false otherwise
   */
  return game_s == CHECK || game_s == CHECK_MATE;
}

bool Board::move(std::string instruction) {
  /**
   * Moves piece like said in the instruction
   * @param instruction next move in chess notation
   * @return true if the move was successfully performed, false otherwise
   */
  // TODO roszada
  // TODO konfliktowe sytuacje gdy 2 figury mogą wykonać ten ruch <= done

  if (instruction.size() < 2) {
    return false;
  }
  bool castling_request = false;
  char dest_x;
  char dest_y;
  Piece_type fig_to_move;

  // figure move
  if (isupper(instruction.at(0))) {
    if (instruction.size() != 3)
      return false;
    dest_x = instruction.at(1);
    dest_y = instruction.at(2);
    switch (instruction.at(0)) {
    case 'B':
      fig_to_move = BISHOP;
      break;
    case 'K':
      fig_to_move = KING;
      break;
    case 'N':
      fig_to_move = KNIGHT;
      break;
    case 'Q':
      fig_to_move = QUEEN;
      break;
    case 'R':
      fig_to_move = ROOK;
      break;
    default:
      return false;
    }
  } else {
    if (instruction.size() == 4 ) { // castling notation eg e8=Q
        if (instruction.at(2) == '=') {
            std::cout << "Castling" << std::endl;
            castling_request = true;
        } else {
            return false;
        }
    } else if (instruction.size() != 2) {
        std::cout << "XDDD" << std::endl;
        return false;
    }

    dest_x = instruction.at(0);
    dest_y = instruction.at(1);
    fig_to_move = PAWN;
  }

  std::vector<Piece *> candidatesToMove = this->findPieces(turn, fig_to_move);
  for (auto it = candidatesToMove.begin(); it != candidatesToMove.end();
       ++it) { // auto = std::vector<Piece*>::iterator
    if ((*it)->move(dest_x, dest_y)) {
      std::cout << "Figure moved to: " << (*it)->getSquare()->getCoords().first
                << (*it)->getSquare()->getCoords().second << std::endl;
      history.push_back(instruction);

      if (castling_request) {
          castling_request = false;
          Piece_type new_type;
          switch (instruction.at(3)) {
              case 'N':
                  new_type = KNIGHT;
                  break;
              case 'Q':
                  new_type = QUEEN;
                  break;
              case 'B':
                  new_type = BISHOP;
                  break;
              case 'R':
                  new_type = ROOK;
                  break;
              default:
                  return false;
          }
          // if castling happened and pawn moved to last field, change its type
          if ((turn == WHITE && (*it)->getSquare()->getCoords().second == '8') || (turn == BLACK && (*it)->getSquare()->getCoords().second == '1')) {
              (*it)->setType(new_type);
          }
          std::cout << "TYPE AFTER CHANGE: " << (*it)->getType() << std::endl;
      }

      turn = turn == WHITE ? BLACK : WHITE;
      return true;
    }
  }
  return false;
}

std::string Board::getHistory() {
  /**
   * Getter of history
   * @return history of the chess game, using standard chess notation
   */
  std::string formattedHistory = "";
  for (int i = 0; i < history.size(); ++i) {
    formattedHistory += history[i];
    formattedHistory += " ";
    if (i % 2 == 1) {
      formattedHistory += "\n";
    }
  }
  formattedHistory += "\n";
  return formattedHistory;
}

std::map<std::pair<char, char>, Square *> Board::getMatrix() {
  /**
   * Getter of matrix
   * @return map containing indexes of squares and object Square describing the
   * square
   */
  return this->matrix;
}

color Board::getTurn() {
  /**
   * Getter of turn
   * @return if black or white is about to move
   */
  return this->turn;
}

std::vector<Piece *> Board::findPieces(color col, Piece_type typ) {
  /**
   * Searches for every possible type of piece on the whole board
   * @return vector of suitable pieces
   */

  std::vector<Piece *> matching_pieces;
  for (auto &sq : matrix) {
    Piece *sq_occup = sq.second->getOccupator();
    if (sq_occup != nullptr && sq_occup->getColor() == col &&
        sq_occup->getType() == typ) {
      matching_pieces.push_back(sq_occup);
    }
  }
  std::cout << "Candidates: " << std::endl;
  for (auto &el : matching_pieces) {
    std::cout << el->getSquare()->getCoords().first
              << el->getSquare()->getCoords().second << std::endl;
  }
  return matching_pieces;
}

Piece *Board::getPieceByCoord(char x_, char y_) {
  /**
   * Getter
   * @param x_ x-coordinate
   * @param y_ y-coordinate
   * @return pointer to Piece on the Square of coordinated x_, y_
   */
  return (this->matrix.at(std::pair<char, char>(x_, y_)))->getOccupator();
}
