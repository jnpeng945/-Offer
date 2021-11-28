#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Solution {
private:
    vector<int> res;
    string s;
public:
    vector<int> printNumbers(int n) {
        s.resize(n, ' ');
        dfs(n, 0);
        return res;
    }
    void dfs(int n, int u) {
        if (u == n) {
            save();
            return;
        }
        for (int i = 0; i <= 9; i++) {
            s[u] = i + '0';
            dfs(n, u + 1);
        }
    }
    // 除去首部的 0
    void save() {
        int ptr = 0;
        while(ptr < s.size() && s[ptr] == '0') ptr++;
        if (ptr != s.size()) {
            res.emplace_back(stoi(s.substr(ptr)));
        }
    }
};

int main() {
    int n = 2;
    Solution A;
    auto res = A.printNumbers(n);
    return 0;
}