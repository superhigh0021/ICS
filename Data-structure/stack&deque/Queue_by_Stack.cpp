#include"Queue_by_Stack.hpp"

int main(void){
    Deque<int>q;
    q.enQueue(1);
    q.enQueue(2);
    q.enQueue(3);
    int x;
    q.deQueue(x);
    q.deQueue(x);
    std::cout<<x<<std::endl;
    q.print();

    return 0;
}