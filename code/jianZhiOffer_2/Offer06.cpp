#include<iostream>
#include<vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) { }
};

class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> res;
        while(head) {
            res.push_back(head->val);
            head = head->next;
        }
        return vector<int>(res.rbegin(), res.rend());
    }
};

int main() {
    vector<int> nums = {1, 3, 2};
    ListNode* head = new ListNode(-1);
    auto cur = head;
    for (int i = 0; i < nums.size(); i++) {
        cur = cur->next = new ListNode(nums[i]);
    }
    Solution A;
    vector<int> res = A.reversePrint(head->next);
    for (auto x : res) cout << x << ' ';
    cout << endl;
    return 0;
}