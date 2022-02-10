#include <iostream>
#include <vector>
#include<type_traits>
using namespace std;

template <typename It>
auto fcn(It beg, It end) -> typename remove_reference<decltype(*beg)>::type {
    return *beg;
}

int main(void) {
    vector<int> v{1, 2, 3, 4, 5, 6};
    fcn(v.begin(),v.end());

    return 0;
}