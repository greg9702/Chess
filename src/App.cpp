#include <iostream>
#include <string>
#include <algorithm>

#include "Board.h"
#include "Enums.h"
#include "Bishop.h"

using namespace std;

class App {
};

void showBoard(Board* chessBoard) {

    std::map<std::pair<char, char>, Square*> mt = chessBoard->getMatrix();

    for (char a = '8'; a >= '1'; a--) {
        for (char b = 'a'; b <= 'h'; b++) {
            if (mt.at(std::pair<char, char>(b, a))->getOccupator() == nullptr) {
                std::cout << "x" << " ";
            } else {
                std::cout << mt.at(std::pair<char, char>(b, a))->getOccupator()->getType() << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main(){
    /*
     * Write moves, emty string ends
     */

    Board chessBoard;
    string instruction;
    cout << "White to move." << endl;
    getline(cin,instruction);
    std::cout << "\033[2J";
    showBoard(&chessBoard);
    while (!instruction.empty()){
        std::cout << "\033[2J";
        if (chessBoard.move(instruction)){
            cout << "History " << chessBoard.getHistory() << endl;
        } else{
            cout << "Invalid move. Try again.";
        }
        if (chessBoard.getTurn() == WHITE)
            cout << "White to move." << endl;
        else
            cout << "Black to move." << endl;


        showBoard(&chessBoard);
        getline(cin,instruction);

    }
    return 0;
}
