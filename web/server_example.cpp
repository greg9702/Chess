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

#define MAXLINE 1024

//#define SA struct sockaddr

#define LISTENQ 2

int
main(int argc, char **argv)
{
    Board * chess_board = new Board();
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
        // buff is 1024 size array and keep trash elements when data is shorter

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


        if (chess_board->move(recived_move)) {
            snprintf(buff, sizeof(buff), "%s", "true");						// there we would send response from
            if( write(connfd, buff, strlen(buff))< 0 )
                fprintf(stderr,"write error : %s\n", strerror(errno));
        } else {
            snprintf(buff, sizeof(buff), "%s", "false");						// there we would send response from
            if( write(connfd, buff, strlen(buff))< 0 )
                fprintf(stderr,"write error : %s\n", strerror(errno));
        }

        close(connfd);
    }
    delete chess_board;
}
