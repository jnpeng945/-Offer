#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

string reverseLeftWords(string s, int k) {
    int n = s.size();
    reverse(s.begin(), s.end());
    reverse(s.begin(), s.begin() + n - k);
    reverse(s.begin() + n - k, s.end());
    return s;
}

int main() {
    string s = "abcdefg";
    int k = 2;
    cout << reverseLeftWords(s, k) << endl;
    return 0;
}