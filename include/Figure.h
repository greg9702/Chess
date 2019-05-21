enum figure_type {
		PAWN,
		ROOK,
		KNIGHT,
		BISHOP,
		QUEEN,
		KING
};

class Figure {
private:
	color color;
	figure_type type;
	Board& board;
	Square& square;
	virtual bool isCorrect() = 0;
	virtual bool isPossible() = 0;
public:
	Figure();
	~Figure();
	virtual bool move(char x_, char y_) = 0;
}
