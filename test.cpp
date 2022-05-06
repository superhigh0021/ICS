//widget.cpp
#include"widget.h"
#include<vector>
#include<iostream>
#include<string>
#include<set>
using namespace std;

int main(void){
    set<char> follow[10];
    for(auto i:follow){
        for(auto j : i)
            cout<<j<<endl;
    }
}

struct Widget::Impl{
    std::string name;
    std::vector<double> data;
};

Widget::Widget() = default;
Widget::Widget(Widget&& rhs) = default;
Widget::~Widget() = default;
Widget& Widget::operator=(Widget&& rhs) = default;