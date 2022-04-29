#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main(){
    char *buf="123456";
    char *str;

    FILE * fp = fopen("test.txt","a");
    fwrite(buf,5,1,fp);

    fclose(fp);
    return 0;
}