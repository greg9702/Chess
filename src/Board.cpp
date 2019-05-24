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
  this->undo_flag = false;
  // create matrix
  for (char tmp_y = '1'; tmp_y <= '8'; ++tmp_y) {
    for (char tmp_x = 'a'; tmp_x <= 'h'; ++tmp_x) {
      matrix.insert(std::pair<std::pair<char, char>, Square *>(
          std::make_pair(tmp_x, tmp_y), new Square(tmp_x, tmp_y)));
    }
  }

  // create pieces

    piecesOnBoard.push_back(
            new Pawn(WHITE, this, matrix.at(std::make_pair('a', '7'))));
    piecesOnBoard.push_back(
            new King(WHITE, this, matrix.at(std::make_pair('e', '1'))));
    piecesOnBoard.push_back(
            new Pawn(WHITE, this, matrix.at(std::make_pair('h', '7'))));


    piecesOnBoard.push_back(
            new King(BLACK, this, matrix.at(std::make_pair('a', '5'))));



    backup = nullptr;

}

Board::Board(Board & brd) {
    /**
     * Copy constructor - we need a deep copy
     * @param brd - Object where from to copy
     */
    this->deepCopy(&brd);
    this->backup = nullptr;
}

Board::~Board() {
  /**
   * Destructor
   */
  for (auto &it : piecesOnBoard)
    delete it;
  //std::cout << "Board destructor" << std::endl;
  for (auto &mp : matrix) {
    delete mp.second;
  }
}


game_state Board::getGameState(color col) {
    /**
     * Method that sets and returns the particular game state
     * It more precise than Board::isCheck() method
     * @param col - color to check the state
     * @return current game_state
     */
    bool stale_mate_flag = true;
    // low performance, highly recommended to change
    std::vector<Piece *> my_pieces = this->findPieces(col);
    for (auto& mover : my_pieces){
        for (char tmp_y = '1'; tmp_y <= '8'; ++tmp_y) {
            for (char tmp_x = 'a'; tmp_x <= 'h'; ++tmp_x) {
                if (mover->isPossible(tmp_x,tmp_y)){
                    char src_x = mover->getSquare()->getCoords().first;
                    char src_y = mover->getSquare()->getCoords().second;

                    mover->square->setOccupator(nullptr);
                    mover->square = this->getMatrix().at(std::pair<char, char>(tmp_x, tmp_y));
                    Piece * was_captured = mover->square->getOccupator();
                    mover->square->setOccupator(mover);

                    // if there is a move possible
                    if (!isCheck(col,std::pair<char,char>('0','0'))) {
                        stale_mate_flag = false;
                        mover->square->setOccupator(nullptr);
                        mover->square = this->getMatrix().at(std::pair<char, char>(src_x, src_y));
                        mover->square->setOccupator(mover);
                        break;
                    }
                    mover->square->setOccupator(was_captured);
                    mover->square = this->getMatrix().at(std::pair<char, char>(src_x, src_y));
                    mover->square->setOccupator(mover);
                }
            }
            // if we've fount a possible move
            if (!stale_mate_flag)
                break;
        }
    }
    isCheck(col,std::pair<char,char>('0','0'));
    if (game_s != CHECK){
        if (stale_mate_flag)
            this->game_s = STALE_MATE;
        else
            this->game_s = NORMAL;
    } else {
        if (!stale_mate_flag) {
            this->game_s = CHECK;
        } else {
            this->game_s = CHECK_MATE;
        }
    }
    return this->game_s;
}

bool Board::move(std::string instruction) {
  /**
   * Moves piece like said in the instruction
   * @param instruction next move in chess notation
   * @return true if the move was successfully performed, false otherwise
   */

  //Remember the state before the move
    delete backup;
    backup = new Board(*this);

    if (instruction.size() < 3 || instruction.size() > 6) {
        return false;
    }

    char src_x,src_y,dest_x,dest_y;
    Piece_type fig_to_move;
    special_args add_opt = NONE;
    // figure move
    if (isupper(instruction.at(0))) { // SET UP ALL FIGURES MOVE EXCEPT PAWN
        if (instruction.size() > 5)
            return false;
        switch (instruction.at(0)) {
            case 'B':
                fig_to_move = BISHOP;
                break;
            case 'K':
                fig_to_move = KING;
                break;
            case 'O':
                fig_to_move = KING;
                if (instruction == "O-O")
                    add_opt = SHORT_CASTLE;
                else if (instruction == "O-O-O")
                    add_opt = LONG_CASTLE;
                else
                    return false;
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
        if (instruction.at(0) != 'O') {
            switch (instruction.size()) {
                case 5:
                    src_x  = instruction.at(1);
                    src_y  = instruction.at(2);
                    dest_x = instruction.at(3);
                    dest_y = instruction.at(4);
                    break;
                default:
                    return false;
            }
        } else{
            if (this->findPieces(this->turn,KING).empty())
                return false;
            Piece * king = this->findPieces(this->turn,KING).at(0);
            src_x  = king->getSquare()->getCoords().first;
            src_y  = king->getSquare()->getCoords().second;
            dest_x = '1';//trash values for castling
            dest_y = 'a';
        }
    } else { // SET UP PAWN MOVE
        switch (instruction.size()){
            case 6:
                if ((instruction.at(instruction.size()-2) != '='))
                    return false;
                std::cout << "promotion!" << std::endl;
                switch (instruction.at((instruction.size()-1))) {
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
            case 4:
                src_x  = instruction.at(0);
                src_y  = instruction.at(1);
                dest_x = instruction.at(2);
                dest_y = instruction.at(3);
                break;
            default:
                break;
        }
        fig_to_move = PAWN;
    }
    Piece * candidate_to_move = this->getPieceByCoord(src_x,src_y);
    if (candidate_to_move == nullptr ||
        fig_to_move != candidate_to_move->getType() ||
        this->turn != candidate_to_move->getColor())
        return false;

    if (candidate_to_move->move(dest_x, dest_y,add_opt)) {
        std::cout << "Figure moved to: " << candidate_to_move->getSquare()->getCoords().first
                  << candidate_to_move->getSquare()->getCoords().second << std::endl;
        history.push_back(instruction);
        turn = turn == WHITE ? BLACK : WHITE;
        return true;
    }

    // if there is still check after the "possible" move (Piece::move() returned false, but it changed the board)
    if (undo_flag)
        undo();
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
            (typ == ANY || sq_occup->getType() == typ)) {
      matching_pieces.push_back(sq_occup);
    }
  }
  /*
  std::cout << "Candidates: " << std::endl;
  for (auto &el : matching_pieces) {
    std::cout << el->getSquare()->getCoords().first
              << el->getSquare()->getCoords().second << std::endl;
  }
  */
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

bool Board::isCheck(color col,std::pair<char,char>king_pos) {
    /**
     * Method that checks if the king of color col is in check
     * Method sets the value of member game_s (CHECK / NORMAL)
     * @param col color of the checked king
     * @param king_pos particular position of king to check (useful f.e. while checking if castling is possible)
     * @return vector of pointers to the pieces that are checking the king
     */
    char king_x,king_y;
    // if there is no special position to check, use current king position
    if (king_pos == std::pair<char,char>('0','0')) {
        std::vector<Piece *> king = this->findPieces(col, KING);
        //if there is no King at the board
        if (king.empty()) {
            return false;
        }
        king_x = king.at(0)->getSquare()->getCoords().first;
        king_y = king.at(0)->getSquare()->getCoords().second;
    }else{
        king_x = king_pos.first;
        king_y = king_pos.second;
    }

    color sec_col = col == WHITE ? BLACK : WHITE;
    std::vector<Piece *> candidates = this->findPieces(sec_col);
    for (auto & cand : candidates){
        if (cand->isPossible(king_x,king_y)){
            this->game_s = CHECK;
            return true;
        }
    }
    this->game_s = NORMAL;
    return false;
}

bool Board::undo() {
    /**
     * Method that changes the content of the board to the state stored in backup
     */
    for (auto &it : piecesOnBoard)
        delete it;
    for (auto &mp : matrix) {
        delete mp.second;
    }
    this->piecesOnBoard.clear();
    this->matrix.clear();

    this->deepCopy(this->backup);

    // create matrix
    undo_flag = false;
    return true;
}

void Board::setUndoFlag() {
    /**
     * Method that sets the private member undo_flag
     */
    this->undo_flag = true;
}

void Board::deepCopy(Board *src) {
    /**
     * Private method that makes a deep copy of Squares and Figures stored in src.
     * They are copied to *this object.
     * There is need that *this has cleared squares map and pieces vector
     * @param src - pointer to Board, where from we will copy the data
     */
    for (char tmp_y = '1'; tmp_y <= '8'; ++tmp_y) {
        for (char tmp_x = 'a'; tmp_x <= 'h'; ++tmp_x) {
            matrix.insert(std::pair<std::pair<char, char>, Square *>(
                    std::make_pair(tmp_x, tmp_y), new Square(tmp_x, tmp_y)));
        }
    }

    // create pieces
    auto white = src->findPieces(WHITE);
    auto black = src->findPieces(BLACK);
    for(auto &white_piece : white){
        Square * my_square = this->matrix.at((white_piece->getSquare()->getCoords()));

        switch (white_piece->getType()){
            case ROOK:
                this->piecesOnBoard.push_back(new Rook(WHITE,this,my_square));
                break;
            case KNIGHT:
                this->piecesOnBoard.push_back(new Knight(WHITE,this,my_square));
                break;
            case BISHOP:
                this->piecesOnBoard.push_back(new Bishop(WHITE,this,my_square));
                break;
            case QUEEN:
                this->piecesOnBoard.push_back(new Queen(WHITE,this,my_square));
                break;
            case KING:
                this->piecesOnBoard.push_back(new King(WHITE,this,my_square));
                break;
            case PAWN:
                this->piecesOnBoard.push_back(new Pawn(WHITE,this,my_square));
                break;
            default:
                break;
        }
    }
    for(auto &black_piece : black){
        Square * my_square = this->matrix.at((black_piece->getSquare()->getCoords()));
        switch (black_piece->getType()){
            case ROOK:
                this->piecesOnBoard.push_back(new Rook(BLACK,this,my_square));
                break;
            case KNIGHT:
                this->piecesOnBoard.push_back(new Knight(BLACK,this,my_square));
                break;
            case BISHOP:
                this->piecesOnBoard.push_back(new Bishop(BLACK,this,my_square));
                break;
            case QUEEN:
                this->piecesOnBoard.push_back(new Queen(BLACK,this,my_square));
                break;
            case KING:
                this->piecesOnBoard.push_back(new King(BLACK,this,my_square));
                break;
            case PAWN:
                this->piecesOnBoard.push_back(new Pawn(BLACK,this,my_square));
                break;
            default:
                break;
        }
    }
    this->turn = src->turn;
    this->game_s = src->game_s;
}



