#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUF_SIZE 1024
#define OPSZ 4
#define RLT_SIZE 4
void error_handling(char* message);

int main(int argc, char** argv) {
    int serv_sock;
    char opmsg[BUF_SIZE];
    int result, opnd_cnt, i;

    struct sockaddr_in serv_addr;

    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error!");
    else
        puts("Connected............\n");
    
    fputs("Operand count: ",stdout);
    scanf("%d",&opnd_cnt);
    opmsg[0] = (char)opnd_cnt;

    for(i = 0; i < opnd_cnt; ++i){
        printf("Operand %d: ",i+1);
        scanf("%d",(int*)&opmsg[i*OPSZ+1]);
    }
    fgetc(stdin); //下一步要输入运算符，所以用fgetc删除缓冲中的字符\n
    fputs("Operator: ",stdout);
    scanf("%c",&opmsg[OPSZ * opnd_cnt + 1]);
    write(serv_sock, opmsg, opnd_cnt * OPSZ + 2);
    read(serv_sock, &result, RLT_SIZE);

    printf("Operation result: %d \n", result);
    close(serv_sock);
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}