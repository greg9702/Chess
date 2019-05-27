#ifndef BOARD_H
#define BOARD_H

#include <utility>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Square.h"
#include "Enums.h"
#include <algorithm>


struct MyComparator {
    bool operator()(const std::pair<char,char>& a, const std::pair<char,char>& b) const {
        if (a.second == b.second){
            return a.first < b.first;
        }
        else {
            return a.second > b.second;
        }
    }
};


class Board {
private:
    special_args cas_type;
	color turn;
	game_state game_s;
	std::map<std::pair<char, char>, Square*,MyComparator> matrix;
	std::vector<Piece*> piecesOnBoard;
	std::vector<std::string> history;
	Board * backup;
	bool undo_flag;
	void deepCopy(Board* src);
public:
	Board();
	Board(Board &);
	~Board();
	bool move(std::string instruction);
	bool undo();
	void setUndoFlag();
    void addNewPiece(Piece* new_piece);
    std::vector<Piece *> findPieces(color col,Piece_type typ = ANY);
    bool isCheck(color col,std::pair<char,char>king_pos=std::pair<char,char>('0','0'));
    game_state getGameState(color col);
    color getTurn();
    Piece* getPieceByCoord(char x_, char y_);
    std::map<std::pair<char,char>, Square*,MyComparator> getMatrix();
    std::string getHistory();
    special_args getCastlingType();
};

#endif
