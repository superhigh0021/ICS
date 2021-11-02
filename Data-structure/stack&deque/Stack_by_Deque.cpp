#include"Stack_by_Deque.hpp"

int main(int argc,char** argv){
    Stack<int>s;
    s.Push(1);
    s.Push(2);
    int i;
    s.Pop(i);
    std::cout<<i<<std::endl;

    return 0;
}