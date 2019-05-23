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
      new Pawn(WHITE, this, matrix.at(std::make_pair('a', '6'))));
  piecesOnBoard.push_back(
      new Pawn(BLACK, this, matrix.at(std::make_pair('h', '5'))));
  piecesOnBoard.push_back(
      new Queen(BLACK, this, matrix.at(std::make_pair('b', '7'))));
  piecesOnBoard.push_back(
      new Queen(WHITE, this, matrix.at(std::make_pair('d', '1'))));
}

Board::~Board() {
  /**
   * Destructor
   */
  for (auto &it : piecesOnBoard)
    delete it;
  std::cout << "Board destructor" << std::endl;
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

    char dest_x;
    char dest_y;
    Piece_type fig_to_move;
    special_args add_opt = NONE;
    // figure move
    if (isupper(instruction.at(0))) { // SET UP ALL FIGURES MOVE EXCEPT PAWN

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
    } else { // SET UP PAWN MOVE

        if (instruction.size() == 4 && instruction.at(2) == '=') {
            // PROCESS promotion
            std::cout << "promotion!" << std::endl;
            switch (instruction.at(3)) {
                case 'B':
                    add_opt = PROM_B;
                    break;
                case 'N':
                    add_opt = PROM_N;
                    break;
                case 'Q':
                    add_opt = PROM_Q;
                    break;
                case 'R':
                    add_opt = PROM_R;
                    break;
                default:
                    return false;
            }
        } else if (instruction.size() != 2) {
            std::cout << "INVALID SIZE OF INSTR" << std::endl;
            return false;
        }

        dest_x = instruction.at(0);
        dest_y = instruction.at(1);
        fig_to_move = PAWN;
    }


    std::vector<Piece *> candidatesToMove = this->findPieces(turn, fig_to_move);
    for (auto it = candidatesToMove.begin(); it != candidatesToMove.end();
         ++it) { // auto = std::vector<Piece*>::iterator
        if ((*it)->move(dest_x, dest_y,add_opt)) {
            std::cout << "Figure moved to: " << (*it)->getSquare()->getCoords().first
                      << (*it)->getSquare()->getCoords().second << std::endl;
            history.push_back(instruction);
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
  for (auto &sq : this->matrix) {
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

void Board::addNewPiece(Piece *new_piece) {
  this->piecesOnBoard.push_back(new_piece);
}
