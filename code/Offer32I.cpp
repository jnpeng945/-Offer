#include<iostream>
#include<queue>
#include<vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


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

int main() {
    

}