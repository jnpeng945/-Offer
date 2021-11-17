#include<iostream>
#include<vector>

using namespace std;

int minArray(vector<int>& nums) {
    int l = 0, r = nums.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (nums[mid] < nums[r]) r = mid;
        else if (nums[mid] == nums[r]) r--;
        else l = mid + 1;
    }
    return nums[r];
}

int main() {
    vector<int> nums = {3, 4, 5, 1, 2};
    cout << minArray(nums) << endl;
    return 0;
}