#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include "lnp.h"

static char buf[4096];

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(atoi(argv[1]));

    Bind(sockfd, (struct sockaddr*)&addr, sizeof addr);

    Listen(sockfd, LISTENQ);

    int fd = Accept(sockfd, NULL, NULL);

    for (;;) {
        ssize_t n = Read(fd, buf, sizeof buf);

        if (n == 0) {
            close(fd);
            break;
        }

        Writen(fd, buf, n);
    }

    close(sockfd);

    return 0;
}