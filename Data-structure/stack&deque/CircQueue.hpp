#include <iostream>

#define initSize 20

template<typename T>
class CircQueue {
private:
    T* elem;
    int maxSize;
    int front, rear;

public:
    // initQueue()
    CircQueue();

    bool queueEmpty();

    bool queueFull();

    bool enQueue(const T& x);

    bool deQueue(T& x);

    bool getFront(T& x);

    void print();
};

template <typename T>
CircQueue<T>::CircQueue()
{
    this->elem = new T(initSize);
    if (this->elem == nullptr) {
        std::cout << "存储分配失败" << std::endl;
        exit(0);
    }
    this->maxSize = initSize;
    this->front = this->rear = 0;
}

template <typename T>
bool CircQueue<T>::queueEmpty()
{
    return this->front == this->rear;
}

template <typename T>
bool CircQueue<T>::queueFull()
{
    return (this->rear + 1) % this->maxSize == this->front;
}

template <typename T>
bool CircQueue<T>::enQueue(const T& x)
{
    if(this->queueFull())
        return false;
    elem[rear] = x;
    rear = (rear + 1) % maxSize;
    return true;
}

template <typename T>
bool CircQueue<T>::deQueue(T& x)
{
    if(this->queueFull())
        return false;
    x = elem[front];
    front = (front + 1) % maxSize;
    return true;
}

template <typename T>
bool CircQueue<T>::getFront(T& x)
{
    if (queueEmpty())
        return false;
    x = this->elem[front];
    return true;
}

template <typename T>
void CircQueue<T>::print()
{
    for (int i = 0; i < maxSize; ++i)
        std::cout << elem[i] << ' ';
    std::cout<<std::endl;
}