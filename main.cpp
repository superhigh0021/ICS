#include <iostream>
#include <vector>
using namespace std;

int compute(vector<int>& nums)
{
    int total = nums.size() * (nums.size() + 1) / 2;
    cout<<total<<endl;
    int sum02=0;
    for (auto i : nums)
        sum02+=i;
    return total - sum02;
}
int main(void)
{
    vector<int>nums={3,0,1};
    cout<<compute(nums)<<endl;
    return 0;
}