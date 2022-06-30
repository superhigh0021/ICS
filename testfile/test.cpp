#include <iostream>
#include <vector>
using namespace std;

struct S {
    S(int i = 100)
        : a(i) {}
    int a;
};

class A {

public:
    A() {}
    vector<S> s;
    void change() {
        this->s.push_back(1000);
    }
};

int main(void) {
    A aa;
    aa.change();

    cout << aa.s[0].a << endl;
}