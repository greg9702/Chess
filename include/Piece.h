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
	virtual bool isCorrect(int x_, int y_) = 0;
	virtual bool isPossible(int x_, int y_) = 0;
public:
	Piece(color col_, Board* board_, Square* square_);
	~Piece();
	virtual bool move(char x_, char y_) = 0;
	color getColor();
	Piece_type getType();
};

#endif
