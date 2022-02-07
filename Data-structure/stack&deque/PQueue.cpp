#include "PQueue.hpp"

int main(int argc, char** argv)
{
    PQueue<int> p;
    p.insertPQueue(1, 4);
    p.insertPQueue(2, 3);
    p.insertPQueue(3, 2);
    p.insertPQueue(4, 1);

    int x,y;
    p.removePQueue(x,y);
    std::cout<<x<<' '<<y<<std::endl;
    
    p.print();

    return 0;
}