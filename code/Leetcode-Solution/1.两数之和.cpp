/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 * 
 * 思路解析：
 * 对数组进行一次遍历，遍历的同时用哈希表保存 hash: [val, index]，以建立元素值到数组元素下标索引的映射关系，哈希表查找仅需 O(1) 时间复杂度。
 */
// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash;       // 元素值->下标
        for (int i = 0; i < nums.size(); i++) {
            if (hash.find(target - nums[i]) != hash.end()) {
                return vector<int>{hash[target - nums[i]], i};
            }
            hash[nums[i]] = i;
        }
        return vector<int>{-1, -1};
    }
};
// @lc code=end