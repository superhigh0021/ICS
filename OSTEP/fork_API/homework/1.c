#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void){
 
   int fd=open("D:\\a.txt",O_RDONLY);
 
   if(fd==-1){
 
      printf("can not open the file\n");
 
      return 1;
 
   }
 
   char buf[1024]={"\0"};
 
   int len=read(fd,buf,1024);
 
   printf("%s\nlen=%d\n",buf,len);
 
   close(fd);
 
   return 0;
 
}