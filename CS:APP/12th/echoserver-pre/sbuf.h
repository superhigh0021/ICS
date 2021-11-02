#include"/home/xiaoyu/sophomore_1st/CS:APP/csapp.h"
typedef struct{
    int *buf;
    int n;
    int front;
    int rear;
    sem_t mutex;
    sem_t slots;
    sem_t items;
}sbuf_t;

void sbuf_init(sbuf_t *sp,int n);

void sbuf_denit(sbuf_t *sp);

void sbuf_insert(sbuf_t *sp,int item);

int sbuf_remove(sbuf_t *sp);