#include <iostream>
#define initSize 100

template <typename T>
class SeqStack
{
private:
    T *elem;
    int maxSize, top;

public:
    SeqStack()
    {
        elem = new T(initSize);
        if (this->elem == nullptr)
            std::cout << "allocate failure!" << std::endl;
        this->maxSize = initSize, this->top = -1;
    }

    bool stackEmpty();

    bool stackFull();

    bool Push(const T &x);

    bool Pop(T &x);

    bool getTop(T &x);

    int StackSize();

    void print()
    {
        for (int i = 0; i < initSize; ++i)
            std::cout << elem[i] << ' ';
        std::cout << std::endl;
    }
};

template <typename T>
bool SeqStack<T>::stackEmpty()
{
    return this->top == -1;
}

template <typename T>
bool SeqStack<T>::stackFull()
{
    return this->top == this->maxSize - 1;
}

template <typename T>
bool SeqStack<T>::Push(const T &x)
{
    if (this->stackFull())
        return false;
    this->elem[++this->top] = x;
    return true;
}

template <typename T>
bool SeqStack<T>::Pop(T &x)
{
    if (this->top == -1)
        return false;
    x = this->elem[this->top--];
    return true;
}

template <typename T>
bool SeqStack<T>::getTop(T &x)
{
    if (this->top == -1)
        return false;
    x = this->elem[top];
    return true;
}

template <typename T>
int SeqStack<T>::StackSize()
{
    return this->top + 1;
}