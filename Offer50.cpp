#include<iostream>
#include<string>
#include<unordered_map>

using namespace  std;

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
int main() {
    string s = "abaccdeff";
    cout << firstUniqChar(s) << endl;
    return 0;
}