#include <bits/stdc++.h>


using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

// 树状数组
template<typename T>
struct BIT {
    const int n;
    std::vector<T> tree;
    BIT(int n) : n(n), tree(n + 1) {};
    T query(int x) {
        T res = 0;
        for (int i = x; i > 0; i -= (i & -i)) {
            res += tree[i];
        }
        return res;
    }
    void modify(int l, T z) {
        if (l <= 0) return;
        for (int i = l; i <= n; i += (i & -i)) {
            tree[i] += z;
        }
    }
    T rangeQuery(int l, int r) {
        return query(std::min(n, r)) - query(std::max(0, l - 1));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    return 0;
}


