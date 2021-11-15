剑指 Offer 系列题目解题思路回顾。

<!--more-->

## 栈与队列

### [9. 用两个栈实现队列](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)

**题目描述**：用两个栈实现一个队列。完成两个操作：

- 队列尾部插入整数；
- 队列头部删除整数，队列为空则返回 -1。

**解题思路**：本题只需理清从队列头部删除整数的逻辑。

```cpp
class CQueue {
public:
    stack<int> stk1, stk2;
    CQueue() { }
    
    void appendTail(int value) {
        stk1.push(value);
    }
    
    int deleteHead() {
        int res = -1;
        if (stk2.empty()) {
            while(!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }
        }
        if (!stk2.empty()) {
            res = stk2.top();
            stk2.pop(); 
        }
        return res;
    }
};
```

### [30. 包含min函数的栈](https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof/)

**题目描述**：定义栈的数据结构，实现四个操作：

- `void push(int x)`，元素入栈；
- `void pop()`，元素出栈；
- `int top()`，返回栈顶元素；
- `int min()`，返回栈中最小的元素；

调用 `min`、`push` 及 `pop` 的时间复杂度都是 O(1)。

**解题思路**：维护 `stk2` 为单调递减的单调栈。

```cpp
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> stk1, stk2;
    MinStack() { }
    
    void push(int x) {
        if (stk1.empty() || stk2.top() >= x) {
            stk2.push(x);
        } 
        stk1.push(x);
    }
    
    void pop() {
        if (stk1.top() == stk2.top()) stk2.pop();
        stk1.pop();
    }
    
    int top() {
        return stk1.top();
    }
    
    int min() {
        return stk2.top();
    }
};
```



## 链表

### [6. 从尾到头打印链表](https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)

**题意描述**：输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

示例 1：

```latex
输入：head = [1,3,2]
输出：[2,3,1]
```

限制：`0 <= 链表长度 <= 10000`

```cpp
vector<int> reversePrint(ListNode* head) {
    vector<int> res;
    while(head) {
        res.push_back(head->val);
        head = head->next;
    }
    return vector<int>(res.rbegin(), res.rend());
}
```



### [24. 反转链表](https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof/)

**题意描述**：输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

示例：

```latex
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
```

递归法：

```cpp
ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* newHead = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}
```

迭代法：

```cpp
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
```



### [35. 复杂链表的复制](https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/)

**题意描述**：实现 `copyRandomList` 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 `next` 指针指向下一个节点，还有一个 `random` 指针指向链表中的任意节点或者 `null`。

示例 1：

<img src="https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/09/e1.png" div align=center/>

```latex
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
```

示例 2：

<img src="https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/09/e2.png" div align=center/>

```latex
输入：head = [[1,1],[2,1]]
输出：[[1,1],[2,1]]
```

示例 3：

<img src="https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/09/e3.png" div align=center/>

```latex
输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]
```

**解题思路**：假设原始链表为下图所示，图中对于 `next` 指针和 `random` 指针，指向空的不做标记，红色表示 `random` 指针。



<img src="../$%7Bfigs%7D/20211115155712.png" div align=center/>

第一步：我们将每个节点复制一遍（忽略 `random` 指针），如下图所示：

<img src="../$%7Bfigs%7D/20211115160033.png" div align=center/>

第二步：复制 `random` 指针，遍历链表，对于非空的 `cur->random` ，让 `cur->next->random = cur->random->next`。

<img src="https://figs-1308257758.cos.ap-nanjing.myqcloud.com/img/20211115160256.png" div align=center />

第三步：分离两个链表。

```cpp
Node* copyRandomList(Node* head) {
    if (head == nullptr) return head;
    Node* cur = head;
    // 链表复制
    while(cur) {
        Node* tmp = new Node(cur->val);
        tmp->next = cur->next;
        cur->next = tmp;
        cur = tmp->next;
    }
    // random 指针复制
    cur = head;
    while(cur) {
        if (cur->random) {
            cur->next->random = cur->random->next;
        }
        cur = cur->next->next;
    }
    // 链表分割
    Node* pre = head;
    cur = head->next;
    Node* newHead = head->next;
    while(cur->next) {
        pre->next = cur->next;
        cur->next = cur->next->next;
        pre = pre->next;
        cur = cur->next;
    }
    pre->next = nullptr;
    return newHead;
}
```



## 字符串

### [05. 替换空格](https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof/)

**题意描述**：把字符串 `s` 中的每个空格替换成 `"%20"`。

示例：

```latex
输入：s = "We are happy."
输出："We%20are%20happy."
```

**解题思路**：假设初始字符串 `s` 的长度为 $n$。 

- 统计字符串 `s` 中的空格个数 $cnt$，将字符串长度调整为 $n + 2 \times cnt$；
- 从后往前遍历字符串，遇到空格就替换为字符串 `"%20"`。

在本题中我们用两个指针 `i` 和 `j` 分别指向 `n - 1` 和  `n + 2 * cnt - 1` 的位置，直到 `i == j` 时我们结束循环。

```cpp
string replaceSpace(string s) {
    int cnt = 0;
    for (auto c : s) {
        if (c == ' ') cnt++;
    }
    int i = s.size() - 1;
    s.resize(s.size() + 2 * cnt);
    int j = s.size() - 1;
    while(i < j) {
        if (s[i] != ' ') s[j--] = s[i--];
        else {
            i--;
            s[j--] = '0';
            s[j--] = '2';
            s[j--] = '%';
        }
    }
    return s;
}
```



### [58 - II. 左旋转字符串](https://leetcode-cn.com/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/)

**题意描述**：实现字符串的左旋操作，也就是把字符串前面的若干个字符转移到字符串的尾部。

**解题思路**：字符串三次翻转。------->--->，<---<-------，---><-------，--->------->

示例 1：

```latex
输入: s = "abcdefg", k = 2
输出: "cdefgab"
```

```cpp
string reverseLeftWords(string s, int k) {
    int n = s.size();
    reverse(s.begin(), s.end());
    reverse(s.begin(), s.begin() + n - k);
    reverse(s.begin() + n - k, s.end());
    return s;
}
```



## 查找

### [03. 数组中重复的数字](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)

**题意描述**：在一个长度为 $n$ 的数组 $nums$ 里的所有数字都在 $0～n-1$ 的范围内。找出数组中任意一个重复的数字。

示例：

```latex
输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3 
```

**解题思路**：

- 方法1：哈希表统计，一次遍历数组中的元素，当遍历到重复数字时 `break`；

```cpp
int findRepeatNumber(vector<int>& nums) {
    unordered_map<int, int> hash;
    for (auto  x : nums) {
        if (hash[x] > 0) return x;
        hash[x]++;
    }
    return -1;
}
```

- 方法2：原地交换。

<img src="https://figs-1308257758.cos.ap-nanjing.myqcloud.com/img/20211115173654.png" width = 600px div align = center/>

```cpp
int findRepeatNumber(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        while(i != nums[i] && nums[i] != nums[nums[i]]) {
            swap(nums[i], nums[nums[i]]);
        }
        if (i != nums[i] && nums[i] == nums[nums[i]]) return nums[i];
    }
    return -1;
}
```



### [53 - I. 在排序数组中查找数字 I](https://leetcode-cn.com/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/)

**题意描述**：统计一个数字在排序数组中出现的次数。

示例 1：

```latex
输入: nums = [5,7,7,8,8,10], target = 8
输出: 2

输入: nums = [5,7,7,8,8,10], target = 6
输出: 0
```

**解题思路**：两次二分查找，在数组中找出这个数字的左边界和右边界。

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() == 0) return 0;
        int l = 0, r = nums.size() - 1;
        while(l < r) {
            int mid = (l + r) >> 1;
            if (nums[mid] >= target) r = mid;
            else l = mid + 1;
        }
        if (nums[r] != target) return 0;
        int left = r;
        l = left, r = nums.size() - 1;
        while(l < r) {
            int mid = (l + r + 1) >> 1;
            if (nums[mid] <= target) l = mid;
            else r = mid - 1;
        }
        return l - left + 1;
    }
};
```



### [53 - II. 0～n-1中缺失的数字](https://leetcode-cn.com/problems/que-shi-de-shu-zi-lcof/)

**题意描述**：一个长度为 $n-1$ 的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围 $0 \sim n-1$ 之内。在范围 $0 \sim n-1$ 内的 $n$ 个数字中有且只有一个数字不在该数组中，请找出这个数字。

示例：

```latex
输入: [0,1,3]
输出: 2

输入: [0,1,2,3,4,5,6,7,9]
输出: 8
```

**解题思路**：二分查找。查找满足性质 `mid != nums[mid]` 的区段的左边界。

```cpp
int missingNumber(vector<int>& nums) {
    int l = 0, r = nums.size();
    while (l < r) {
        int mid = l + r >> 1;
        if (mid != nums[mid]) r = mid;
        else l = mid + 1;
    }
    return r;
}
```



### [04. 二维数组中的查找](https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/)

**题意描述**：在一个 $n \times m$ 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

示例：

```latex
matrix = [
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]

target = 5, return true;
target = 20, return false;
```

**解题思路**：从数组右上角开始遍历，当该元素大于 `target` 时，到下一列的位置开始遍历，否则到下一行的位置开始遍历。

```cpp
bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;
    int n = matrix.size(), m = matrix[0].size();
    int i = 0, j = m - 1;
    while(i < n && j >= 0) {
        if (matrix[i][j] == target) return true;
        if (matrix[i][j] > target) j--;
        else i++;
    }
    return false;
}
```



### [11. 旋转数组的最小数字](https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/)

**题意描述**：数组的旋转是指把数组最开始的若干个元素搬到数组的末尾。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。

示例：

```latex
输入：[3,4,5,1,2]
输出：1
```

解题思路：题中数组满足部分有序，可尝试使用二分查找解法。

```cpp
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
```



### [50. 第一个只出现一次的字符](https://leetcode-cn.com/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof/)

**题意描述**：在字符串 $s$ 中找出第一个只出现一次的字符。如果没有，返回一个单空格。$s $ 只包含小写字母。

示例：

```latex
输入：s = "abaccdeff"
输出：'b'
```

**解题思路**：两次遍历，第一次用哈希表统计字符串中每个字母出现的次数，第二次遍历查看出现一次的字母。

```cpp
char firstUniqChar(string s) {
    unordered_map<char, int> hash;
    for (auto x : s) {
        hash[x]++;
    }
    for (auto x : s) {
        if (hash[x] == 1) return x;
    }
    return ' ';
}
```



## 搜索与回溯算法

### [32 - I. 从上到下打印二叉树](https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-lcof/)

**题意描述**：从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。

示例：

```latex
给定二叉树: [3,9,20,null,null,15,7]
    3
   / \
  9  20
    /  \
   15   7
   
输出：[3,9,20,15,7]
```

**解题思路**：BFS，二叉树的层序遍历。

```cpp
vector<int> levelOrder(TreeNode* root) {
    if (root == nullptr) return {};
    queue<TreeNode*> que;
    que.push(root);
    vector<int> res;
    while(!que.empty()) {
        auto node = que.front();
        que.pop();
        res.push_back(node->val);
        if (node->left) que.push(node->left);
        if (node->right) que.push(node->right);
    }
    return res;
}
```



### [32 - II. 从上到下打印二叉树 II](https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-ii-lcof/)

**题意描述**：从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。

示例：

```latex
给定二叉树: [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
输出其层序遍历结果：
[ [3],
  [9,20],
  [15,7]]
```

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    if (root == nullptr) return {};
    queue<TreeNode*> que;
    que.push(root);
    vector<vector<int>> res;
    while(!que.empty()) {
        int n = que.size();
        vector<int> tmp;
        for (int i = 0; i < n; i++) {
            auto node = que.front();
            que.pop();
            tmp.push_back(node->val);
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
        res.push_back(tmp);
    }
    return res;
}
```







