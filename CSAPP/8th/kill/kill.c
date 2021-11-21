#include"/home/xiaoyu/sophomore_1st/CS:APP/csapp.h"

int main(void)
{
    pid_t pid;

    if ((pid = fork()) == 0) {
        printf("Control should never reach here!\n");
        exit(0);
    }
    kill(pid, SIGKILL);
    exit(0);
}