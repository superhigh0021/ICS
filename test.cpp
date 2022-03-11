#include<iostream>
#include<future>

int print(int n){
    std::cout<<"thread_child"<<std::endl;
    return n;
}

int main(void){
    auto fut=std::async(std::launch::async,print,6);
    fut.wait();
    std::cout<<"thread_parent\n";
    std::cout<<fut.get()<<std::endl;

    return 0;
}