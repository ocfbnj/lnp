#ifndef LNP_H
#define LNP_H

#include <sys/socket.h>
#include <sys/types.h>

#define LISTENQ 1024

#ifdef __cplusplus
extern "C" {
#endif

// error handling functions.
void err_sys(const char* str);
void err_quit(const char* str);

// wrapper functions.
int Socket(int domain, int type, int protocol);
int Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
int Accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);
ssize_t Read(int fd, void* buf, size_t count);
ssize_t Writen(int fd, const void* buf, size_t count);

// custom functions.
ssize_t readn(int fd, void* buf, size_t count);
ssize_t writen(int fd, const void* buf, size_t count);

#ifdef __cplusplus
}
#endif

#endif
