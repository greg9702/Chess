

#include <algorithm>
#include <iostream>
#include <string>

#include "Bishop.h"
#include "Board.h"
#include "Enums.h"
#include "Board.h"

#include        <sys/types.h>   /* basic system data types */
#include        <sys/socket.h>  /* basic socket definitions */
#include 		<unistd.h>
#if TIME_WITH_SYS_TIME
#include        <sys/time.h>    /* timeval{} for select() */
#include        <time.h>                /* timespec{} for pselect() */
#else
#if HAVE_SYS_TIME_H
#include        <sys/time.h>    /* includes <time.h> unsafely */
#else
#include        <time.h>                /* old system? */
#endif
#endif
#include        <netinet/in.h>  /* sockaddr_in{} and other Internet defns */
#include        <arpa/inet.h>   /* inet(3) functions */
#include        <errno.h>
#include        <fcntl.h>               /* for nonblocking */
#include        <netdb.h>
#include        <signal.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include		<unistd.h>
#include 		<iostream>
#include 		<string>

void showBoard(Board *chessBoard) {

    std::map<std::pair<char, char>, Square *,MyComparator> mt = chessBoard->getMatrix();

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

#define MAXLINE 2048


//#define SA struct sockaddr

#define LISTENQ 2

int
main(int argc, char **argv)
{
    Board chess_board = Board();
    int				listenfd, connfd;
    socklen_t			len;
    char				buff[MAXLINE], str[INET6_ADDRSTRLEN+1];
    time_t				ticks;
    struct sockaddr_in6	servaddr, cliaddr;

    if ( (listenfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0){
        fprintf(stderr,"socket error : %s\n", strerror(errno));
        return 1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_addr   = in6addr_any;
    servaddr.sin6_port   = htons(8001);	/* daytime server */

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &buff, sizeof(buff)) < 0){
        fprintf(stderr,"SO_REUSEADDR setsockopt error : %s\n", strerror(errno));
    }

    if ( bind( listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        fprintf(stderr,"bind error : %s\n", strerror(errno));
        return 1;
    }

    if ( listen(listenfd, LISTENQ) < 0){
        fprintf(stderr,"listen error : %s\n", strerror(errno));
        return 1;
    }

    for ( ; ; ) {
        len = sizeof(cliaddr);
        if ( (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len)) < 0){
            fprintf(stderr,"accept error : %s\n", strerror(errno));
            continue;
        }

        bzero(str, sizeof(str));
        inet_ntop(AF_INET6, (struct sockaddr  *) &cliaddr.sin6_addr,  str, sizeof(str));
        printf("Connection from %s\n", str);

        int ret;
        std::string recived_move = "";
        if ((ret = read(connfd, buff, sizeof(buff)-1)) > 0) {
            buff[ret] = 0x00;
            printf("block read: \n%s\n", buff);
            std::cout << "BUFFER" << std::endl;
            for (int i = 0; i < ret; i++) {
                recived_move += buff[i];
            }
        }
        // buff is MAXLINE size array and keep trash elements when data is shorter

        // recived_move keeps only valuable data and is std::string
        std::cout << "recived move string: " << recived_move << std::endl;

        // std::string response = "";
        // // if (moveBoard(recived_move) == false) { // in final version
        // if (buff == "b4") {				// for debug purpose
        // 	response = "wrong";
        // } else {
        // 	response = "true";
        // }

        // Simulation of moveBoard() function

        //showBoard(&chess_board);

        std::string info_to_front = "";
        game_state gs;

        if (recived_move.size() == 4 || recived_move.size() == 5){
            for (int i=0;i<3;i+=2) {
                if (recived_move.at(i) < 'a' || recived_move.at(i) > 'h' ||
                    recived_move.at(i+1) < '1' || recived_move.at(i+1) > '8')

                    info_to_front = "0;0;";

            }
        }
        if (info_to_front != "0;0;") {
            //  correct move
            if (chess_board.move(recived_move)) {
                info_to_front += "1;";
            } else {
                info_to_front += "0;";
            }


            // GAMESTATE
            gs = chess_board.getGameState(chess_board.getTurn());
            switch (gs) {
                case NORMAL:
                    info_to_front += "0;";
                    break;
                case CHECK:
                    if (chess_board.getTurn() == WHITE)
                        info_to_front += "1;";
                    else
                        info_to_front += "3;";
                    break;
                case CHECK_MATE:
                    if (chess_board.getTurn() == WHITE)
                        info_to_front += "2;";
                    else
                        info_to_front += "4;";
                    break;
                case STALE_MATE:
                    info_to_front += "5;";
            }
        }
        //COLOR TO MOVE
        if (gs == CHECK_MATE || gs == STALE_MATE)
            info_to_front += "2;";
        else {
            if (chess_board.getTurn() == WHITE)
                info_to_front += "0;";
            else
                info_to_front += "1;";
        }

        std::string colorTable[] = {"white","black"};
        std::string pieceTable[] = {"Pawn","Rook","Knight","Bishop","Queen","King"};
        std::string whiteCodeTable[] = {"#9817","#9814","#9816","#9815","#9813","#9812"};
        std::string blackCodeTable[] = {"#9823","#9820","#9822","#9821","#9819","#9818"};


        auto squares = chess_board.getMatrix();
        for (auto sq : squares){
            info_to_front += colorTable[sq.second->getColor()] + ",";
            if (sq.second->getOccupator() == nullptr){
                info_to_front += ",,";
            }
            else {
                info_to_front += colorTable[sq.second->getOccupator()->getColor()] + ",";
                info_to_front += pieceTable[sq.second->getOccupator()->getType()] + ",";
            }
            info_to_front.append(1,sq.first.first);
            info_to_front.append(1,sq.first.second);
            info_to_front += ",";
            if (sq.second->getOccupator() == nullptr){
                info_to_front += ";";
            }
            else {
                if (sq.second->getOccupator()->getColor() == WHITE)
                    info_to_front += whiteCodeTable[sq.second->getOccupator()->getType()] + ";";
                else
                    info_to_front += blackCodeTable[sq.second->getOccupator()->getType()] + ";";
            }
        }
        info_to_front = info_to_front.substr(0,info_to_front.size()-1);

        //std::cout << info_to_front << std::endl;

        snprintf(buff, sizeof(buff), "%s", info_to_front.c_str());						// there we would send response from
        if( write(connfd, buff, strlen(buff))< 0 )
            fprintf(stderr,"write error : %s\n", strerror(errno));

        close(connfd);
    }
}


/*
using namespace std;

class App {};






int main() {
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

*/
