#include <bits/stdc++.h>

using namespace std;
// 桥
struct Tarjan {
    vector<vector<int>> g;  // 图
    vector<int> dfn;
    vector<int> low;
    vector<bool> vis;
    vector<vector<int>> res;
    int n, times = -1;
    Tarjan(int n, vector<vector<int>> edges) : n(n), g(n), dfn(n, -1), low(n, -1), vis(n) {
        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
    }
    void tarjan(int x, int fa) {
        dfn[x] = low[x] = ++times;
        vis[x] = true;
        for (auto e : g[x]) {
            if (e == fa) continue;
            if (!vis[e]) {
                tarjan(e, x);
                low[x] = min(low[e], low[x]);
                if (low[e] > dfn[x]) {
                    res.push_back({x, e});
                }
            } else {
                low[x] = min(low[x], dfn[e]);
            }
        }
    }
    vector<vector<int>> getBrige() {
        for (int i = 0; i < n; ++i) {
            if (dfn[i] == -1) {
                tarjan(i, -1);
            }
        }
        return res;
    }
};