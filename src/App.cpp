#include <iostream>
#include <string>
#include <algorithm>

#include "Board.h"
#include "Enums.h"
#include "Bishop.h"

using namespace std;

class App {
};

int main(){
    /*
     * Write moves, emty string ends
     */
    Board chessBoard;
    auto mt = chessBoard.getMatrix();
    for (auto& x : mt){
        cout << x.first.first << ", " << x.first.second << ": ";
        if (x.second->getOccupator() != nullptr)
            cout << x.second->getOccupator()->getType();
        cout << endl;
    }
    string instruction;
    cout << "White to move." << endl;
    getline(cin,instruction);
    while (!instruction.empty()){
        if (chessBoard.move(instruction)){
            cout << "History " << chessBoard.getHistory() << endl;
        } else{
            cout << "Invalid move. Try again.";
        }
        if (chessBoard.getTurn() == WHITE)
            cout << "White to move." << endl;
        else
            cout << "Black to move." << endl;
        getline(cin,instruction);
    }
    return 0;
}
