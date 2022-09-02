/**
 * 服务器程序
 * 示例：超时接收服务器数据，超时时间例程中设置为10秒
 * 编译： $ gcc timeout_recv_server.c -o server
 * 运行方式：
 * $ ./server
 * 默认监听端口8001（根据实际情况修改）
 * 服务器功能：从键盘接收用户输入，每接收一行就向客户输出一行。如果没有用户输入，
 * 则阻塞。
 * 客户端需要跟服务器安装在同一网段上，为了测试方便，就直接都安装到同一机器上
 */
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> /* See NOTES */
#include <unistd.h>

int sockfd = -1;

void sig_func(int sig_no) {
    if (sig_no == SIGINT || sig_no == SIGTERM) {
        if (sockfd >= 0) {
            close(sockfd);
        }
        exit(1);
    }
}

int main() {
    struct sockaddr_in servaddr, cliaddr;
    int listenfd;

    signal(SIGINT, sig_func);

    printf("server start...\n");

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }
    sockfd = listenfd;

    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        perror("setsocketopt error");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8001);

    if (bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind error");
        exit(1);
    }

    if (listen(listenfd, 5) < 0) {
        perror("listen error");
        exit(1);
    }

    char buf[1024];
    socklen_t clilen = sizeof(cliaddr);
    int connfd;

    if ((connfd = accept(listenfd, nullptr, nullptr)) < 0) {
        perror("accept error");
        exit(1);
    }

    printf("input a line string: \n");
    int nbytes;
    while (fgets(buf, sizeof(buf), stdin)) {
        nbytes = send(connfd, buf, strlen(buf), 0);
        if (nbytes < 0) {
            perror("send error");
            break;
        } else if (nbytes == 0) {
        }
        printf("send: %s\n", buf);
    }

    close(connfd);
    close(listenfd);

    return 0;
}