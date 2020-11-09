#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "lnp.h"

void err_sys(const char* str) {
    fprintf(stderr, "%s: %s\n", str, strerror(errno));
    exit(1);
}

void err_quit(const char* str) {
    fprintf(stderr, "%s\n", str);
    exit(1);
}

int Socket(int domain, int type, int protocol) {
    int n;

    if ((n = socket(domain, type, protocol)) == -1) {
        err_sys("socket() error");
    }

    return n;
}

int Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
    int n;

    if ((n = bind(sockfd, addr, addrlen)) == -1) {
        err_sys("bind() error");
    }

    return n;
}

int Listen(int sockfd, int backlog) {
    int n;

    if ((n = listen(sockfd, backlog)) == -1) {
        err_sys("listen() error");
    }

    return n;
}

int Connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
    int n;

    if ((n = connect(sockfd, addr, addrlen)) == -1) {
        err_sys("connect() error");
    }

    return n;
}

int Accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen) {
    int n;

    if ((n = accept(sockfd, addr, addrlen)) == -1) {
        err_sys("accept() error");
    }

    return n;
}

ssize_t Read(int fd, void* buf, size_t count) {
    ssize_t n;

    if ((n = read(fd, buf, count)) == -1) {
        err_sys("read() error");
    }

    return n;
}

ssize_t Writen(int fd, const void* buf, size_t count) {
    ssize_t n;

    if ((n = writen(fd, buf, count)) == -1) {
        err_sys("write() error");
    }

    return n;
}

ssize_t readn(int fd, void* buf, size_t count) {
    size_t nleft = count;
    ssize_t nread = 0;
    const char* ptr = (const char*)buf;

    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) == -1) {
            if (nread < 0 && errno == EINTR) {
                nread = 0;
            } else {
                return -1;
            }
        }

        nleft -= nread;
        ptr += nread;
    }

    return count;
}

ssize_t writen(int fd, const void* buf, size_t count) {
    size_t nleft = count;
    ssize_t nwrite = 0;
    const char* ptr = (const char*)buf;

    while (nleft > 0) {
        if ((nwrite = write(fd, ptr, nleft)) == -1) {
            if (nwrite < 0 && errno == EINTR) {
                nwrite = 0;
            } else {
                return -1;
            }
        }

        nleft -= nwrite;
        ptr += nwrite;
    }

    return count;
}
