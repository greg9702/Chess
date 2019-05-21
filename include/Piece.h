#ifndef PIECE_H
#define PIECE_H

enum Piece_type {
		PAWN,
		ROOK,
		KNIGHT,
		BISHOP,
		QUEEN,
		KING
};

class Piece{
private:
	color color;
	Piece_type type;
	Board& board;
	Square& square;
	virtual bool isCorrect() = 0;
	virtual bool isPossible() = 0;
public:
	Piece();
	~Piece();
	virtual bool move(char x_, char y_) = 0;
}

#endif
