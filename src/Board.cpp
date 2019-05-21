#include <assert.h>
#include "Board.h"

Board::Board() {
    /**
     * Parameterless constructor, initializes table with all pieces
     */
    turn = WHITE;
    game_s = NORMAL;
    for (char tmp_y = '1'; tmp_y <= '8'; ++tmp_y) {
            for (char tmp_x='a';tmp_x<='h';++tmp_x) {
                matrix.insert(std::pair<std::pair<char, char>, Square>(std::make_pair(tmp_x, tmp_y), Square(tmp_x, tmp_y)));
        }
    }
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
    return game_s == CHECK || game_s == CHECK_MATE;
}

bool Board::move(std::string instruction) {
    /**
     * Moves piece like said in the instruction
     * @param instruction next move in chess notation
     * @return true if the move was successfully performed, false otherwise
     */
     // TO DO roszada

     assert(instruction.size() > 2);
     char dest_x, char dest_y
    // figure move
    if (isupper(instruction.at(0))){
        assert(instruction.size()==3);
        dest_x = instruction.at(1);
        dest_y = instruction.at(2);
     }
     else{
        assert(instruction.size()==2);
        dest_x = instruction.at(0);
        dest_y = instruction.at(1);
    }

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
    return matrix;
}

color Board::getTurn() {
    /**
     * Getter of turn
     * @return if black or white is about to move
     */
    return BLACK;
}
