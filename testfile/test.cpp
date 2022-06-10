#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class A {
public:
    virtual void print() {
        cout << "base" << endl;
    }
};

class B : public A {
public:
    void print() {
        cout << "derived" << endl;
    }
};

int main(void) {
    A a;
    B b;
    A& aa = b;
    aa.print();
}