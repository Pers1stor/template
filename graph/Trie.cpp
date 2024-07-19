#include <bits/stdc++.h>


using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

//自定义第二维长度
template <const int M>
struct Trie {
    vector<array<int, M>> trie;
    vector<bool> exist;
    vector<int> cnt;

    Trie() { init(); }
    void init() {
        trie.emplace_back(array<int, M>{});
        exist.resize(1);
        cnt.resize(1);
    }
    void insert(const string& str) {
        int now = 0, p;
        for (auto& c : str) {
            p = pos(c);
            if (!trie[now][p]) {
                trie[now][p] = trie.size();
                trie.emplace_back(array<int, M>{});
                exist.emplace_back(false);
                cnt.emplace_back(0);
            }
            now = trie[now][p];
            ++cnt[now];
        }
        exist[now] = true;
    }
    int queryPre(const string& str) {
        int now = 0, p;
        for (auto& c : str) {
            p = pos(c);
            if (!trie[now][p]) {
                return 0;
            }
            now = trie[now][p];
        }
        return cnt[now];
    }
    bool queryStr(const string& str) {
        int now = 0, p;
        for (auto& c : str) {
            p = pos(c);
            if (!trie[now][p]) {
                return false;
            }
            now = trie[now][p];
        }
        return exist[now];
    }
    int pos(char ch) {
    	//自定义位置参数
        if (ch >= 'a' && ch <= 'z') return ch - 'a';
        if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 26;
        if (ch >= '0' && ch <= '9') return ch - '0' + 52;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Trie<26> trie;
    trie.insert("zabc");
    trie.insert("zabs");
    trie.insert("zc");
    trie.insert("#");
    cout << trie.queryPre("zab") << endl;
    cout << trie.queryPre("za") << endl;
    cout << trie.queryPre("z") << endl;
    cout << trie.queryPre("#") << endl;
    return 0;
}


