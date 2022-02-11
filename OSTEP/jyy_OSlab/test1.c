#include<stdio.h>
#include<pthread.h>

void* a(){
    printf("a");
}

int main(int argc,char** argv){
    pthread_t myThread1,myThread2;
    for(int i=0;i<10000000;++i)
        pthread_create(&myThread1, NULL, a, NULL);
}