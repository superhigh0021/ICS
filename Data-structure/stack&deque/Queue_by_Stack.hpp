#include "SeqStack.hpp"

template <typename T>
class Deque
{
private:
    SeqStack<T> S1, S2;

public:
    bool queueEmpty();

    bool enQueue(const T &x);

    bool deQueue(T &x);

    void print(){
        S2.print();
    }
};

template <typename T>
bool Deque<T>::queueEmpty()
{
    if (S1.stackEmpty() && S2.stackEmpty())
        return true;
    else
        return false;
}

template<typename T>
bool Deque<T>::enQueue(const T& x){
    if(S1.stackFull()){
        if(!S2.stackEmpty())
            std::cout<<"deque is full!"<<std::endl;
        else{
            T temp;
            while(!S1.stackEmpty()){
                S1.Pop(temp);
                S2.Push(temp);
            }
        }
    }
    S1.Push(x);
    return true;
}

template<typename T>
bool Deque<T>::deQueue(T &x){
    if(S1.stackEmpty()&&S2.stackEmpty())
        return false;
    else{
        if(S2.stackEmpty()){
            while(!S1.stackEmpty()){
                S1.Pop(x);
                S2.Push(x);
            }
        }
        S2.Pop(x);
        return true;
    }
}