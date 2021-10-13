#include </home/xiaoyu/ubuntu_vscode_cpp/csapp.h>

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