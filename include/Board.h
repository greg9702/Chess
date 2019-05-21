#ifndef BOARD_H
#define BOARD_H

#include <iostream>

enum game_state {
	NORMAL,
	CHECK,
	CHECK MATE
};

enum color {
	BLACK,
	WHITE
};

class Board {
private:
	color turn;
	game_state game_s;
	std::map<std::pair<char, char>, Square square> matrix;
public:
	Board();
	~Board();
};

#endif
