#include        <sys/types.h>   /* basic system data types */
#include        <sys/socket.h>  /* basic socket definitions */
#include        <sys/time.h>    /* timeval{} for select() */
#include        <time.h>                /* timespec{} for pselect() */
#include        <netinet/in.h>  /* sockaddr_in{} and other Internet defns */
#include        <arpa/inet.h>   /* inet(3) functions */
#include        <errno.h>
#include        <fcntl.h>               /* for nonblocking */
#include        <netdb.h>
#include        <signal.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include    <netinet/tcp.h>        /* for TCP_MAXSEG */
#include        <unistd.h>


#define SA      struct sockaddr
#define MAXLINE 2048

int
main(int argc, char **argv) {
    int sockfd, ipttl, mss;
    socklen_t len;
    struct sockaddr_in servaddr;
    char recvline[MAXLINE + 1];
    int err, n;
    struct timeval start, stop;

    if (argc != 2) {
        fprintf(stderr, "ERROR: usage: %s <IPv4 address>\n", argv[0]);
        return 1;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "socket error : %s\n", strerror(errno));
        return 1;
    }

//#define IP_TTL_SET
#ifdef IP_TTL_SET
    ipttl = 32;
    if( setsockopt(sockfd, SOL_IP, IP_TTL, &ipttl, sizeof(ipttl)) == -1){
        fprintf(stderr,"setsockopt error : %s\n", strerror(errno));
        return 1;
    }
#endif

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(4444);        /* daytime server */
    int er;
    if ((er = inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) == -1) {
        fprintf(stderr, "inet_pton error : %s\n", strerror(errno));
        return 1;
    } else if (er = 0) {
        printf("Addres error \n");
        return 1;
    }

    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) == -1) {
        fprintf(stderr, "connect: %s\n", strerror(errno));
        return 1;
    }


    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;    /* null terminate */
        if (fputs(recvline, stdout) == EOF) {
            fprintf(stderr, "fputs error : %s\n", strerror(errno));
            return 1;
        }
    }
    if (n < 0)
        fprintf(stderr, "read error : %s\n", strerror(errno));

    fflush(stdout);
    exit(0);
}
