#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(void){
    char *str="123\n";
    write(1,str,strlen(str));

    return 0;
}