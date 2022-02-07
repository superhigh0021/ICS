#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct A{
    int a=0;
    A(int i):a(i){}
    ~A(){
        cout<<"destructed!"<<endl;
    }
};

int main(void){
    A *a1=new A(3);

    //!销毁指针对象的时候调用析构函数 不delete而出作用域的指针对象 不调用
    //delete a1;
    return 0;
}