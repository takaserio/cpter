// https://www.linuxhowtos.org/C_C++/socket.htm
// This tutorial that explains how to use sockets is nice.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

// the header file define Info struct
//#include "../../lib/infomation.h"
#include "getinfo.c"

void error(char *msg) {
    printf("%s", msg);
    exit(1);
}

int build_socket() {
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR: opening socket");

    return sockfd;
}

void bind_socket(int portno, int sockfd) {
    struct sockaddr_in serv_addr;

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("ERROR: on binding");
}

void wrap_write(char *msg, int newsockfd) {
    int status;
    status = write(newsockfd, msg, strlen(msg));
    if (status < 0) error("ERROR: writing to socket");
}

void wrap_read(int newsockfd) {
    char *buffer[256];
    int status;

    bzero(buffer, 256);
    status = read(newsockfd, buffer, 255);
    if (status < 0) error("ERROR: reading from socket");
}

int main() {
    int sockfd, newsockfd, clilen, n;
    char buffer[256];
    struct sockaddr_in cli_addr;
    int port = PORT;

    // building a socket and bind it.
    sockfd = build_socket();
    bind_socket(port, sockfd);
    listen(sockfd, 5);

    // accept connections
    clilen = sizeof(cli_addr);
    
    printf("Waiting for reqests...\n");
    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) error("ERROR: on accept");

        // by using newsockfd the sockfd can communicate with it.
        // write what to do with the client below.

        printf("!!Connection has been established!!\n");
        //printf("ip addr: %s", cli_addr.sin_addr);

        // get infomation
        struct Info info;
        getinfo(&info);

        printf("Fetching infomation...");

        // send data
        write(newsockfd, &info, sizeof(struct Info));

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}