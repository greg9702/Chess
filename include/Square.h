#ifndef SQUARE_H
#define SQUARE_H

#include "Piece.h"

class Square {
private:
	char x;
	char y;
	Piece* occupator;
public:
	Square(char x_, char y_);
	~Square();
	Piece* getOccupator();
	void setOccupator(Piece* occupator_);
};

#endif
