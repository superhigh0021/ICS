#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc,char**argv){
    int rc=fork();
    if(rc>0){
        sleep(0);
        printf("goodbye\n");
    }else{
        printf("hello\n");
    }
    return 0;
}