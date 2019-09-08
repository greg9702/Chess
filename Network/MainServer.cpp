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
#include <sys/signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <experimental/filesystem>

#define PORT 4444

void printVectorContent(const std::vector<std::pair<char *, unsigned short>> &users);

void killBoardServersAndClients();

std::string prepareMessageForClient(const std::pair<char *, unsigned short> &user);

std::basic_string<char> getAddress(const std::pair<char *, unsigned short> &user);

std::string getPort(const std::pair<char *, unsigned short> &user);

bool arePlayersToPair(const std::vector<std::pair<char *, unsigned short>> &users);

std::string getCommandRunningSingleGame(const std::string &path_to_build, int board_port, const std::string &white_port,
                                        const std::string &black_port);

void runCommand(const std::string &command);

#define    MAXFD    64

int daemon_init(const char *pname, int facility, uid_t uid, int socket, std::string &path_to_build) {
    int i, p;
    pid_t pid;

    if (uid < 0)
        return -1;

    if ((pid = fork()) < 0)
        return (-1);
    else if (pid)
        exit(0);            /* parent terminates */

    /* child 1 continues... */

    if (setsid() < 0)            /* become session leader */
        return (-1);

    signal(SIGHUP, SIG_IGN);
    if ((pid = fork()) < 0)
        return (-1);
    else if (pid)
        exit(0);            /* child 1 terminates */

    /* child 2 continues... */
    path_to_build = std::experimental::filesystem::current_path();
    chdir("/tmp");                /* change working directory  or chroot()*/
//	chroot("/tmp");

    /* close off file descriptors */
    for (i = 0; i < MAXFD; i++) {
        if (socket != i)
            close(i);
    }

    /* redirect stdin, stdout, and stderr to /dev/null */
    p = open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);

    openlog(pname, LOG_PID, facility);

    syslog(LOG_ERR, " STDIN =   %i\n", p);
    syslog(LOG_NOTICE, "Program started by User %d", getuid());
    setuid(uid); /* change user */

    return (0);                /* success */
}
//----------------------

int main(int argc, char **argv) {
    killBoardServersAndClients();

    int sockfd, ret;
    struct sockaddr_in serverAddr;

    int newSocket, newSocket2;
    struct sockaddr_in newAddr;

    socklen_t addr_size;

    char buffer[1024];
    pid_t childpid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    std::string path_to_build;
    daemon_init("CHESS MAIN SERVER", LOG_LOCAL7, 1000, sockfd, path_to_build);
    if (sockfd < 0) {
        syslog (LOG_ERR, "Error in connection.\n");
        return 1;
    }
    syslog (LOG_INFO, "Server Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

#define REUSEADDR
#ifdef REUSEADDR
    int sndbuf = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sndbuf, sizeof(sndbuf)) < 0) {
        syslog (LOG_ERR, "SO_REUSEADDR setsockopt error : %s\n", strerror(errno));
    }
#endif

    ret = bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (ret < 0) {
        syslog (LOG_ERR, "Error in binding.\n");
        return 1;
    }
    syslog (LOG_INFO, "Bind to port %d\n", 4444);

    if (listen(sockfd, 10) == 0) {
        syslog (LOG_INFO, "Listening....\n");
    } else {
        syslog (LOG_INFO, "Error in binding.\n");
    }
    syslog(LOG_INFO, "Waiting for clients ... ");

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
        if (!arePlayersToPair(users)) {
            messageToClient.append("Wait for second player...\n");
        }

        send(newSocket, messageToClient.c_str(), strlen(messageToClient.c_str()), 0);
        close(newSocket);

//        TODO żeby zamykać później gniazdo, dopiero jak znajdzie partnera do gry

        if (arePlayersToPair(users)) {
            if ((childpid = fork()) == 0) {
                close(sockfd);
                std::string white_port = getPort(users.at(0));
                std::string black_port = getPort(users.at(1));
                std::string white_addr = getAddress(users.at(0));
                std::string black_addr = getAddress(users.at(1));

                std::string command = getCommandRunningSingleGame(path_to_build, board_port, white_port, black_port);

                syslog(LOG_INFO, "White player: addr: %s, port: %s", white_addr.c_str(), white_port.c_str());
                syslog(LOG_INFO, "Black player: addr: %s, port: %s", black_addr.c_str(), black_port.c_str());
                syslog(LOG_INFO, "Local server: addr: %s, port: %i", "127.0.0.1", board_port);
                syslog(LOG_INFO, "Executed command: %s", command.c_str());

                runCommand(command);
            }
            users.clear();
            board_port++;
        }
    }
    return 0;
}

void runCommand(const std::string &command) { system(command.c_str()); }

std::string getCommandRunningSingleGame(const std::string &path_to_build, int board_port, const std::string &white_port,
                                        const std::string &black_port) {
    std::string command = path_to_build + "/../run_single_game.sh " + std::to_string(board_port) + " " +
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

void killBoardServersAndClients() {
    system("killall chess");
    system("killall python");
}

void printVectorContent(const std::vector<std::pair<char *, unsigned short>> &users) {
    for (auto i : users)
        std::cout << i.first << " " << i.second << std::endl;
}