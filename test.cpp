#include <iostream>
#include <typeinfo>
using namespace std;

class Widget{
public:
    Widget()=default;
    Widget(int i):_i(i){
        cout<<"cons"<<endl;
    }
    template<typename T>
    Widget(T&& w):_i(std::forward<int>(w._i)){
        cout<<"ohhhhhh"<<endl;
        w._i=100;
    }

    Widget(const Widget& w):_i(w._i){
        cout<<"copy cons"<<endl;
    }

    void print(){
        cout<<this->_i<<endl;
    }
private:
    int _i;
};

int main(int argc, char** argv) {
    Widget w(9);
    auto ww(w);
    w.print();

    return 0;
}