#include <arpa/inet.h>
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "lst_timer.h"

enum { FD_LIMIT = 65535,
       MAX_EVENT_NUMBER = 1024,
       TIMEOUT = 5 };

static int pipefd[2];

static sort_timer_lst timer_lst;
static int epollfd = 0;

int setNonblocking(int fd) {
    int old_option = fcntl(fd, F_SETFL);
    int new_option = fcntl(fd, F_SETFL, old_option | O_NONBLOCK);
    return old_option;
}

void addFd(int epollfd, int fd) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setNonblocking(fd);
}

void sigHandler(int sig) {
    int save_errno = errno;
    int msg = sig;
    send(pipefd[1], (char*)&msg, 1, 0);
    errno = save_errno;
}