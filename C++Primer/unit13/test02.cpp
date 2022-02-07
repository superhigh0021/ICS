#include <iostream>
#include <utility>
using namespace std;

class A {
public:
    A();
    A(int i) : a(i) {}
    A(const A& Aa) : a(Aa.a) { cout << "copy!" << endl; }
    A(A&& Aa)
    noexcept : a(Aa.a) { cout << "move!" << endl; }
    A& operator=(const A& Aa) {
        a = Aa.a;
        cout << "equal!" << endl;
        return *this;
    }
    A& operator=(A&& Aa) {
        a = Aa.a;
        cout << "equal_move!" << endl;
        return *this;
    }

private:
    int a = 0;
};

A getA() {
    A ss(4);
    return ss;
}

int main(int argc, char** argv) {
    A aa(3);
    A aaa(aa);           // copy
    A a = std::move(aa); // move
    A ab(4);
    ab = getA(); // equal_move!!!!!!!!!!!!!!!!!!
    a = aa;      // equal

    return 0;
}