#include<iostream>
using namespace std;

template <typename F,typename T1,typename T2>
void filp(F f,T1 &&t1,T2 &&t2){
    f(t2,t1);
}

void add(int &a,int&b){
    a=a+b;
    b=a+b;
}

int main(void){
    int i=1;
    filp(add,i,42);
    cout<<i<<endl;
    return 0;
}