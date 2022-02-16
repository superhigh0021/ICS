#include<iostream>
using namespace std;


int main(void){
    union{
        char cval;
        int ival;
        double dval;
    };
    cval='c';
    cout<<ival<<endl;

    return 0;
}