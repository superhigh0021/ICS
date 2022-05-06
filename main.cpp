#include<typeinfo>
#include<iostream>
#include<memory>

class Widget{
public:
    Widget()=default;
    
    Widget(const Widget& w):_i(w._i){
        std::cout<<"copy cons"<<std::endl;
    }
    
    Widget(Widget&& w):_i(std::move(w._i)){
        std::cout<<"move cons"<<std::endl;
    }
    void process();

private:
    int _i;
};

Widget process(Widget ww){
    Widget w;
    return w;
}

void Widget::process(){
    auto lbd=[_i = _i](){return _i;};
}

int main(void){
    int nums[9];
    std::cin>>nums[9];
    std::cout<<nums[9]<<std::endl;

    return 0;
}