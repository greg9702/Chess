#ifndef BOARD_H
#define BOARD_H

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
	std::vector<std::string> history;
public:
	Board();
	~Board();
	bool isCheck();
	bool move(std::string instruction);
    std::string getHistory();
    color getTurn();
    std::map<std::pair<char,char>,Square> getMatrix();
};

#endif
