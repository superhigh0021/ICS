#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>
#define BUF_SIZE 30

int main(int argc, char **argv){
    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;
    FD_ZERO(&reads);
    FD_SET(0, &reads);
    

    while(1){
        temps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        /*  在调用select的时候，传递进去的fd_set变量原来为1的所有位全部变成0；
            所以可以认为仍然为1的位置上的文件描述符发生了变化*/
        result = select(1, &temps, 0, 0, &timeout);
        if(result == -1){
            puts("select() error!");
            break;
        }
        else if(result == 0)
            puts("Time-out!");
        else{
            if(FD_ISSET(0,&temps)){
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                printf("message from console: %s",buf);
            }
        }
    }
    return 0;
}