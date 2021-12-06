/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 */

// @lc code=start
class Solution {
public:
    string longestPalindrome(string s) {
        string res = "";
        for (int i = 0; i < s.size(); i++) {
            auto [left1, right1] = findLongest(s, i, i);
            if (right1 - left1 + 1 > res.size()) {
                res = s.substr(left1, right1 - left1 + 1);
            }
            auto [left2, right2] = findLongest(s, i, i + 1);
            if (right2 - left2 + 1 > res.size()) {
                res = s.substr(left2, right2 - left2 + 1);
            }
        }
        return res;
    }
    pair<int, int> findLongest(string s, int l, int r) {
        while(l >= 0 && r < s.size() && s[l] == s[r]) {
            l--, r++;
        }
        return {l + 1, r - 1};
    }
};
// @lc code=end

