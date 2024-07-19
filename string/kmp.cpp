#include <bits/stdc++.h>


using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;


// KMP 模板
vector<int> calc_max_match(string s) {
    vector<int> match(s.length());
    int c = 0;
    for (int i = 1; i < s.length(); i++) {
        char v = s[i];
        while (c && s[c] != v) {
            c = match[c - 1];
        }
        if (s[c] == v) {
            c++;
        }
        match[i] = c;
    }
    return match;
}

// KMP 模板
// 返回 text 中出现 pattern 的位置
vector<int> kmp_search(string text, string pattern) {
    vector<int> match = calc_max_match(pattern);
    vector<int> pos;
    int c = 0;
    for (int i = 0; i < text.length(); i++) {
        char v = text[i];
        while (c && pattern[c] != v) {
            c = match[c - 1];
        }
        if (pattern[c] == v) {
            c++;
        }
        if (c == pattern.length()) {
            pos.push_back(i - pattern.size() + 1);
            c = match[c - 1];
        }
    }
    return pos;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    auto vec = kmp_search("abcdef", "ef");
    for (int x: vec) cout << x << ' ';
    return 0;
}