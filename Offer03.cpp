#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int findRepeatNumber(vector<int>& nums) {
    unordered_map<int, int> hash;
    for (auto  x : nums) {
        if (hash[x] > 0) return x;
        hash[x]++;
    }
    return -1;
}

int main() {
    vector<int> nums{2, 3, 1, 0, 2, 5, 3};
    cout << findRepeatNumber(nums) << endl;
    return 0;
}