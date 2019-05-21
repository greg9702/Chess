#include "Board.h"

Board::Board() {
    /**
     * Parameterless constructor, initializes table with all pieces
     */
}

Board::~Board() {
    /**
     * Destructor
     */
}

bool Board::isCheck() {
    /**
     * Checks if there was check.
     * @return true if there was check, false otherwise
     */
    return false;
}

bool Board::move(std::string instruction) {
    /**
     * Moves piece like said in the instruction
     * @param instruction next move in chess notation
     * @return true if the move was successfully performed, false otherwise
     */
    return false;
}

std::string Board::getHistory() {
    /**
     * Getter of history
     * @return history of the chess game, using standard chess notation
     */
    return std::__cxx11::string();
}

std::map<std::pair<char, char>, Square> Board::getMatrix() {
    /**
     * Getter of matrix
     * @return map containing indexes of squares and object Square describing the square
     */
    return std::map<std::pair<char, char>, Square>();
}

color Board::getTurn() {
    /**
     * Getter of turn
     * @return if black or white is about to move
     */
    return BLACK;
}
