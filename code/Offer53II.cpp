#include<iostream>
#include<vector>

using namespace std;

int missingNumber(vector<int>& nums) {
    int l = 0, r = nums.size();
    while (l < r) {
        int mid = l + r >> 1;
        if (mid != nums[mid]) r = mid;
        else l = mid + 1;
    }
    return r;
}

int main() {
    vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 9};
    cout << missingNumber(nums) << endl;
    return 0;
}