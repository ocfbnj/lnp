#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include "lnp.h"

static char buf[4096];

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <ipaddr> <port>\n", argv[0]);
        exit(1);
    }

    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &addr.sin_addr);

    Connect(sockfd, (struct sockaddr*)&addr, sizeof addr);

    for (;;) {
        if (fgets(buf, sizeof buf - 1, stdin) == NULL) {
            break;
        }

        Writen(sockfd, buf, strlen(buf));
        ssize_t n = Read(sockfd, buf, strlen(buf));

        if (n == 0) {
            break;
        }

        buf[n] = 0;
        fprintf(stdout, "%s", buf);
    }

    close(sockfd);

    return 0;
}