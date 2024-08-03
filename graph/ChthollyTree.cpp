#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Node {
    ll l, r;
    mutable ll v;
    Node(ll l, ll r, ll v) : l(l), r(r), v(v) {}
    bool operator<(const Node& o) const { return l < o.l; }
};
struct ChthollyTree {
    
    set<Node> tree;
    ChthollyTree() {}
    auto split(ll pos) {
        auto it = tree.lower_bound(Node(pos, 0, 0));
        if (it != tree.end() && it->l == pos) return it;
        it--;
        ll l = it->l, r = it->r, v = it->v;
        tree.erase(it);
        tree.insert(Node(l, pos - 1, v));
        return tree.insert(Node(pos, r, v)).first;
    }

    // 区间推平，给这个区间赋予同一个值 
    void assign(ll l, ll r, ll v) {
        auto end = split(r + 1), begin = split(l);
        tree.erase(begin, end);
        tree.insert(Node(l, r, v));
    }

    // 整个区间进行加法运算 
    void add(ll l, ll r, ll v) {
        auto end = split(r + 1);
        for (auto it = split(l); it != end; it++)
            it->v += v;
    }

    ll querySum(int l, int r) {
        auto itr = split(r + 1), itl = split(l);
        ll res = 0;
        for (auto it = itl; it != itr; ++it) {
            res += (it->r - it->l + 1) * it->v;
        }
        return res;
    }
    
    ll queryKth(ll l, ll r, ll k) {
        auto end = split(r + 1);
        vector<pair<ll, ll>> v;
        for (auto it = split(l); it != end; ++it) {
            v.push_back(make_pair(it->v, it->r - it->l + 1));
        }
            
        sort(v.begin(), v.end());
        for (int i = 0; i < v.size(); ++i) {
            k -= v[i].second;
            if (k <= 0) return v[i].first;
        }
        return -1;
    }
};
