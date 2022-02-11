#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int p = open("1.c", O_RDONLY);
    char buffer[1024] = { "\0" };
    int rc = fork();
    if (rc == 0) {
        read(p, buffer, sizeof(buffer) / sizeof(char));
        printf("%d %s\n%d",p, buffer,getpid());
    } else {
        read(p, buffer, sizeof(buffer) / sizeof(char));
        printf("%d %s \n%d", p,buffer,getpid());
    }

    return 0;
}