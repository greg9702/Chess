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
#include <cstdlib>

#define PORT 4444

void printVectorContent(const std::vector<std::pair<char *, unsigned short>> &users);

void killBoardServers();

std::string prepareMessageForClient(const std::pair<char *, unsigned short> &user);

std::basic_string<char> getAddress(const std::pair<char *, unsigned short> &user);

std::string getPort(const std::pair<char *, unsigned short> &user);

bool arePlayersToPair(const std::vector<std::pair<char *, unsigned short>> &users);

std::string getCommandRunningSingleGame(int board_port, const std::string &white_port, const std::string &black_port);

void runCommand(const std::string &command);

int main() {
    killBoardServers();

    int sockfd, ret;
    struct sockaddr_in serverAddr;

    int newSocket, newSocket2;
    struct sockaddr_in newAddr;

    socklen_t addr_size;

    char buffer[1024];
    pid_t childpid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
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

    ret = bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (ret < 0) {
        printf("[-]Error in binding.\n");
        return 1;
    }
    printf("[+]Bind to port %d\n", 4444);

    if (listen(sockfd, 10) == 0) {
        printf("[+]Listening....\n");
    } else {
        printf("[-]Error in binding.\n");
    }

//    int prevSocket;
    std::vector<std::pair<char *, short unsigned int>> users;
    int board_port = 5000;

    while (1) {
        newSocket = accept(sockfd, (struct sockaddr *) &newAddr, &addr_size);
        std::pair<char *, unsigned short> current_user = std::make_pair(inet_ntoa(newAddr.sin_addr),
                                                                        ntohs(newAddr.sin_port));
        users.push_back(current_user);

        if (newSocket < 0) {
            return 1;
        }
        std::string messageToClient = prepareMessageForClient(current_user);
        if(!arePlayersToPair(users)) {
            messageToClient.append("Wait for second player...\n");
        }

        send(newSocket, messageToClient.c_str(), strlen(messageToClient.c_str()), 0);
        close(newSocket);

//        TODO żeby zamykać później gniazdo, dopiero jak znajdzie partnera do gry
//        prevSocket = newSocket;

        printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
//        printVectorContent(users);
        if (arePlayersToPair(users)) {

//            close(prevSocket);
            if ((childpid = fork()) == 0) {
                close(sockfd);
                std::string white_port = getPort(users.at(0));
                std::string black_port = getPort(users.at(1));
                std::cout << "white port: " << white_port
                          << " black port: " << black_port
                          << " server port: " << board_port << std::endl;
                std::string command = getCommandRunningSingleGame(board_port, white_port, black_port);
                runCommand(command);
            }
            users.clear();
            board_port++;
        }
    }

    return 0;
}

void runCommand(const std::string &command) { system(command.c_str()); }

std::string getCommandRunningSingleGame(int board_port, const std::string &white_port, const std::string &black_port) {
    std::string command = "../run.sh " + std::to_string(board_port) + " " +
                          white_port + " " + black_port;
    return command;
}

bool arePlayersToPair(const std::vector<std::pair<char *, unsigned short>> &users) { return users.size() % 2 == 0; }

std::string prepareMessageForClient(const std::pair<char *, unsigned short> &user) {
    std::string messageToClient = "Open your browser http://" +
                                  getAddress(user) +
                                  ":" +
                                  getPort(user) +
                                  " to play chess\n";
    return messageToClient;
}

std::string getPort(const std::pair<char *, unsigned short> &user) { return std::to_string(user.second); }

std::basic_string<char> getAddress(const std::pair<char *, unsigned short> &user) { return std::string(user.first); }

void killBoardServers() { system("killall chess"); }

void printVectorContent(const std::vector<std::pair<char *, unsigned short>> &users) {
    for (auto i : users)
        std::cout << i.first << " " << i.second << std::endl;
}