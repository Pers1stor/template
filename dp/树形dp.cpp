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