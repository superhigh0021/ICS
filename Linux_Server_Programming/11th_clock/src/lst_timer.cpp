#include "lst_timer.h"
#include <cstdio>

util_timer::util_timer() : prev(nullptr), next(nullptr) {}

sort_timer_lst::sort_timer_lst() : head(nullptr), tail(nullptr) {}

sort_timer_lst::~sort_timer_lst() {
    util_timer* tmp = head;
    while (tmp) {
        head = tmp->next;
        delete tmp;
        tmp = head;
    }
}

void sort_timer_lst::add_timer(util_timer* timer) {
    if (!timer) {
        return;
    }

    if (!head) {
        head = tail = timer;
        return;
    }

    /* 如果目标定时器的超时时间小于当前链表中所有定时器的超时时间，则把该定时器插入链表头部，作为头结点。
       否则就调用重载函数，将它插入链表中合适的位置，保证链表的升序特性 */
    if (timer->expire < head->expire) {
        timer->next = head;
        head->prev = timer;
        head = timer;
        return;
    }
    add_timer(timer, head);
}

void sort_timer_lst::adjust_timer(util_timer* timer) {
    if (!timer) {
        return;
    }
    util_timer* tmp = timer->next;

    /* 如果被调整的目标定时器处在链表尾部，或者该定时器新的超时值仍然小于其下一个定时器的超时值，则不用调整 */
    if (!tmp || (timer->expire < tmp->expire)) {
        return;
    }

    /* 如果目标定时器是链表的头结点，则将该定时器从链表中去除并重新插入链表 */
    if (timer == head) {
        head = head->next;
        head->prev = nullptr;
        head->next = nullptr;
        add_timer(timer, head);
    }
    /* 如果不是头结点，也不是尾结点，就取出来放到头结点后面的哪部分链表中 */
    else {
        timer->prev->next = timer->next;
        timer->next->prev = timer->prev;
        add_timer(timer, timer->next);
    }
}

void sort_timer_lst::del_timer(util_timer* timer) {
    if (!timer) {
        return;
    }

    /* 表示整个链表中只有一个定时器 ———— 目标定时器 */
    if ((timer == head) && (timer == tail)) {
        delete timer;
        head = nullptr;
        tail = nullptr;
        return;
    }

    /* 如果链表中至少有两个定时器，且目标定时器是链表的头结点，则将链表的头结点重置为原头结点的下一个节点，
       然后删除目标定时器 */
    if (timer == head) {
        head = head->next;
        head->prev = nullptr;
        delete timer;
        return;
    }

    if (timer == tail) {
        tail = tail->prev;
        tail->next = nullptr;
        delete timer;
        return;
    }

    /* 如果目标定时器在链表中间，则把它前后的定时器串联起来，然后删除目标定时器 */
    timer->prev->next = timer->next;
    timer->next->prev = timer->prev;
    delete timer;
}

void sort_timer_lst::tick() {
    if (!head) {
        return;
    }
    puts("timer tick");
    time_t cur = time(nullptr);
    util_timer* tmp = head;

    while (tmp) {
        /* 因为每个定时器都是用绝对时间作为超时值，可以把定时器的超时值和系统当前时间比较，
           判断定时器是否到期 */
        if (cur < tmp->expire) {
            break;
        }

        /* 调用定时器的回调函数，执行定时任务 */
        tmp->cb_func(tmp->user_data);

        /* 删除该定时任务，并重置链表头结点 */
        head = tmp->next;
        if (head) {
            head->prev = nullptr;
        }
        delete tmp;
        tmp = head;
    }
}

void sort_timer_lst::add_timer(util_timer* timer, util_timer* lst_head) {
    util_timer* prev = lst_head;
    util_timer* tmp = prev->next;
    /* 遍历lst_head节点之后的部分链表，直到找到一个超时时间大于目标定时器的超时时间的节点，
       并将目标定时器插入该节点之前 */
    while (tmp) {
        if (timer->expire < tmp->expire) {
            prev->next = timer;
            timer->next = tmp;
            tmp->prev = timer;
            timer->prev = prev;
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    /* 遍历完都没有找到，就加入作为新的尾结点 */
    if (!tmp) {
        prev->next = timer;
        timer->prev = prev;
        timer->next = nullptr;
        tail = timer;
    }
}