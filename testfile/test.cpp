#include <iostream>
#include <unordered_map>
#include<vector>
using namespace std;

int main(void) {
    vector<int>nums{0,1,2,3,4,5};
    auto i = nums.begin();
    cout<<*(i+2)<<endl;
}