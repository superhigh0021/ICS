#include <iostream>
using namespace std;

class Vector {
public:
    Vector() {
        for (auto& i : a)
            i = 0;
    }
    int& operator[](int i) {
        return a[i];
    }

private:
    int a[12];
};

auto change(Vector& v, int i)->decltype(v[i]){
    return v[i];
}

int main(void) {
    Vector v;
    change(v,0)=12;
    cout<<v[0]<<endl;

    return 0;
}