#ifndef SQUARE_H
#define SQUARE_H

class Square {
private:
	char x;
	char y;
	Piece occupator;
public:
	Square(Piece& Piece_, );
	Square& getOccupator();
	void setOccupator(Square& occupator_);

};

#endif
