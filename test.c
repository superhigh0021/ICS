#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(void){

    pid_t pid;
    pid = fork();
    if(pid == 0){
        puts("child\n");
        return 0;
    }else puts("father");
    puts("end.....");

    return 0;
}