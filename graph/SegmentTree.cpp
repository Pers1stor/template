#include <bits/stdc++.h>

using namespace std;

using namespace std;

template <typename T>
class SegTreeLazyRangeAdd {
    vector<T> tree, lazy;
    vector<T>* arr;
    int n, root, n4, end;
    // 从儿子节点更新当前节点
    void maintain(int cl, int cr, int p) {
        int cm = cl + (cr - cl) / 2;
        if (cl != cr && lazy[p]) {
            lazy[p * 2] += lazy[p];
            lazy[p * 2 + 1] += lazy[p];
            tree[p * 2] += lazy[p] * (cm - cl + 1);
            tree[p * 2 + 1] += lazy[p] * (cr - cm);
            lazy[p] = 0;
        }
    }

    T range_sum(int l, int r, int cl, int cr, int p) {
        // [l, r] 为查询区间, [cl, cr] 为当前节点包含的区间, p 为当前节点的编号
        // 当前区间为询问区间的子集时直接返回当前区间的和
        if (l <= cl && cr <= r) return tree[p];
        int m = cl + (cr - cl) / 2;
        T sum = 0;
        maintain(cl, cr, p);
        if (l <= m) sum += range_sum(l, r, cl, m, p * 2);
        if (r > m) sum += range_sum(l, r, m + 1, cr, p * 2 + 1);
        return sum;
    }

    void range_add(int l, int r, T val, int cl, int cr, int p) {
        if (l <= cl && cr <= r) {
            lazy[p] += val;
            tree[p] += (cr - cl + 1) * val;
            return;
        }
        int m = cl + (cr - cl) / 2;
        maintain(cl, cr, p);
        if (l <= m) range_add(l, r, val, cl, m, p * 2);
        if (r > m) range_add(l, r, val, m + 1, cr, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

    void build(int s, int t, int p) {
        if (s == t) {
            tree[p] = (*arr)[s];
            return;
        }
        int m = s + (t - s) / 2;
        build(s, m, p * 2);
        build(m + 1, t, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

public:
    SegTreeLazyRangeAdd<T>(vector<T> v) {
        n = v.size();
        n4 = n * 4;
        tree = vector<T>(n4, 0);
        lazy = vector<T>(n4, 0);
        arr = &v;
        end = n - 1;
        root = 1;
        build(0, end, 1);
        arr = nullptr;
    }

    T range_sum(int l, int r) { return range_sum(l, r, 0, end, root); }

    void range_add(int l, int r, T val) { range_add(l, r, val, 0, end, root); }
};

template <typename T>
class SegTreeLazyRangeSet {
    vector<T> tree, lazy;
    vector<T>* arr;
    int n, root, n4, end;

    void maintain(int cl, int cr, int p) {
        int cm = cl + (cr - cl) / 2;
        if (cl != cr && lazy[p]) {
            lazy[p * 2] = lazy[p];
            lazy[p * 2 + 1] = lazy[p];
            tree[p * 2] = lazy[p] * (cm - cl + 1);
            tree[p * 2 + 1] = lazy[p] * (cr - cm);
            lazy[p] = 0;
        }
    }

    T range_sum(int l, int r, int cl, int cr, int p) {
        if (l <= cl && cr <= r) return tree[p];
        int m = cl + (cr - cl) / 2;
        T sum = 0;
        maintain(cl, cr, p);
        if (l <= m) sum += range_sum(l, r, cl, m, p * 2);
        if (r > m) sum += range_sum(l, r, m + 1, cr, p * 2 + 1);
        return sum;
    }

    void range_set(int l, int r, T val, int cl, int cr, int p) {
        if (l <= cl && cr <= r) {
            lazy[p] = val;
            tree[p] = (cr - cl + 1) * val;
            return;
        }
        int m = cl + (cr - cl) / 2;
        maintain(cl, cr, p);
        if (l <= m) range_set(l, r, val, cl, m, p * 2);
        if (r > m) range_set(l, r, val, m + 1, cr, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

    void build(int s, int t, int p) {
        if (s == t) {
            tree[p] = (*arr)[s];
            return;
        }
        int m = s + (t - s) / 2;
        build(s, m, p * 2);
        build(m + 1, t, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

public:
    SegTreeLazyRangeSet<T>(vector<T> v) {
        n = v.size();
        n4 = n * 4;
        tree = vector<T>(n4, 0);
        lazy = vector<T>(n4, 0);
        arr = &v;
        end = n - 1;
        root = 1;
        build(0, end, 1);
        arr = nullptr;
    }

    T range_sum(int l, int r) { return range_sum(l, r, 0, end, root); }

    void range_set(int l, int r, T val) { range_set(l, r, val, 0, end, root); }
};

//Node 版本
// 区间和
class SegmentTree {
    class Node {
    public:
        int val, add;
        Node *left, *right;
        Node() : val(0), add(0), left(nullptr), right(nullptr) {}
    };
    const int N = 1e9;
    Node* root = new Node();
    void update(Node* node, int l, int r, int L, int R, int val) {
        if (L <= l && r <= R) {
            node->val += (r - l + 1) * val;
            node->add += val;
            return;
        }
        int mid = (l + r) >> 1;
        pushDown(node, mid - l + 1, r - mid);
        if (L <= mid) update(node->left, l, mid, L, R, val);
        if (R > mid) update(node->right, mid + 1, r, L, R, val);
        pushUp(node);
    }
    int query(Node* node, int l, int r, int L, int R) {
        if (L <= l && r <= R) return node->val;
        int mid = (l + r) >> 1, ans = 0;
        pushDown(node, mid - l + 1, r - mid);
        if (L <= mid) ans += query(node->left, l, mid, L, R);
        if (R > mid) ans += query(node->right, mid + 1, r, L, R);
        return ans;
    }

    void pushUp(Node* node) {
        node->val = node->left->val + node->right->val;
    }
    void pushDown(Node* node, int leftNum, int rightNum) {
        if (node->left == nullptr) node->left = new Node();
        if (node->right == nullptr) node->right = new Node();
        if (node->add == 0) return;
        node->left->val += node->add * leftNum;
        node->right->val += node->add * rightNum;
        // 对区间进行「加减」的更新操作，下推懒惰标记时需要累加起来，不能直接覆盖
        node->left->add += node->add;
        node->right->add += node->add;
        node->add = 0;
    }
};

// 区间最值
class SegmentTree2 {
    class Node {
    public:
        int val, add;
        Node *left, *right;
        Node() : val(0), add(0), left(nullptr), right(nullptr) {}
    };
    const int N = 1e9;
    Node* root = new Node();
    void update(Node* node, int l, int r, int L, int R, int val) {
        if (L <= l && r <= R) {
            node->val = (r - l + 1) * val;
            node->add += val;
            return;
        }
        int mid = (l + r) >> 1;
        pushDown(node, mid - l + 1, r - mid);
        if (L <= mid) update(node->left, l, mid, L, R, val);
        if (R > mid) update(node->right, mid + 1, r, L, R, val);
        pushUp(node);
    }
    int query(Node* node, int l, int r, int L, int R) {
        if (L <= l && r <= R) return node->val;
        int mid = (l + r) >> 1, ans = 0;
        pushDown(node, mid - l + 1, r - mid);
        if (L <= mid) ans = query(node->left, l, mid, L, R);
        if (R > mid) ans = max(ans, query(node->right, mid + 1, r, L, R));
        return ans;
    }

    void pushUp(Node* node) {
        node->val = max(node->left->val, node->right->val);
    }
    void pushDown(Node* node, int leftNum, int rightNum) {
        if (node->left == nullptr) node->left = new Node();
        if (node->right == nullptr) node->right = new Node();
        if (node->add == 0) return;
        node->left->val += node->add;
        node->right->val += node->add;
        // 对区间进行「加减」的更新操作，下推懒惰标记时需要累加起来，不能直接覆盖
        node->left->add += node->add;
        node->right->add += node->add;
        node->add = 0;
    }
};
// 区间覆盖
class SegmentTree3 {
    struct Node {
        // 表示当前区间是否被覆盖
        bool cover;
        int add;
        Node *left, *right;
    };

    const int N = 1e9;
    Node* root = new Node();

    void update(Node* node, int l, int r, int L, int R, int val) {
        if (L <= l && r <= R) {
            // 1 表示复盖；-1 表示取消覆盖
            node->cover = val == 1;
            node->add = val;
            return;
        }
        int mid = (l + r) >> 1;
        pushDown(node, mid - l + 1, r - mid);
        if (L <= mid) update(node->left, l, mid, L, R, val);
        if (R > mid) update(node->right, mid + 1, r, L, R, val);
        pushUp(node);
    }

    bool query(Node* node, int l, int r, int L, int R) {
        if (L <= l && r <= R) return node->cover;
        int mid = (l + r) >> 1;
        pushDown(node, mid - l + 1, r - mid);
        // 查询左右子树是否被覆盖
        bool ans = true;
        if (L <= mid) ans = ans && query(node->left, l, mid, L, R);
        if (R > mid) ans = ans && query(node->right, mid + 1, r, L, R);
        return ans;
    }

    void pushUp(Node* node) {
        // 向上更新
        node->cover = node->left->cover && node->right->cover;
    }

    void pushDown(Node* node, int leftNum, int rightNum) {
        if (node->left == nullptr) node->left = new Node();
        if (node->right == nullptr) node->right = new Node();
        if (node->add == 0) return;
        node->left->cover = node->add == 1;
        node->right->cover = node->add == 1;
        node->left->add = node->add;
        node->right->add = node->add;
        node->add = 0;
    }
};
