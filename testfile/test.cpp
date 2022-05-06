#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

#define M 5
#define N M+M

int main(){
    int k;
    k = N * N * 5;
    printf("%d\n",k);
    return 0;
}