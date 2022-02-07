#include <functional>
#include <iostream>
#include <map>
using namespace std;

int add(int i, int j) {
    return i + j;
}

struct divide {
    int operator()(int i, int j) {
        return i / j;
    }
};

auto mod = [](int i, int j) { return i % j; };

map<string, function<int(int, int)>> binops = {
    {"+", add},
    {"-", std::minus<int>()},
    {"/", divide()},
    {"*", [](int i, int j) { return i * j; }},
    {"%", mod}};

int main(int argc,char**argv){
    cout<<"binops[\"+\"](4,5) = "<<binops["+"](4,5)<<endl;
    cout<<"binops[\"-\"](100,10) = "<<binops["-"](100,10)<<endl;
    cout<<"binops[\"/\"](100,10) = "<<binops["/"](100,10)<<endl;
    cout<<"binops[\"*\"](100,10) = "<<binops["*"](100,10)<<endl;
    cout<<"binops[\"%\"](107,10) = "<<binops["%"](107,10)<<endl;

    return 0;
}