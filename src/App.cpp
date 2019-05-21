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
    string instruction;
    cout << "White to move.\n";
    getline(cin,instruction);
    while (!instruction.empty()){
        if (chessBoard.move(instruction)){
            cout << chessBoard.getHistory();
        } else{
            cout << "Invalid move. Try again.";
        }
        if (chessBoard.getTurn() == WHITE)
            cout << "White to move.\n";
        else
            cout << "Black to move.\n";
        getline(cin,instruction);
    }

    return 0;
}
