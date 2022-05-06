#include <stdio.h>
#include <fcntl.h>

#define BUF_SIZE 30

int main()
{
    FILE *fp;
    char buf[BUF_SIZE];
    int fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC); //创建文件并返回文件描述符
    if (fd == -1)
    {
        fputs("file open error", stdout);
        return -1;
    }
    fp = fdopen(fd, "w"); //返回 写 模式的 FILE 指针
    fputs("NetWork C programming \n", fp);
    fclose(fp);
    return 0;
}