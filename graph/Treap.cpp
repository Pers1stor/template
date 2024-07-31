#include <bits/stdc++.h>
// 无旋Treap

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

struct Treap {
    struct Node {
        int lson, rson;  // 左右子结点
        int key;         // 值
        int w;           // 随机权重
        int size;        // 自身+子树 大小
    };
    Treap(int n) : tree(n) {}
    int idx;  // 索引分配器
    int root;
    vector<Node> tree;  // fhq treap

    inline int create_node(int key) {
        tree[++idx].key = key;
        tree[idx].w = rand();
        tree[idx].size = 1;
        return idx;
    }

    inline void push_up(int rt) {
        tree[rt].size = tree[tree[rt].lson].size + tree[tree[rt].rson].size + 1;
    }

    inline void split(int rt, int key, int &ansl, int &ansr) {
        if (!rt) {
            ansl = ansr = 0;
        } else {
            if (tree[rt].key <= key) {
                ansl = rt;
                split(tree[rt].rson, key, tree[rt].rson, ansr);
            } else {
                ansr = rt;
                split(tree[rt].lson, key, ansl, tree[rt].lson);
            }
            push_up(rt);
        }
    }

    inline int merge(int ansl, int ansr) {
        // ansl 中的所有key一定都小于 ansr中的所有key
        if (!ansl || !ansr) {
            return ansl + ansr;
        } else {
            if (tree[ansl].w < tree[ansr].w) {                   // 按照小根堆处理，父结点的w小于所有子结点的w
                tree[ansl].rson = merge(tree[ansl].rson, ansr);  // 传参顺序不能反
                push_up(ansl);
                return ansl;
            } else {
                tree[ansr].lson = merge(ansl, tree[ansr].lson);  // 传参顺序不能反
                push_up(ansr);
                return ansr;
            }
        }
    }

    inline void insert(int key) {
        int ansl = 0, ansr = 0;
        split(root, key, ansl, ansr);
        root = merge(merge(ansl, create_node(key)), ansr);
    }

    inline void remove(int key) {
        int x, y, z;
        split(root, key, x, z);
        split(x, key - 1, x, y);
        y = merge(tree[y].lson, tree[y].rson);
        root = merge(merge(x, y), z);
    }

    inline int query_rank(int key) {  // 查询key的排名(比key小的数的个数+1)
        int ans, x, y;
        split(root, key - 1, x, y);
        ans = tree[x].size + 1;
        root = merge(x, y);
        return ans;
    }

    inline int query_key(int rank) {
        int ptr = root;
        while (ptr) {
            if (tree[tree[ptr].lson].size + 1 == rank) {
                return tree[ptr].key;
            } else if (tree[tree[ptr].lson].size + 1 > rank) {
                ptr = tree[ptr].lson;
            } else {
                rank -= tree[tree[ptr].lson].size + 1;
                ptr = tree[ptr].rson;
            }
        }
        return -1;
    }

    inline int max_less(int key) { // 小于 key 的最大值
        int ans, x, y;
        split(root, key - 1, x, y);
        int ptr = x;
        while (tree[ptr].rson) {
            ptr = tree[ptr].rson;
        }
        ans = tree[ptr].key;
        root = merge(x, y);
        return ans;
    }

    inline int min_greater(int key) { // 大于 key 的最小值
        int ans, x, y;
        split(root, key, x, y);
        int ptr = y;
        while (tree[ptr].lson) {
            ptr = tree[ptr].lson;
        }
        ans = tree[ptr].key;
        root = merge(x, y);
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Treap treap(1e5);
    for (int i = 0; i < 10; ++i) treap.insert(i);
    cout << treap.query_rank(9) << endl;
    cout << treap.min_greater(5) << endl;
    cout << treap.max_less(-1) << endl;
    return 0;
}
