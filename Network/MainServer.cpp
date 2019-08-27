#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <iostream>

#define PORT 4444

void printVectorContent(const std::vector<std::pair<char *, unsigned short>> &users);

int main(){

    int sockfd, ret;
    struct sockaddr_in serverAddr;

    int newSocket, newSocket2;
    struct sockaddr_in newAddr;

    socklen_t addr_size;

    char buffer[1024];
    pid_t childpid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        printf("[-]Error in connection.\n");
        return 1;
    }
    printf("[+]Server Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

#define REUSEADDR
#ifdef REUSEADDR
    int sndbuf = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sndbuf, sizeof(sndbuf)) < 0) {
        fprintf(stderr, "SO_REUSEADDR setsockopt error : %s\n", strerror(errno));
    }
#endif

    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret < 0){
        printf("[-]Error in binding.\n");
        return 1;
    }
    printf("[+]Bind to port %d\n", 4444);

    if(listen(sockfd, 10) == 0){
        printf("[+]Listening....\n");
    }else{
        printf("[-]Error in binding.\n");
    }
    std::vector<std::pair<char*, short unsigned int>> users;

    int board_port = 8001;


    while(1){
        newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
        users.push_back(std::make_pair(inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port)));

        if(newSocket < 0){
            return 1;
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
        printVectorContent(users);
        if (users.size() % 2 == 0) {
//      STARTUJEMY NOWY SERWER Z NOWYM PORTEM EFEMERYCZNYM
            int white_port = users[0].second;
            int black_port = users[1].second;
            std::cout << "white port: " << white_port
                      << " black port: " << black_port
                      << " server port: " << board_port << std::endl;
            char command[50];
            sprintf( command, "../run.sh %d", board_port );
            printf("%s", command);
//            system(command);
//            board_port++;

//      FORKI ITD
//            if((childpid = fork()) == 0){
//                close(sockfd);
//                printf("forked\n");
//
//                while(1){
//                    recv(newSocket, buffer, 1024, 0);
//                    if(strcmp(buffer, ":exit") == 0){
//                        printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
//                        break;
//                    }else{
//                        printf("Client: %s\n", buffer);
//                        send(newSocket, buffer, strlen(buffer), 0);
//                        bzero(buffer, sizeof(buffer));
//                    }
//                }
//            }

        }


    }

    close(newSocket);


    return 0;
}

void printVectorContent(const std::vector<std::pair<char *, unsigned short>> &users) {
    for (auto i : users)
        std::cout << i.first << " " << i.second << std::endl;
}