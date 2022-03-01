#include<iostream>
using namespace std;


int main(void){
    printf("location of code : %p\n", (void *) main); 
    printf("location of heap : %p\n", (void *) malloc(1));
    int i=0;
    printf("location of stack : %p\n", (void *)&i); 

    return 0;
}