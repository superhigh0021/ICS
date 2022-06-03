#include <E:\sophomore_1st\smartPointer\sharedPtr.h>
#include <memory>

void test() {
    {
        sharedPtr<int> sp(new int(3));
        int c = *sp;
        std::cout << c << std::endl;
        sharedPtr<int> ssp(std::move(sp));
        std::cout << *sp << std::endl;
    }
}

int main(void) {

    test ();

    return 0;
}