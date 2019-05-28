#ifndef SQUARE_H
#define SQUARE_H

#include <utility>
#include "Piece.h"

class Square {
private:
	char x;
	char y;
	Piece* occupator;
	color col;
	bool en_passant_flag;
public:
	Square(char x_, char y_);
	~Square();
	Piece* getOccupator();
	void setOccupator(Piece* occupator_);
	std::pair<char, char> getCoords();
	color getColor();
    bool getEnPassant();
    void setEnPassant(bool en_pass);
};

#endif
