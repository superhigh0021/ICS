#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc,char**argv){
    int rc=fork();
    if(rc==0){
        fclose(stdout);
        printf("123456\n");
    }
    else printf("654321\n");
    return 0;
}