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



## 分治

### [07. 重建二叉树](https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/)

**题意描述**：输入某二叉树的前序遍历和中序遍历的结果，请构建该二叉树并返回其根节点。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

示例：

```latex
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
```

限制：0 <= 节点个数 <= 5000

**解题思路**：分治思想。前序遍历的首元素是根节点 `root` 的值。利用哈希表 `hash` 存储中序遍历中值与索引的映射，提高查询效率。`preL > preR` 表示已经越过了叶节点，函数返回。

```cpp
class Solution {
public:
    unordered_map<int, int> hash;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        if (n == 0) return nullptr;
        for (int i = 0; i < n; i++) {
            hash[inorder[i]] = i;
        }
        return dfs(preorder, 0, n - 1, inorder, 0, n - 1);
    }
    TreeNode* dfs(vector<int>& preorder, int preL, int preR, vector<int>& inorder, int inL, int inR) {
        if (preL > preR || inL > inR) return nullptr;
        TreeNode* root = new TreeNode(preorder[preL]);
        int index = hash[preorder[preL]];
        root->left = dfs(preorder, preL + 1, index - inL + preL, inorder, inL, index - 1);
        root->right = dfs(preorder, index - inL + preL + 1, preR, inorder, index + 1, inR);
        return root;
    }
};
```



### [16. 数值的整数次方](https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/)

**题意描述**：实现 [pow(*x*, *n*)](https://www.cplusplus.com/reference/valarray/pow/) ，即计算 x 的 n 次幂函数（即，$x^n$）。不得使用库函数，同时不需要考虑大数问题。

示例：

```latex
输入：x = 2.00000, n = 10
输出：1024.00000

输入：x = 2.00000, n = -2
输出：0.25000
解释：2-2 = 1/22 = 1/4 = 0.25
```

注意：

- $-100.0 < x < 100.0$
- $-2^{31} <= n <= 2^{31}-1$
- $-10^4 <= x^n <= 10^4$

**解题思路**：分治思想，快速幂模板题。

```cpp
double myPow(double x, int n) {
    long long k = n;
    bool is_minus = false;
    if (k < 0) {
        is_minus = true;
        k = -k;
    }
    double res = 1;
    while(k) {
        if (k & 1) res *= x;
        x *= x;
        k >>= 1;
    }
    return is_minus ? 1 / res : res;
}
```



### [33. 二叉搜索树的后序遍历序列](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/)

**题意描述**：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 `true`，否则返回 `false`。假设输入的数组的任意两个数字都互不相同。

示例：

```latex
输入: [1,3,2,6,5]
输出: true
```

**解题思路**：基于分治的思想，递归实现。

- `l >= r` 表示到达叶子节点，返回 `true`；
- 左子树节点值应当小于根节点的值 `rootVal`，且右子树节点值应当大于根节点的值 `rootVal`；

```cpp
class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        return dfs(postorder, 0, postorder.size() - 1);
    }
    bool dfs(vector<int>& postorder, int l, int r) {
        if (l >= r) return true;
        int rootVal = postorder[r];
        int k = l;
        while(k < r && postorder[k] < rootVal) k++;     // k 应指向右子树首个节点的值
        for (int i = k; i < r; i++) {
            if (postorder[i] < rootVal) return false;
        }
        return dfs(postorder, l, k - 1) && dfs(postorder, k, r - 1);
    }
};
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

### [32 - III. 从上到下打印二叉树 III](https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof/)

**题意描述**：实现一个函数按照之字形顺序打印二叉树。

示例：

```latex
给定二叉树: [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
输出层次遍历结果：
[ [3],
  [20,9],
  [15,7]]
```

**解题思路**：同前几题类似，直接贴出代码：

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    vector<vector<int>> res;
    queue<TreeNode*> que;
    que.push(root);
    bool flag = false;
    while(!que.empty()) {
        int n = que.size();
        vector<int> tmp;
        flag = !flag;
        for (int i = 0; i < n; i++) {
            auto node = que.front();
            que.pop();
            tmp.emplace_back(node->val);
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
        if (!flag) res.emplace_back(tmp.rbegin(), tmp.rend());
        else res.emplace_back(tmp);
    }
    return res;
}
```



### [26. 树的子结构](https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/)

**题意描述**：输入两棵二叉树 A 和 B，判断 B 是不是 A 的子结构。B 是 A 的子结构， 即 A 中有出现和 B 相同的结构和节点值。（约定空树不是任意一个树的子结构）

示例：

```latex
给定的树 A:
     3
    / \
   4   5
  / \
 1   2
给定的树 B：
   4 
  /
 1
返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。
```

**解题思路**：递归法。

```cpp
class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (!A || !B) return false;		// 空树不是任何树的子结构
        if (isSubStr(A, B)) return true;
        return isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }
    bool isSubStr(TreeNode* p1, TreeNode* p2) {
        if (!p2) return true;
        if (!p1 || p1->val != p2->val) return false;
        return isSubStr(p1->left, p2->left) && isSubStr(p1->right, p2->right);
    }
};
```



### [27. 二叉树的镜像](https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof/)

**题意描述**：输入一个二叉树，该函数输出它的镜像。

示例：

```latex
输入：
     4
   /   \
  2     7
 / \   / \
1   3 6   9
镜像输出：
     4
   /   \
  7     2
 / \   / \
9   6 3   1
```

递归解法：

```cpp
TreeNode* mirrorTree(TreeNode* root) {
    if (!root) return root;
    auto tmp = root->right;
    root->right = mirrorTree(root->left);
    root->left = mirrorTree(tmp);
    return root;
}
```

辅助栈解法：

```cpp
TreeNode* mirrorTree(TreeNode* root) {
    if (!root) return nullptr;
    stack<TreeNode*> stk;
    stk.push(root);
    while(!stk.empty()) {
        auto node = stk.top();
        stk.pop();
        if (node->left) stk.push(node->left);
        if (node->right) stk.push(node->right);
        swap(node->left, node->right);
    }
    return root;
}
```

### [28. 对称的二叉树](https://leetcode-cn.com/problems/dui-cheng-de-er-cha-shu-lcof/)

**题意描述**：判断一棵二叉树是不是对称的。对称二叉树定义：二叉树和它的镜像一样。

示例：

```latex
二叉树 [1,2,2,3,4,4,3] 是对称的
	1
   / \
  2   2
 / \ / \
3  4 4  3
```

**解题思路**：递归法。

- 空树满足对称二叉树的性质；
- 不满足对称二叉树的情况：左右子儿子中存在空节点，左右子儿子节点值不相等。

```cpp
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return dfs(root->left, root->right);
    }
    bool dfs(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        if (!p || !q || p->val != q->val) return false;
        return dfs(p->left, q->right) && dfs(p->right, q->left);
    }
};
```



### [12. 矩阵中的路径](https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/)

**题意描述**：给定一个 `m x n` 二维字符网格 `board` 和一个字符串单词 `word` 。如果 `word` 存在于网格中，返回 `true` ；否则，返回 `false` 。单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

示例：

```latex
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true
```

**解题思路**：DFS + 回溯。首先遍历网格 `board` ，查找单词首字母。由于同一个单元格内的字母不能重复使用，因此在搜索的过程中我们需要标记已经访问过的位置，并在本次搜索结束时进行回溯。 

```cpp
class Solution {
public:
    int m, n;
    const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    if (dfs(board, word, i, j, 1)) return true;
                }
            }
        }
        return false;
    }
    bool dfs(vector<vector<char>>& board, string& word, int x, int y, int u) {
        if (u == word.size()) return true;
        char t = board[x][y];
        board[x][y] = '.';		// 标记已访问
        for (int i = 0; i < 4; i++) {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < m && b >= 0 && b < n && board[a][b] == word[u]) {
                if (dfs(board, word, a, b, u + 1)) return true;
            }
        }
        board[x][y] = t;        // 回溯
        return false;
    }
};
```



### [13. 机器人的运动范围](https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/)

**题意描述**：地上有一个 $m$ 行 $n$ 列的方格，从坐标 [0, 0] 到坐标 [m - 1, n - 1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于 $k$ 的格子。求机器人能够到达多少个格子。

示例：

```latex
当 k 为 18 时，机器人能够进入方格 [35, 37] ，因为 3+5+3+7=18。但它不能进入方格 [35, 38]，因为 3+5+3+8=19。

输入：m = 2, n = 3, k = 1
输出：3
```

**解题思路**：DFS。`vis` 数组标记已经访问过的位置，`canArrived` 函数判断数组的位置是否可达。

```cpp
class Solution {
public:
    int res = 0;
    vector<vector<bool>> vis;
    const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    int movingCount(int m, int n, int k) {
        vis = vector<vector<bool>>(m, vector<bool>(n, false));
        dfs(0, 0, m, n, k);
        return res;
    }
    void dfs(int x, int y, int m, int n, int k) {
        if (!canArrived(x, y, k)) return;

        res++;
        vis[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < m && b >= 0 && b < n && !vis[a][b]) {
                dfs(a, b, m, n, k);
            }
        }
    }
    bool canArrived(int a, int b, int k) {
        int t = 0;
        while(a) {
            t += a % 10;
            a /= 10;
        }
        while(b) {
            t += b % 10;
            b /= 10;
        }
        return t <= k;
    }
};
```



### [34. 二叉树中和为某一值的路径](https://leetcode-cn.com/problems/er-cha-shu-zhong-he-wei-mou-yi-zhi-de-lu-jing-lcof/)

**题意描述**：给你二叉树的根节点 `root` 和一个整数目标和 `targetSum` ，找出所有 **从根节点到叶子节点** 路径总和等于给定目标和的路径。**叶子节点** 是指没有子节点的节点。

示例：

```latex
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：[[5,4,11,2],[5,8,4,5]]
```

**解题思路**：DFS + 回溯。

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<int> path;
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        dfs(root, 0, target);
        return res;
    }
    void dfs(TreeNode* root, int curSum, int target) {
        if (!root) return;

        curSum += root->val;		// curSum 是传值，所以不需要回溯
        path.push_back(root->val);
        if (curSum == target && !root->left && !root->right) {
            res.push_back(path);
        }
        dfs(root->left, curSum, target);
        dfs(root->right, curSum, target);
        path.pop_back();		// 回溯
    }
};
```



### [36. 二叉搜索树与双向链表](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/)

**题意描述**：输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。

<img src="https://figs-1308257758.cos.ap-nanjing.myqcloud.com/img/20211116191037.png" width = 300px div align = center/>

<img src="../$%7Bfigs%7D/20211116191120.png"/>" width = 300px div align = center/>

**解题思路**：二叉搜索树的中序遍历为**递增序列**。算法流程如下：

```latex
dfs(cur): 递归法中序遍历；
1. 终止条件：当 cur 为 空表示越过叶子节点，需返回；
2. 递归左子树 dfs(cur->left)
3. 构建链表：
	当 pre 为空时：代表正在访问链表头节点，记为 head；
	当 pre 不为空时：修改双向节点指向，pre->right = cur，cur->left = pre；
	保存 cur: 更新 pre = cur, 即节点 cur 是后继节点的 pre；
4. 递归右子树 dfs(cur->right)
```

注意：在本算法中，需要特判根节点为 `nullptr` 的情况，中序遍历完成后，`head` 指向头节点，`pre` 指向尾节点，主函数中修改 `head` 和 `pre` 的双向节点指向。

```cpp
class Solution {
public:
    Node *pre, *head;
    Node* treeToDoublyList(Node* root) {
        if (root == nullptr) return nullptr;
        dfs(root);
        head->left = pre;
        pre->right = head;
        return head;
    }
    void dfs(Node* cur) {
        if (cur == nullptr) return;
        dfs(cur->left);
        if(pre == nullptr) head = cur;
        else {
            pre->right = cur;
            cur->left = pre;
        }
        pre = cur;
        dfs(cur->right);
    }
};
```



### [54. 二叉搜索树的第k大节点](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof/)

**题意描述**：给定一棵二叉搜索树，请找出其中第 $k$ 大的节点。（1 ≤ k ≤ 二叉搜索树元素个数）

示例：

```latex
输入: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
输出: 4
```

**解题思路**：二叉搜索树的中序遍历为递增序列。若按照右中左顺序遍历就可以得到递减序列。

```cpp
class Solution {
public:
    int ans;
    int kthLargest(TreeNode* root, int k) {
        dfs(root, k);
        return ans;
    }
    void dfs(TreeNode* root, int& k) {
        if (!root) return;
        dfs(root->right, k);
        k--;
        if (k == 0) {
            ans = root->val;
            return;
        }
        if (k) dfs(root->left, k);
    }
};
```



### [55 - I. 二叉树的深度](https://leetcode-cn.com/problems/er-cha-shu-de-shen-du-lcof/)

**题意描述**：输入一棵二叉树的根节点，求该树的深度。从根节点到叶节点依次经过的节点（含根、叶节点）形成树的一条路径，最长路径的长度为树的深度。

示例：

```latex
给定二叉树 [3,9,20,null,null,15,7]，
    3
   / \
  9  20
    /  \
   15   7
返回它的最大深度 3 。
```

**解题思路 1**：DFS 遍历。

```cpp
// DFS 遍历
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    if (!left || !right) return left + right + 1;
    return max(left, right) + 1;
}
```

**解题思路 2**：BFS 求二叉树的层数。

```cpp
int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    int res = 0;
    queue<TreeNode*> que;
    que.push(root);
    while(!que.empty()) {
        int n = que.size();
        while(n--) {
            auto node = que.front();
            que.pop();
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
        res++;
    }
    return res;
}
```



### [55 - II. 平衡二叉树](https://leetcode-cn.com/problems/ping-heng-er-cha-shu-lcof/)

**题意描述**：输入一棵二叉树的根节点，判断该树是不是平衡二叉树。

示例：

```latex
给定二叉树 [3,9,20,null,null,15,7]

    3
   / \
  9  20
    /  \
   15   7
返回 true 。
```

**解题思路**：平衡二叉树的定义是其**任意节点**的左右子树的深度相差不超过 1。本题本质上是需要求二叉树的高度，因此可以套用上一题的解题思路来解本题。

```cpp
class Solution {
public:
    bool res = true;
    bool isBalanced(TreeNode* root) {
        dfs(root);
        return res;
    }
    int dfs(TreeNode* root) {
        if (!root) return 0;
        int left = dfs(root->left), right = dfs(root->right);
        if (abs(left - right) > 1) res = false;
        return max(left, right) + 1;
    }
};
```



### [68 - I. 二叉搜索树的最近公共祖先](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-zui-jin-gong-gong-zu-xian-lcof/)

**题意描述**：给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

**祖先**： 若节点 $p$ 在节点 $root$ 的左（右）子树中，或 $p = root$ ，则称 $root$ 是 $p$ 的祖先。

**最近公共祖先**： 设节点 $root$ 为节点 $p, q$ 的某公共祖先，若其左子节点 `root->left` 和右子节点 `root->right` 都不是 $p, q$ 的公共祖先，则称 $root$ 是最近的公共祖先。

示例：

```latex
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6 
解释: 节点 2 和节点 8 的最近公共祖先是 6。
```

**说明**：

- 所有节点的值都是唯一的；
- `p` 与 `q` 为不同节点且均存在于给定的二叉搜索树中；

**解题思路**：题中两个重要条件：1）树为二叉搜索树；2）树中所有节点的值都是唯一的。根据这两个条件可以得到 `p,q` 与 `root` 的关系：

- 若 `root->val == p->val`，`root` 和 `p` 指向同一个节点；
- 若 `root->val > p->val`，`p` 在 `root` 的左子树中；
- 若 `root->val < p->val`，`p` 在 `root` 的右子树中；

**解法 1：迭代**

```latex
// 算法流程
while root 不为空
	if p,q 都在 root 的右子树中：
		遍历 root->right
	else if p,q 都在 root 的左子树中：
		遍历 root->left
	else 找到了最近公共祖先，break
return root
```

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    while(root) {
        if (root->val > p->val && root->val > q->val) 
            root = root->left;
        else if (root->val < p->val && root->val < q->val) 
            root = root->right;
        else break;
    }
    return root;
}
// 迭代法优化：有序性——> p->val <= q->val
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (p->val > q->val) {
        swap(p, q);
    }
    while(root) {
        if (root->val > q->val) 
            root = root->left;
        else if (root->val < p->val) 
            root = root->right;
        else break;
    }
    return root;
}
```

**解法 2：递归**

```latex
// 算法流程
当 p,q 都在 root 的右子树中，进入递归 root->right 并返回
当 p,q 都在 root 的左子树中，进入递归 root->left 并返回
返回值：最近公共祖先 root
```

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root->val < p->val && root->val < q->val)
        return lowestCommonAncestor(root->right, p, q);
    else if (root->val > p->val && root->val > q->val)
        return lowestCommonAncestor(root->left, p, q);
    return root;
}
```



### [68 - II. 二叉树的最近公共祖先](https://leetcode-cn.com/problems/er-cha-shu-de-zui-jin-gong-gong-zu-xian-lcof/)

**题意描述**：给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

示例：

```latex
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出: 3
解释: 节点 5 和节点 1 的最近公共祖先是节点 3。

```

**说明:**

- 所有节点的值都是唯一的。
- p、q 为不同节点且均存在于给定的二叉树中。

**解题思路**：针对 `root` 是 `p,q` 的最近公共祖先，则可能是以下情况之一：

1. `p` 和 `q` 在 `root` 的子树中，且分别位于 `root` 的两侧；
2. `p == root` ，且 `q` 在 `root` 的左或右子树中；
3. `q == root` ，且 `p` 在 `root` 的左或右子树中。

**函数返回值分析**：

- `left` 和 `right` 同时为空：`root` 的左 / 右子树中都不包含 `p,q` ，返回 `nullptr`；
- `left` 和 `right` 同时不为空：说明 `p,q` 分列在 `root` 的异侧，因此 `root` 为最近公共祖先，返回 `root`；
- `left` 为空，`right` 不为空：`p,q` 都不在 `root` 的左子树中，直接返回 `right`，具体可分为两种情况：
  - `p,q` 其中一个在 `root` 的右子树中，此时 `right` 指向 `p` （假设为 `p`）；
  - `p,q` 两节点都在 `root` 的右子树中，此时 `right` 指向 最近公共祖先节点。
- `left` 不为空，`right` 为空：与情况 3 类似分析过程。

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left && right) return root;
    if (left) return left;
    return right;
}
```





## 动态规划

### [10- I. 斐波那契数列](https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof/)

**题意描述**：输入 $n$ 求斐波那契（Fibonacci）数列的第 `n` 项。

```latex
F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
```

答案需要取模 1e9+7（1000000007），`0 <= n <= 100`。

**解题思路**：题中已经给出了 $f[n]$ 的状态表示，考虑动态规划。

```cpp
int fib(int n) {
    if (n < 2) return n;
    int a = 0, b = 1;
    const int MOD = 1e9 + 7;
    for (int i = 2; i <= n; i++) {
        int t = b;
        b = (a + b) % MOD;
        a = t;
    }
    return b;
}
```

快速幂解法：

```cpp
class Solution {
public:
    const int MOD = 1000000007;
    int fib(int n) {
        if (n < 2) return n;
        vector<vector<long long>> A = {{1, 1}, {1, 0}};
        vector<vector<long long>> res = qmi(A, n - 1);
        return res[0][0];
    }
    vector<vector<long long>> qmi(vector<vector<long long>> A, int k) {
        vector<vector<long long>> ret = {{1, 0}, {0, 1}};
        while(k) {
            if (k & 1) {
                ret = mul(ret, A);
            }
            A = mul(A, A);
            k >>= 1;
        }
        return ret;
    }
    vector<vector<long long>> mul(vector<vector<long long>> A, vector<vector<long long>> B) {
        vector<vector<long long>> res = {{1, 0}, {0, 1}};
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                res[i][j] = (A[i][0] * B[0][j] + A[i][1] * B[1][j])  % MOD;
            }
        }
        return res;
    }
};
```



### [10- II. 青蛙跳台阶问题](https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/)

**题意描述**：每次可以跳 $1$ 级台阶也可以跳 $2$ 级台阶，求青蛙跳上一个 $n$ 级台阶总共有多少种跳法。答案对 $1e9+7$ 取模。

**解题思路**：状态计算：$f[i] = f[i - 1] + f[i - 2]$。特别地，对于第 $0$ 级台阶有 $1$ 种跳法。

```cpp
int numWays(int n) {
    int a = 1, b = 1;
    for (int i = 2; i <= n; i++) {
        int c = (a + b) % 1000000007;
        a = b;
        b = c;
    }
    return b;
}
```



### [63. 股票的最大利润](https://leetcode-cn.com/problems/gu-piao-de-zui-da-li-run-lcof/)

**题意描述**：把某股票的价格按照时间先后顺序存储在数组中，求买卖该股票一次可能获得的最大利润。

示例：

```latex
输入: [7,1,5,3,6,4]
输出: 5

输入: [7,6,4,3,1]
输出: 0
```

**解题思路**：遍历整个数组，每次遍历到一个元素时计算到目前为止的最低价格，并求得当前股价与最低价格之差（差值与本来结果取 $max$）。

```cpp
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX, res = 0;
    for (auto x : prices) {
        minPrice = min(minPrice, x);
        res = max(res, x - minPrice);
    }
    return res;
}
```



### [42. 连续子数组的最大和](https://leetcode-cn.com/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof/)

**题意描述**：输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。要求时间复杂度为O(n)。

示例：

```latex
输入: nums = [-2,1,-3,4,-1,2,1,-5,4]
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
```

**解题思路**：贪心。直接在原数组上进行遍历，只有数组中前一个元素大于 0 时才会对当前连续子数组的最大和有贡献价值。

```cpp
int maxSubArray(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int res = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i - 1] > 0) nums[i] += nums[i - 1];
        res = max(res, nums[i]);
    }
    return res;
}
```



### [47. 礼物的最大价值](https://leetcode-cn.com/problems/li-wu-de-zui-da-jie-zhi-lcof/)

**题意描述**：在一个 $m \times n$ 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，求礼物最大价值。

示例：

```latex
输入: 
[ [1,3,1],
  [1,5,1],
  [4,2,1]]
输出: 12
解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物
```

**解题思路**：DP 状态计算：$\text{f[i][j] = max(f[i][j - 1], f[i - 1][j]) + grid[i][j]}$

```cpp
int maxValue(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> f(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]) + grid[i - 1][j - 1];
        }
    }
    return f[m][n];
}
```



### [46. 把数字翻译成字符串](https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/)

**题意描述**：给定一个数字，我们定义翻译规则：$0 \sim 25$  分别翻译成 $a \sim z$ 。给定一个数字，求一共有多少种不同的翻译方法。

示例：

```latex
输入: 12258
输出: 5
解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"
```

**解题思路**：考虑动态规划。定义状态表示：$dp[i]$ 为将前 $i$ 个数字翻译为字符串的方案数，其中 $dp[0] = 1$。

状态计算：$dp[i] = dp[i - 1] + dp[i - 2]$。

```cpp
int translateNum(int num) {
    string s = to_string(num);
    int n = s.size();
    vector<int> dp(n + 1, 1);   // 边界情况 dp[0] = 1
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        if (i > 1) {
            int t = (s[i - 2] - '0') * 10 + s[i - 1] - '0';
            if (t > 9 && t < 26) {
                dp[i] += dp[i - 2];
            }
        }
    }
    return dp[n];
}
```



### [48. 最长不含重复字符的子字符串](https://leetcode-cn.com/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof/)

**题意描述**：给定一个字符串，求它的最长的不包含重复字符的子字符串的长度。

示例：

```latex
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
```

**解题思路**：哈希表 + 滑动窗口。核心思想：保持窗口 $\text{[j, i]}$ 内不含有重复字母。

```cpp
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> hash;
    int res = 0;
    for (int i = 0, j = 0; i < s.size(); i++) {
        hash[s[i]]++;
        while(hash[s[i]] > 1) hash[s[j++]]--;
        res = max(res, i - j + 1);
    }
    return res;
}
```



## 双指针

### [18. 删除链表的节点](https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/)

**题意描述**：给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。返回删除后的链表的头节点。

示例：

```latex
输入: head = [4,5,1,9], val = 5
输出: [4,1,9]
解释: 给定你链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.
```

说明：

- 题目保证链表中节点的值互不相同
- 若使用 C 或 C++ 语言，你不需要 `free` 或 `delete` 被删除的节点

**解题思路**：题中说了链表节点值互不相同，我们只需按照节点的值进行查找遍历即可。注意要删除的点可能是链表的头节点，因此我们需要设置虚拟头节点。

```cpp
ListNode* deleteNode(ListNode* head, int val) {
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;
    ListNode* cur = dummy;
    while(cur->next) {
        if (cur->next->val == val) {
            cur->next = cur->next->next;
            break;
        }
        cur = cur->next;
    }
    return dummy->next;
}
```



### [22. 链表中倒数第k个节点](https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/)

**题意描述**：输入一个链表，输出该链表中倒数第k个节点。（链表的尾节点是倒数第1个节点。）

示例：

```latex
给定一个链表: 1->2->3->4->5, 和 k = 2.
返回链表 4->5.
```

**解题思路**：双指针。设置指针 $\text{p1}$ 指向 $\text{head}$，指针 $\text{p2}$ 指向 $\text{head}$ 后面的第 $k$ 个节点的位置。同时移动两个指针节点，直到 $\text{p2}$ 指向 $\text{nullptr}$ 为止。 

```cpp
ListNode* getKthFromEnd(ListNode* head, int k) {
    ListNode *p1 = head, *p2 = head;
    while (k--) 
        p2 = p2->next;
    while(p2) {
        p1 = p1->next, p2 = p2->next;
    }
    return p1;
}
```



### [25. 合并两个排序的链表](https://leetcode-cn.com/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof/)

**题意描述**：输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

示例：

```latex
输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
```

**解题思路**：双指针。两个指针分别指向链表当前遍历到的节点，比较大小关系即可。同样本题需要设置虚拟头节点。

```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    auto dummy = new ListNode(-1);
    auto cur = dummy;
    while(l1 && l2) {
        if (l1->val < l2->val) {
            cur->next = l1;
            l1 = l1->next;
        } else {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    if (l1) cur->next = l1;
    else cur->next = l2;
    return dummy->next;
}
```



### [52. 两个链表的第一个公共节点](https://leetcode-cn.com/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof/)

**题意描述**：输入两个链表，找出它们的第一个公共节点。如果两个链表没有交点，返回空节点。

示例：

```latex
给出两个链表如下所示：
A：        a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
输出第一个公共节点c1
```

**解题思路**：双指针。两个指针分别指向两个链表，各自依次往后遍历，直到两个指针指向的链表节点相等为止。循环内，当某个节点遍历到 $\text{nullptr}$ 时，我们让其从另一个链表的位置开始遍历。

```cpp
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    auto p1 = headA, p2 = headB;
    while(p1 != p2) {
        p1 = p1 ? p1->next : headB;
        p2 = p2 ? p2->next : headA;
    }
    return p1;
}
```



### [21. 调整数组顺序使奇数位于偶数前面](https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof/)

**题意描述**：输入一个整数数组，我们需要调整数组中数字的顺序，使得所有奇数在数组的前半部分，所有偶数在数组的后半部分。

示例：

```latex
输入：nums = [1,2,3,4]
输出：[1,3,2,4] 
注：[3,1,2,4] 也是正确的答案之一。
```

**解题思路**：双指针。两个指针分别数组的头和尾，指针 $i$ 从前往后找偶数位置，指针 $j$ 从后往前找奇数位置，满足 $i < j$ 时则交换两个元素的值，直到两个指针位置交错时循环结束。

```cpp
vector<int> exchange(vector<int>& nums) {
    int i = 0, j = nums.size() - 1;
    while(i < j) {
        while(i < j && (nums[i] & 1)) i++;
        while(i < j && (nums[j] % 2 == 0)) j--;
        if (i < j) swap(nums[i], nums[j]);
    }
    return nums;
}
```



### [57. 和为s的两个数字](https://leetcode-cn.com/problems/he-wei-sde-liang-ge-shu-zi-lcof/)

**题意描述**：输入一个递增排序的数组和一个数字 s，在数组中查找两个数，使得它们的和正好是 s。如果有多对数字的和等于 s，则输出任意一对即可。

示例：

```latex
输入：nums = [2,7,11,15], target = 9
输出：[2,7] 或者 [7,2]
```

**解题思路**：双指针。两个指针分别指向数组的头和尾，根据判断条件向中间收缩。

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    int i = 0, j = nums.size() - 1;
    while(i < j) {
        if(nums[i] + nums[j] == target) return {nums[i], nums[j]};
        else if(nums[i] + nums[j] > target) j--;
        else i++;
    }
    return {-1, -1};
}
```



### [58 - I. 翻转单词顺序](https://leetcode-cn.com/problems/fan-zhuan-dan-ci-shun-xu-lcof/)

**题意描述**：输入一个字符串，翻转字符串中单词的顺序，但单词内字符的顺序不变。（标点符号和普通字母一样处理）

示例：

```latex
输入: "  hello world!  "
输出: "world! hello"
```

注意：

- 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。

- 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

**解题思路**：双指针。保持区间 $[i, j)$ 内的字符串恰好是一个单词，然后我们翻转该单词，并用 $k$ 来标记期望输出字符串的长度。循环结束我们 `resize` 字符串长度，并反转字符串即可得到符合要求的字符串。

```cpp
string reverseWords(string s) {
    int k = 0;
    for (int i = 0; i < s.size(); i++) {
        while(i < s.size() && s[i] == ' ') i++;
        if (i == s.size()) break;
        int j = i;
        while(j < s.size() && s[j] != ' ') j++;
        reverse(s.begin() + i, s.begin() + j);
        if (k) s[k++] = ' ';
        while(i < j) s[k++] = s[i++];
    }
    s.resize(k);
    reverse(s.begin(), s.end());
    return s;
}
```



## 排序

### [45. 把数组排成最小的数](https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/)

**题意描述**：输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

示例：

```latex
输入: [10,2]
输出: "102"

输入: [3,30,34,5,9]
输出: "3033459"
```

说明：

- 输出结果可能非常大，我们返回一个字符串即可；
- 拼接起来的数字可能会有前导 0，最后结果不需要去掉前导 0；

**解题思路**：自定义一个排序逻辑，针对数组 $nums$ 中任意两个数字的字符串为 $x$ 和 $y$，规定 $x + y < y + x$ ，则 $x$ 应该排在 $y$ 的前面。

```cpp
string minNumber(vector<int>& nums) {
    sort(nums.begin(), nums.end(), [=](int& a, int& b){
        string stra = to_string(a), strb = to_string(b);
        return stra + strb < strb + stra;
    });

    string res("");
    for (auto x : nums) {
        res += to_string(x);
    }
    return res;
}
```



### [ 61. 扑克牌中的顺子](https://leetcode-cn.com/problems/bu-ke-pai-zhong-de-shun-zi-lcof/)

**题意描述**：从若干副扑克牌中随机抽 5 张牌，判断是不是一个顺子，即这 5 张牌是不是连续的。2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王为 0 ，可以看成任意数字。A 不能视为 14。

示例：

```latex
输入: [1,2,3,4,5]
输出: True

输入: [0,0,1,2,5]
输出: True
```

**解题思路**：对数组进行排序，并统计数组中为 0 的元素个数。5 张牌是顺子的条件：

- 除了大小王之外，不含有重复的元素；
- 数组中最大的元素 - 数组中最小的非零元素 $\leq$ 4；

```cpp
bool isStraight(vector<int>& nums) {
    if (nums.size() == 0) return false;
    sort(nums.begin(), nums.end());
    int cnt = 0;
    while(nums[cnt] == 0) {
        cnt++;
    }
    for (int i = cnt + 1; i < nums.size(); i++) {
        if (nums[i] == nums[i - 1]) return false;
    }
    return nums.back() - nums[cnt] <= 4;
}
```



### [40. 最小的k个数](https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/)

**题意描述**：输入整数数组 `arr` ，找出其中最小的 `k` 个数。

示例：

```latex
输入：arr = [3,2,1], k = 2
输出：[1,2] 或者 [2,1]
```

**解题思路**：排序：快速排序，归并排序，堆排序。

```cpp
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        int n = arr.size();
        quick_sort(arr, 0, n - 1);
        arr.resize(k);
        return arr;
    }
    void quick_sort(vector<int>& arr, int l, int r) {
        if (l >= r) return;
        int i = l - 1, j = r + 1, x = arr[(l + r) / 2];
        while(i < j) {
            do i++; while(arr[i] < x);
            do j--; while(arr[j] > x);
            if (i < j) swap(arr[i], arr[j]);
        }
        quick_sort(arr, l, j), quick_sort(arr, j + 1, r);
    }
};
// 归并排序子函数
void merge_sort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    merge_sort(arr, l, mid), merge_sort(arr, mid + 1, r);
    int k = 0, i = l, j = mid + 1;
    while(i <= mid && j <= r) {
        if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }
    while(i <= mid) tmp[k++] = arr[i++];
    while(j <= r) tmp[k++] = arr[j++];

    for (int i = l, j = 0; i <= r; i++, j++) arr[i] = tmp[j];
}
```



### [41. 数据流中的中位数](https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/)

**题意描述**：设计一个支持以下两种操作的数据结构：

- `void addNum(int num)` ：从数据流中添加一个整数到数据结构中。
- `double findMedian()`：返回目前所有元素的中位数。

示例：

```latex
输入：
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
输出：[null,null,null,1.50000,null,2.00000]
```

**解题思路**：设计两个堆，一个大根堆 `maxHeap`，一个小根堆 `minHeap`。

- 维持大根堆 `maxHeap` 内元素数量**至多**比小根堆 `minHeap` 多一个。
  - 若 `maxHeap.size() == minHeap.size()`，中位数是两者堆顶元素的均值；
  - 若 `maxHeap.size() == minHeap.size() + 1`，中位数是 `maxHeap.top()`； 
- 有序性：`maxHeap.top() <= minHeap.top()`

```cpp
class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int> maxHeap;    // 默认大根堆
    priority_queue<int, vector<int>, greater<int>> minHeap; // 小根堆
    MedianFinder() { }
    
    void addNum(int num) {
        maxHeap.push(num);
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        while (minHeap.size() && maxHeap.top() > minHeap.top()) {
            int x = maxHeap.top(), y = minHeap.top();
            maxHeap.pop();
            minHeap.pop();
            maxHeap.push(y);
            minHeap.push(x);
        }
    }
    
    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
        return maxHeap.top();
    }
};
```



## 位运算

### [15. 二进制中1的个数](https://leetcode-cn.com/problems/er-jin-zhi-zhong-1de-ge-shu-lcof/)

**题意描述**：编写一个函数，输入是一个无符号整数（以二进制串的形式），返回其二进制表达式中数字位数为 '1' 的个数（也被称为 [汉明重量](http://en.wikipedia.org/wiki/Hamming_weight)).）。

**解题思路**：`n&(n-1)` 每次移除最低位上的比特 `1`。

```cpp
int hammingWeight(uint32_t n) {
    int res = 0;
    while(n) {
        res++;
        n &= n - 1;
    }
    return res;
}
```



### [65. 不用加减乘除做加法](https://leetcode-cn.com/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof/)

**题意描述**：写一个函数，求两个整数之和，要求在函数体内不得使用 “+”、“-”、“*”、“/” 四则运算符号。

示例：

```latex
输入: a = 1, b = 1
输出: 2
```

**提示：**

- `a`, `b` 均可能是负数或 0
- 结果不会溢出 32 位整数

**解题思路**：不进位加法：`a^b`，进位：`a&b`。 

```cpp
int add(int a, int b) {
    while(b) {
        int sum = a ^ b;
        int c = (unsigned int)(a & b) << 1;
        a = sum;
        b = c;
    }
    return a;
}
```



### [56 - I. 数组中数字出现的次数](https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/)

**题意描述**：一个整型数组 `nums` 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。

示例：

```latex
输入：nums = [4,1,4,6]
输出：[1,6] 或 [6,1]
```

**解题思路**：位运算，假设答案分别为 $a$ 和 $b$，且 `t = a ^ b`。

- 遍历数组先求 $t$ ；
- 求 $t$ 的第几位上是 $1$；
- 遍历数组求 $a$，`b = t ^ a`；

```cpp
vector<int> singleNumbers(vector<int>& nums) {
    int t = 0;
    for (int &num : nums) {
        t ^= num;
    }
    int i = 0;
    while(!(t >> i & 1)) {
        i++;
    }
    int a = 0;
    for (int &num : nums) {
        if (num >> i & 1) a ^= num;
    }
    return {a, t ^ a};
}
```



### [56 - II. 数组中数字出现的次数 II](https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-ii-lcof/)

**题意描述**：在一个数组 `nums` 中除一个数字只出现一次之外，其他数字都出现了三次。请找出那个只出现一次的数字。

示例：

```latex
输入：nums = [3,4,3,3]
输出：4
```

**解题思路**：$res$ 的第 $i$ 个二进制位就是数组中所有元素的第 $i$ 个二进制位之和除以 $3$ 的余数。

```cpp
int singleNumber(vector<int>& nums) {
    int res = 0;
    for (int i = 0; i < 32; i++) {
        int t = 0;
        for (int &num : nums) {
            t += (num >> i & 1);
        }
        res += (t % 3) << i;
    }
    return res;
}
```





## 数学

### [64. 求1+2+…+n](https://leetcode-cn.com/problems/qiu-12n-lcof/)

**题意描述**：求 `1+2+...+n` ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

示例：

```latex
输入: n = 3
输出: 6
```

**解题思路**：运算符 `&&` 的短路求值特性。

```cpp
int sumNums(int n) {
    int res = n;
    n && (res += sumNums(n - 1));
    return res;
}
```



### [39. 数组中出现次数超过一半的数字](https://leetcode-cn.com/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof/)

**题意描述**：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。你可以假设数组是非空的，并且给定的数组总是存在多数元素。

示例：

```latex
输入: [1, 2, 3, 2, 2, 2, 5, 4, 2]
输出: 2
```

**解题思路**：一共三种解法，其中摩尔投票法为最优解法。

- 解法1：数组由小到大排序，取中位数；
- 解法2：哈希表统计数组元素出现次数；
- **解法3**：摩尔投票法，票数正负抵消；

```cpp
int majorityElement(vector<int>& nums) {
    int res = nums[0], cnt = 1;
    for (int i = 1; i < nums.size(); i++) {
        if (cnt == 0) {
            res = nums[i];
            cnt++;
        } else {
            if (res == nums[i]) cnt++;
            else cnt--;
        }
    }
    return res;
}
```



### [66. 构建乘积数组](https://leetcode-cn.com/problems/gou-jian-cheng-ji-shu-zu-lcof/)

**题意描述**：给定一个数组 $A[0,1,…,n-1]$，请构建一个数组 $B[0,1,…,n-1]$，其中 $B[i]$ 的值是数组 $A$ 中除了下标 $i$ 以外的元素的积, 即 $B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]$。不能使用除法。

示例：

```latex
输入: [1,2,3,4,5]
输出: [120,60,40,30,24]
```

**提示：**

- 所有元素乘积之和不会溢出 32 位整数
- `a.length <= 100000`

**解题思路**：构建前后缀差分数组。

```cpp
vector<int> constructArr(vector<int>& a) {
    if (a.empty()) return {};
    int n = a.size();
    vector<int> b(n, 1);
    for (int i = 1, t = a[0]; i < n; i++) {
        b[i] = t;
        t *= a[i];
    }

    for (int i = n - 2, t = a[n - 1]; i >= 0; i--) {
        b[i] *= t;
        t *= a[i];
    }
    return b;
}
```



### [14- I. 剪绳子](https://leetcode-cn.com/problems/jian-sheng-zi-lcof/)

**题意描述**：将一根长度为 $n$ 的绳子剪成整数长度的 $m$ 段（$m,n$ 都是整数，$n,m>1$），每段绳子的长度记为 $k[0],k[1]...k[m-1]$ 。请问  $k[0] \times k[1] \times...\times k[m-1]$ 可能的最大乘积是多少。

示例：

```latex
输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36
```

提示：`2 <= n <= 58`

**解题思路 1**：**贪心**：将一个正整数 $N$ 拆分成若干个整数有有限种拆法，所以存在最大乘积。<u>重要推论</u>：1）所有绳段长度相等时，乘积最大；2）最优绳段长度为 3；

假设 $N=n_1 + n_2 + ... + n_k$，并且 $n_1 \times n_2 \times n_3 \times ... \times n_k$ 是最大乘积。

- 显然，$1$ 不会出现在其中；
- 如果对于某个 $n_i \geq 5$，那么将 $n_i$ 拆分成 $3 + (n_i - 3)$ ，有 $3 * (n_i - 3) > n_i$
- 如果 $n_i = 4$ ，拆分成 $2 + 2$ 乘积不变，所以假设没有 $4$
- 如果有 $3$ 个连续以上 $2$，那么 $3 \times 3 > 2 \times 2 \times 2$ ，所以替换成 $3$ 乘积更大；

```cpp
int cuttingRope(int n) {
    if (n <= 3) return n - 1;
    int res = 1;
    if (n % 3 == 1) {       // 不能有 4，2 * 2 > 3 * 1
        res = 4;
        n -= 4;
    } else if (n % 3 == 2) {
        res = 2;
        n -= 2;
    } 
    while(n) {      // e 处取
        res *= 3;
        n -= 3;
    }
    return res;
}
```

**解题思路 2**：**动态规划**。定义状态 `f[i]` 为将长度为 $i$ 的绳子剪成若干段后各段长度乘积的最大值。剪第一刀时，我们有 $n - 1$ 种可能的选择，也就是剪出来的第一段绳子的可能长度分别是 $1,2,..,n-1$。因此 $f[i] = max(f[i], max(j * (i - j), j * f[i - j]))$。

减去第一段长度为 $j$ 的绳子之后，可以选择不再剪断，也可选择继续往下剪。若是继续剪，则需要继续求子问题 $f[i - j]$。

```cpp
int cuttingRope(int n) {
    vector<int> f(n + 1, 0);
    f[2] = 1;
    for (int i = 3; i <= n; i++) {
        for (int j = 2; j < i; j++) {
            f[i] = max(f[i], max(j * (i - j), j * f[i - j]));
        }
    }
    return f[n];
}
```



### [57 - II. 和为s的连续正数序列](https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/)

**题意描述**：输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。

示例：

```latex
输入：target = 15
输出：[[1,2,3,4,5],[4,5,6],[7,8]]
```

限制：`1 <= target <= 10^5`

**解题思路**：**双指针（滑动窗口）**。设连续正整数序列的左边界 $left$ 和右边界 $right$ ，则可构建滑动窗口从左向右滑动。循环中，每轮判断滑动窗口内的元素和与目标值 $target$ 的大小关系。若相等则记录，若大于 $target$ 则移动左边界 $left$ （以减少窗口内的元素和），若小于 $target$ 则移动右边界 $right$ （以增加窗口内的元素和）。

```cpp
vector<vector<int>> findContinuousSequence(int target) {
    vector<vector<int>> res;
    int left = 1, right = 2, sum = 3;
    while(left < right) {
        if (sum == target) {
            vector<int> path;
            for (int i = left; i <= right; i++) {
                path.push_back(i);
            }
            res.push_back(path);
        } 
        if (sum >= target) {
            sum -= left;
            left++;
        } else {
            right++;
            sum += right;
        }
    }
    return res;
}
```



### [62. 圆圈中最后剩下的数字](https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/)

**题意描述**：$0,1,···,n-1$ 这 $n$ 个数字排成一个圆圈，从数字 $0$ 开始，每次从这个圆圈里删除第 $m$ 个数字（删除后从下一个数字开始计数）。求出这个圆圈里剩下的最后一个数字。

示例：

```latex
0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。
```

**解题思路**：约瑟夫环问题。由下往上递推：$(\text{当前索引编号} index + m) \mod \text{上一轮元素个数} i$ 

```cpp
int lastRemaining(int n, int m) {
    int index = 0;
    for (int i = 2; i <= n; i++) {
        index = (index + m) % i;
    }
    return index;
}
```

```cpp
// 简化版
int lastRemaining(int n, int m) {
    if (n == 1) return 0;
    return (lastRemaining(n - 1, m) + m) % n;
}
```



## 模拟

### [29. 顺时针打印矩阵](https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/)

**题意描述**：输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

示例：

```latex
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
```

限制：`0 <= matrix.length <= 100`，`0 <= matrix[i].length <= 100`

**解题思路**：代码中以 `st` 数组来标记元素是否被访问过，尽管有点浪费空间。

```cpp
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return {};
    int m = matrix.size(), n = matrix[0].size();
    vector<int> res;
    vector<vector<bool>> st(m, vector<bool>(n, false));
    const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    int x = 0, y = 0, d = 1;
    for (int i = 0; i < m * n; i++) {
        res.emplace_back(matrix[x][y]);
        st[x][y] = true;
        int a = x + dx[d], b = y + dy[d];
        if (a < 0 || a >= m || b < 0 || b >= n || st[a][b]) {
            d = (d + 1) % 4;
            a = x + dx[d], b = y + dy[d];
        }
        x = a, y = b;
    }
    return res;
}
```



### [31. 栈的压入、弹出序列](https://leetcode-cn.com/problems/zhan-de-ya-ru-dan-chu-xu-lie-lcof/)

**题意描述**：输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。

示例：

```latex
输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
输出：true
解释：我们可以按以下顺序执行：
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
```

**解题思路**：见代码。

```cpp
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        if (pushed.size() != popped.size()) return false;
        stack<int> stk;
        int i = 0;
        for (auto x : pushed) {
            stk.push(x);
            while(!stk.empty() && stk.top() == popped[i]) {
                stk.pop();
                i++;
            }
        }
        return stk.empty();
    }
};
```

