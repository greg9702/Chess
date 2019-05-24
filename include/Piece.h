#ifndef PIECE_H
#define PIECE_H

class Board;
class Square;

#include "Enums.h"
#include <iostream>
#include <vector>

class Piece{
    friend class King;
    friend class Board;
protected:
	color col;
	Piece_type type;
	Board* board;
	Square* square;
    bool first_move_made;
	virtual bool isCorrect(char x_, char y_) = 0;
public:
	Piece(color col_, Board* board_, Square* square_);
	virtual ~Piece();
    virtual bool isPossible(char x_, char y_) = 0;
	virtual bool move(char x_, char y_,special_args add_opt=NONE);
	color getColor();
	Piece_type getType();
	Square * getSquare();
	bool isStarting();
};

#endif
