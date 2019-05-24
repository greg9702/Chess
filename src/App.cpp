#include <algorithm>
#include <iostream>
#include <string>

#include "Bishop.h"
#include "Board.h"
#include "Enums.h"

using namespace std;

class App {};

void showBoard(Board *chessBoard) {

  std::map<std::pair<char, char>, Square *> mt = chessBoard->getMatrix();
  int i = 8;
  for (char a = '8'; a >= '1'; a--) {
    std::cout << i << "| ";
    i--;
    for (char b = 'a'; b <= 'h'; b++) {
      if (mt.at(std::pair<char, char>(b, a))->getOccupator() == nullptr) {
        std::cout << "-"
                  << "  ";
      } else {
		  if (mt.at(std::pair<char, char>(b, a))->getOccupator()->getColor() == WHITE)
		  {
			  std::cout
				  << mt.at(std::pair<char, char>(b, a))->getOccupator()->getType()
				  << "  ";
		  }
		  else {
			  std::cout
				  << mt.at(std::pair<char, char>(b, a))->getOccupator()->getType()
				  << "* ";
		  }
      }
    }
    std::cout << std::endl;
  }
  std::cout << "   ";
  for (char a = 'a'; a <= 'h'; a++) {
    std::cout << a << "  ";
  }
  std::cout << std::endl;
}

int main() {
  /*
   * Write moves, emty string ends
   */

  Board chessBoard;
  string instruction = "";

  while (instruction != "0") {
      showBoard(&chessBoard);
      game_state gs = chessBoard.getGameState(chessBoard.getTurn());
      if (gs == STALE_MATE) {
          std::cout << "IT'S STALEMATE! DRAW\n";
          break;
      }
      if (chessBoard.getTurn() == WHITE){
          if (gs == CHECK_MATE){
              std::cout << "IT'S CHECK MATE! BLACK WINS.";
              break;
          }
      }
      if (chessBoard.getTurn() == BLACK){
          if (gs == CHECK_MATE){
              std::cout << "IT'S CHECK MATE! WHITE WINS.";
              break;
          }
      }

    if (chessBoard.getTurn() == WHITE)
      cout << "White turn" << endl;
    else
      cout << "Black turn" << endl;

    getline(cin, instruction);

    if (chessBoard.move(instruction)) {
      //            cout << "History " << chessBoard.getHistory() << endl;
    } else {
      cout << "Invalid move. Try again." << std::endl;
    }

  }
  return 0;
}
