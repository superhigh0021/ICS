#include<iostream>
#include<typeinfo>
using namespace std;

class SmallInt{
public:
    SmallInt(int i=0):val(i){
        if(i<0||i>255)
            throw std::out_of_range("Bad SmallInt value");
    }
    explicit operator int()const {return val;}
    void show(){cout<<val<<endl;}
private:
    std::size_t val;
};

int main(int argc,char**argv){
    SmallInt si;
    si=4;
    si.show();
    static_cast<int>(si)+3;

    return 0;
}