#include <iostream>
#include <typeinfo>
#include <unordered_map>
#include <vector>
using namespace std;

class A {
public:
    explicit A(int _a)
        : a(_a) {}

private:
    int a;
};

int main(void) {
    // string s{"123"};
    // unordered_map<char, string>mp{{'1',"aaa"}};
    // cout<<typeid(s[1]).name()<<endl;
    // mp[s[1]];
    int i = 0;
    if (++i < 0)
        cout << "i" << endl;
    cout << i << endl;

    return 0;
}