// widget.h
#include<memory>
class Widget{
public:
    Widget();
    ~Widget();
    
    Widget(Widget&& rhs);
    Widget& operator=(Widget&& rhs);
        
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};