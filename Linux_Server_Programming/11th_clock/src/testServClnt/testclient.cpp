/**
 * 客户端程序
 * 示例：超时接收服务器数据，超时时间例程中设置为10秒
 * 编译： $ gcc timeout_recv_client.c -o client
 * 运行方式：
 * 如本地运行（对应服务器实际监听的IP地址和端口号） $ ./client 127.0.0.1 8001
 */
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> /* See NOTES */
#include <unistd.h>

int timeout_recv(int fd, char* buf, int len, int nsec) {
    struct timeval timeout;
    timeout.tv_sec = nsec;
    timeout.tv_usec = 0;

    printf("timeout_recv called, timeout %d seconds\n", nsec);

    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("setsockopt error");
        exit(1);
    }

    int n = recv(fd, buf, len, 0);

    return n;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: %s <ip address> <port>\n", argv[0]);
    }

    char* ip = argv[1];
    uint16_t port = atoi(argv[2]);

    printf("client start..\n");
    printf("connect to %s:%d\n", ip, port);

    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);

    int connfd;
    if ((connfd = connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr))) < 0) {
        perror("connect error");
        exit(1);
    }

    printf("success to connect server %s:%d\n", ip, port);
    printf("wait for server's response\n");
    char buf[100];
    while (1) {
        int nread;

        nread = timeout_recv(sockfd, buf, sizeof(buf), 10);
        if (nread < 0) {
            perror("timeout_recv error");
            exit(1);
        } else if (nread == 0) {
            shutdown(sockfd, SHUT_RDWR);
            break;
        }

        write(STDOUT_FILENO, buf, nread);
    }

    return 0;
}