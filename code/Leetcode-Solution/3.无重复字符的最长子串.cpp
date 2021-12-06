/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 */

// @lc code=start
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> hash;
        int maxLen = 0;
        for (int i = 0, j = 0; i < s.size(); i++) {
            hash[s[i]]++;
            while(hash[s[i]] > 1) hash[s[j++]]--;
            maxLen = max(maxLen, i - j + 1);
        }
        return maxLen;
    }
};
// @lc code=end

