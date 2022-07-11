#include <fstream>
#include <iostream>
#include <typeinfo>
#include <vector>
using namespace std;

class A {
public:
    int a;
    virtual void myfuncA() {
        cout << "A" << endl;
    }
    virtual ~A() = default;
};

class B : public A {
public:
    int b;
    void myfuncA() {
        cout << "B" << endl;
    }
};

int main(void) {
    fstream f1("serverkey", std::ios::in | std::ios::out | std::ios::binary);
    string s1{"123456"};
    f1.write(s1.c_str(), sizeof(s1.c_str()));

    char* str = new char[30];
    f1.read(str, 30);
    cout << str << endl;

    return 0;
}