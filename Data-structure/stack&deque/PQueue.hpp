//不带头结点的链表实现的优先队列
#include <iostream>

template <typename T>
struct LinkNode {
public:
    T data;
    int priority;
    LinkNode<T>* link;

public:
    LinkNode(const T& x, const int& priority)
        : data(x), priority(priority), link(nullptr) {}
};

template <typename T>
class PQueue {
private:
    LinkNode<T>*front, *rear;

public:
    PQueue() : front(nullptr), rear(nullptr) {}

    bool pqueueEmpty();

    void insertPQueue(const T& x, const int& priority);

    bool removePQueue(T& x, int& priority);

    bool getFront(T& x, int& priority);

    bool getRear(T& x, int& priority);

    void print() {
        for (LinkNode<T>* s = front; s != nullptr; s = s->link)
            std::cout << s->data << ' ';
        std::cout << std::endl;
    }
};

template <typename T>
bool PQueue<T>::pqueueEmpty() {
    return this->front == this->rear;
}

template <typename T>
void PQueue<T>::insertPQueue(const T& x, const int& priority) {
    LinkNode<T>* s = new LinkNode<T>(x, priority);
    if (this->front == nullptr)
        this->front = this->rear = s;
    else {
        LinkNode<T>*p = this->front, *pr = nullptr;
        //查找ｓ的插入位置
        while (p != nullptr) {
            if (p->priority >= s->priority)
                break;
            else {
                pr = p;
                p = p->link;
            }
        }
        if (pr == nullptr) {
            //插在队头
            s->link = this->front;
            this->front = s;
        } else {
            //插在队列中部或尾部
            s->link = p;
            pr->link = s;
            if (pr == this->rear)
                this->rear = s;
        }
    }
}

//删除队头元素
template <typename T>
bool PQueue<T>::removePQueue(T& x, int& priority) {
    if (this->pqueueEmpty())
        return false;
    LinkNode<T>* s = this->front;
    this->front = this->front->link;
    x = s->data, priority = s->priority;
    delete s;
    if (this->front == nullptr)
        this->rear = nullptr;
    return true;
}

template <typename T>
bool PQueue<T>::getFront(T& x, int& priority) {
    if (this->pqueueEmpty())
        return false;
    x = this->front->data, priority = this->front->priority;
    return true;
}

template <typename T>
bool PQueue<T>::getRear(T& x, int& priority) {
    if (this->pqueueEmpty())
        return false;
    x = this->rear->data, priority = this->rear->priority;
    return true;
}