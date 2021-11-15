#include<iostream>
#include<string>

using namespace std;

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

int main() {
    string s = "We are happy.";
    cout << replaceSpace(s) << endl;
    return 0;
}