#ifndef PIECE_H
#define PIECE_H

class Board;
class Square;

#include "Enums.h"

class Piece{
protected:
	color col;
	Piece_type type;
	Board* board;
	Square* square;
	virtual bool isCorrect() = 0;
	virtual bool isPossible() = 0;
public:
	Piece();
	~Piece();
	virtual bool move(char x_, char y_) = 0;
};

#endif
