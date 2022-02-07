#include "CircQueue.hpp"

#define Size 20

template <typename T>
class Stack {
private:
    CircQueue<T> Q1, Q2;

public:
    bool stackEmpty()
    {
        return Q1.queueEmpty() && Q2.queueEmpty();
    }

    bool stackFull()
    {
        return Q1.queueFull() && Q2.queueFull();
    }

    bool Push(const int& x);

    bool Pop(int& x);

    void show()
    {
        Q1.print();
    }
};

template <typename T>
bool Stack<T>::Push(const int& x)
{
    if (this->stackFull())
        return false;
    if (this->stackEmpty())
        Q1.enQueue(x);
    else if (!Q1.queueEmpty())
        Q1.enQueue(x);
    else
        Q2.enQueue(x);
    return true;
}

template <typename T>
bool Stack<T>::Pop(int& x)
{

    if (this->stackEmpty())
        return false;
    if (!Q1.queueEmpty()) {
        while (1) {
            Q1.deQueue(x);
            if (!Q1.queueEmpty())
                Q2.enQueue(x);
            else
                break;
        }
    } else {
        while (1) {
            Q2.deQueue(x);
            if (!Q2.queueEmpty())
                Q1.enQueue(x);
            else
                break;
        }
    }
    return true;
}