#ifndef PIECE_H
#define PIECE_H

class Board;
class Square;

#include <memory>
#include "Enums.h"

class Piece{
protected:
	color col;
	Piece_type type;
	std::shared_ptr<Board> board;
	std::shared_ptr<Square> square;
	virtual bool isCorrect() = 0;
	virtual bool isPossible() = 0;
public:
	Piece(color col_, std::shared_ptr<Board> & board_, std::shared_ptr<Square> & square_);
	~Piece();
	virtual bool move(char x_, char y_) = 0;
};

#endif
