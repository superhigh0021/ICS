#ifndef LST_TIMER
#define LST_TIMER

#include <arpa/inet.h>
#include <ctime>
#include <sys/socket.h>
#include <sys/types.h>

enum { BUFFER_SIZE = 64 };

class util_timer;

/* 客户端socket地址、socket文件描述符、读缓存和定时器 */
struct client_data {
    sockaddr_in address;
    int sockfd;
    char buf[BUFFER_SIZE];
    util_timer* timer;
};

// 定时器类
class util_timer {
public:
    util_timer();

public:
    /* 任务的超时时间，此处使用绝对时间 */
    time_t expire;

    /* 任务回调函数 */
    void (*cb_func)(client_data*);

    /* 回调函数处理的客户数据，由定时器的执行者传递给回调函数 */
    client_data* user_data;

    /* 指向前一个定时器 */
    util_timer* prev;

    /* 指向后一个定时器 */
    util_timer* next;
};

/* 定时器链表，是一个升序、双向链表，带有头结点和尾结点 */
class sort_timer_lst {
public:
    sort_timer_lst();

    /* 链表被销毁时，删除其中所有的定时器 */
    ~sort_timer_lst();

    /* 将目标定时器 timer 添加到链表中 */
    void add_timer(util_timer* timer);

    /* 当某个定时任务发生变化时，调整对应的定时器在链表中的位置
       该函数只考虑被调整的定时器的超时时间延长的情况，即定时器需要往链表尾部移动 */
    void adjust_timer(util_timer* timer);

    /* 将目标定时器timer从链表中删除 */
    void del_timer(util_timer* timer);

    /* SIGALRM信号每次被触发就在其信号处理函数中执行一次该函数，以处理链表上到期的任务 */
    void tick();

private:
    /* 重载的辅助函数，被public的函数调用
       表示将目标定时器timer添加到lst_head之后的哪部分链表中 */
    void add_timer(util_timer* timer, util_timer* lst_head);

private:
    util_timer* head;
    util_timer* tail;
};

#endif