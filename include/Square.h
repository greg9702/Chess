


class Square {
private:
	char x;
	char y;
	Figure occupator;
public:
	Square(Figure& figure_, );
	Square& getOccupator();
	void setOccupator(Square& occupator_);
	
};
