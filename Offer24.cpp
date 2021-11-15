#include<iostream>
#include<vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head) return head;
        ListNode* pre = nullptr, *cur = head;
        while(cur) {
            ListNode* p = cur->next;
            cur->next = pre;
            pre = cur;
            cur = p;
        }
        return pre;
    }
};

int main() {
    vector<int> nums = {1, 2, 3, 4};
    ListNode* head = new ListNode(-1);
    auto cur = head;
    for (int i = 0; i < nums.size(); i++) {
        cur = cur->next = new ListNode(nums[i]);
    }

    Solution A;
    auto p = A.reverseList(head->next);
    while(p) {
        cout << p->val << ' ';
        p = p->next;
    }
    cout << endl;
    return 0;
}