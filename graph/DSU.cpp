#include <bits/stdc++.h>
using namespace std;
// 并查集
struct DSU {
    vector<int> fa, siz;
    DSU(int n) : fa(n + 1), siz(n + 1, 1) { iota(fa.begin(), fa.end(), 0); };
    int find(int x) {
        while (x != fa[x]) x = fa[x] = fa[fa[x]];
        return x;
    }
    int size(int x) { return siz[find(x)]; }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        siz[y] += siz[x];
        fa[x] = y;
        return true;
    }
};

