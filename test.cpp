#include <future>
#include <iostream>
#include <vector>

class String {
public:
    explicit String(const char* ptr){
        std::cout<<"explicit!"<<std::endl;
    }

private:
};

int main(void) {
    String s=nullptr;
    String ss(nullptr);

    return 0;
}