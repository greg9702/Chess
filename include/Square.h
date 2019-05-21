#ifndef SQUARE_H
#define SQUARE_H

#include <memory>
#include "Piece.h"

class Square {
private:
	char x;
	char y;
	std::shared_ptr<Piece> occupator;
public:
	Square(char x_, char y_);
	~Square();
	std::shared_ptr<Piece> getOccupator();
	void setOccupator(std::shared_ptr<Piece> occupator_);
};

#endif
