#include <bits/stdc++.h>


using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

#include <bits/stdc++.h>


using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

// 换根dp
//树的高度： 1. 先以节点 0 为根节点进行dfs，生成初始的每个节点高度 h
//          2. 然后再以节点 0 为根节点再次dfs，进行换根处理
//              a. 设当前根节点为 x，找到其子节点中的最大高度 maxH 和次大高度 secondH，更新根节点的树高度为 height[x] = maxH + 1;
//              b.枚举其此节点进行换根处理，那么 h[node] 就需要进行更新：
//                  如果 h[x] == maxH，即这个子节点就是提供最大高度的子节点。当前根节点变为子节点时，高度发生变化，h[x] = secondMaxH + 1
//                  否则，当前根节点变为子节点时，高度不变， h[x] = maxH + 1;




//打家劫舍3推广到一般树
void solve() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> happy(n + 1);
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> happy[i];
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    function<pii(int, int)> dfs = [&](int x, int fa) -> pii {
        pii res{happy[x], 0};
        for (int y: g[x]) {
            if (y == fa) continue;
            auto [r, not_r] = dfs(y, x);
            res.first += not_r;
            res.second += max(r, not_r);
        }
        return res;
    };
    auto p = dfs(1, 0);
       
    cout << max(p.first, p.second);
}
//P1352
void solve2() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> happy(n + 1);
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> happy[i];
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    function<pii(int, int)> dfs = [&](int x, int fa) -> pii {
        pii res{happy[x], 0};
        for (int y: g[x]) {
            if (y == fa) continue;
            auto [r, not_r] = dfs(y, x);
            res.first += not_r;
            res.second += max(r, not_r);
        }
        return res;
    };
    auto p = dfs(1, 0);
       
    cout << max(p.first, p.second);
}
// P5765
void solve3() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    if (n == 1) {
        cout << 1;
        return;
    }
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<vector<int>> f(n + 1, vector<int>(10, INT_MAX)); // f[i][x] 以 i 为跟的
    function<void(int, int)> dfs = [&](int x, int fa) -> void {
        for (int i = 1; i < 10; ++i) f[x][i] = i;
        for (int y: g[x]) {
            if (y == fa) continue;
            dfs(y, x);
            for (int i = 1; i < 10; ++i) {
                int mn = 1e9;
                for (int j = 1; j < 10; ++j) {
                    if (i == j) continue;
                    mn = min(mn, f[y][j]);
                }
                f[x][i] += mn;
            }
        }
        
    };
    dfs(1, 0);
    int ans = 1e9;
    for (int i = 0; i < 10; ++i) ans = min(ans, f[1][i]);
    cout << ans;
}

int main() {
    
    return 0;
}