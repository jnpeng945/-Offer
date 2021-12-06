/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个正序数组的中位数
 */

// @lc code=start
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int sumLen = nums1.size() + nums2.size();
        if (sumLen % 2 == 0) {
            int left = getKthSmallest(nums1, 0, nums2, 0, sumLen / 2);
            int right = getKthSmallest(nums1, 0, nums2, 0, sumLen / 2 + 1);
            return (left + right) / 2.0;
        } else {
            return getKthSmallest(nums1, 0, nums2, 0, sumLen / 2 + 1);
        }
    }
    int getKthSmallest(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
        if (nums1.size() - i > nums2.size() - j) return getKthSmallest(nums2, j, nums1, i, k);
        // nums1 为空
        if (nums1.size() == i) return nums2[j + k - 1];
        if (k == 1) return min(nums1[i], nums2[j]);

        int si = min((int)nums1.size(), i + k / 2), sj = j + k - k / 2;
        if (nums1[si - 1] > nums2[sj - 1]) {
            return getKthSmallest(nums1, i, nums2, sj, k - (sj - j));
        } else {
            return getKthSmallest(nums1, si, nums2, j, k - (si - i));
        }
    }
};
// @lc code=end

