#include<iostream>
using namespace std;

struct T{
    typedef int number;
};

template<typename T>
struct Iter{
    typedef typename T::number num;
};

template<typename T>
struct Iter<T*>{
    typedef T num;
};

int main(void){
    T t;
    cout<<sizeof(typename Iter<int*>::num)<<endl;
    return 0;
}