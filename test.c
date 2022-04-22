#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(void){

    char buf[100];
    int fd = open("test.c",O_RDONLY);
    read(fd,buf,2);
    printf("%s",buf);
    read(fd,buf,2);
    printf("%s",buf);

    return 0;
}