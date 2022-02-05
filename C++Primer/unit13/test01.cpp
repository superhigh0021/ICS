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
    delete a1;
    return 0;
}