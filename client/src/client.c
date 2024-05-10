// https://www.linuxhowtos.org/C_C++/socket.htm
// This tutorial that explain how to use sockets is nice.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include "../../lib/infomation.h"

void error(char *msg) {
    printf(msg);
    exit(1);
}

int build_socket() {
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR: opening socket");

    return sockfd;
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    struct Info info;

    if (argc < 3) {
        printf("usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = build_socket();

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        printf("ERROR: no such host\n");
        exit(0);
    }
      
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("ERROR: connecting");

    printf("!!Connection has been established!!\n");
    n = read(sockfd, &info, sizeof(struct Info));
    if (n < 0) error("ERROR: reading from socket");

    printf("CPU: %s\n", info.cpu.cpu_name);

    close(sockfd);
    return 0;
}