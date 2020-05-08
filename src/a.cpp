#include <iostream>
#include <vector>
using namespace std;

int find(vector<int> &nums)
{
    int left = 0, right = 0;
    for (int i = 1; i < nums.size(); i++)
        right += nums[i];
    for (int i = 1; i < nums.size(); i++)
    {
        left += nums[i - 1];
        right -= nums[i];
        if (left == right)
            return i;
    }
    return -1;
}


int main()
{
    vector<int> nums = {-1,-1,-1,0,1,1};
    cout << find(nums) << endl;
    return 0;
}