#include "Queen.h"
#include "Square.h"
#include "Board.h"

Queen::Queen(color col_, Board* board_, Square* square_) : Piece(col_, board_, square_) {
    this->type = QUEEN;
}

Queen::~Queen() {

}


bool Queen::isPossible(char x_, char y_) {

    if (!(this->isCorrect(x_, y_))) {
        return  false;
    }
    std::pair<char, char> current_pos = this->square->getCoords();

    if (this->board->getPieceByCoord(x_,y_) != nullptr && this->board->getPieceByCoord(x_,y_)->getColor() == this->col)
        return false;
    //horizontal movement
    if (x_ == this->square->getCoords().first){
        char target = this->square->getCoords().second;
        // beg, fin - range of squares to check if there is something
        char beg = target > y_ ? y_+1 : target+1;
        char fin = target > y_ ? target-1 : y_-1;
        for (char i = beg; i < fin; ++i){
            if (this->board->getPieceByCoord(x_,i) != nullptr)
                return false;
        }
    }
    //vertical movement
    if (y_ == this->square->getCoords().second){
        char target = this->square->getCoords().first;
        char beg = target > x_ ? x_+1 : target+1;
        char fin = target > x_ ? target-1 : x_-1;
        for (char i = beg; i<fin; ++i){
            if (this->board->getPieceByCoord(i,y_) != nullptr)
                return false;
        }
    }

    // diagonally movement
    for (int i = 1; i < abs(x_ - current_pos.first); i++) {
        std::cout << "i: " << i << std::endl;
        if (current_pos.first > x_ && current_pos.second > y_) { // figure move left down
            if (this->board->getMatrix().at(std::pair<char, char>(current_pos.first - i, current_pos.second - i))->getOccupator() != nullptr) {
                return false;
            }
        }
        if (current_pos.first > x_ && current_pos.second < y_) { // figure move top left
            if (this->board->getMatrix().at(std::pair<char, char>(current_pos.first - i, current_pos.second + i))->getOccupator() != nullptr) {
                return false;
            }
        }
        if (current_pos.first < x_ && current_pos.second > y_) { // figure move down right
            if (this->board->getMatrix().at(std::pair<char, char>(current_pos.first + i, current_pos.second - i))->getOccupator() != nullptr) {
                return false;
            }
        }
        if (current_pos.first < x_ && current_pos.second < y_) { //figure move top right
            std::cout << "Move right top" << std::endl;
            if (this->board->getMatrix().at(std::pair<char, char>(current_pos.first + i, current_pos.second + i))->getOccupator() != nullptr) {
                return false;
            }
        }
    }
    // check if last field is occupated by figure, if its your figure move is invalid, if not it is correct
    if (this->board->getMatrix().at(std::pair<char, char>(x_, y_))->getOccupator() != nullptr) {
        if (this->board->getMatrix().at(std::pair<char, char>(x_, y_))->getOccupator()->getColor() == this->col) {
            return false;
        }
    }

    return true;

}

bool Queen::isCorrect(char x_, char y_) {
    std::pair<char, char> current_pos = this->square->getCoords();

    if ((x_ == current_pos.first) == (y_ == current_pos.second)) {
        if (abs((y_ - current_pos.second) != abs(x_ - current_pos.first))) {
            return false;
        }
    }
    return true;
}
