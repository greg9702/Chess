#ifndef BOARD_H
#define BOARD_H

#include <utility>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Square.h"
#include "Enums.h"

class Board {
private:
	color turn;
	game_state game_s;
	std::map<std::pair<char, char>, Square> matrix;
	std::vector<Piece *> piecesOnBoard;
	std::vector<std::string> history;
	std::vector<Piece *> findPieces(color col,Piece_type typ);
public:
	Board();
	~Board();
	bool isCheck();
	bool move(std::string instruction);
    std::string getHistory();
    color getTurn();
    Piece* getPieceByCoord(char x_, char y_);
    std::map<std::pair<char,char>,Square> getMatrix();
};

#endif
