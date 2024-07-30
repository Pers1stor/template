#include <bits/stdc++.h>

using namespace std;
//区间和
class SegmentTree1 {
    class Node {
    public:
        int val, add;
        Node* left, * right;
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

//区间最值
class SegmentTree2 {
    class Node {
    public:
        int val, add;
        Node* left, * right;
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

//区间覆盖
class SegmentTree3 {

    struct Node {
        Node* left;
        Node* right;
        // 表示当前区间是否被覆盖
        bool cover;
        int add;
    };

    const int N = 1e9;
    Node* root = new Node();

    void update(Node* node, int start, int end, int l, int r, int val) {
        if (l <= start && end <= r) {
            // 1 表示复盖；-1 表示取消覆盖
            node->cover = val == 1;
            node->add = val;
            return;
        }
        int mid = (start + end) >> 1;
        pushDown(node, mid - start + 1, end - mid);
        if (l <= mid) update(node->left, start, mid, l, r, val);
        if (r > mid) update(node->right, mid + 1, end, l, r, val);
        pushUp(node);
    }

    bool query(Node* node, int start, int end, int l, int r) {
        if (l <= start && end <= r) return node->cover;
        int mid = (start + end) >> 1;
        pushDown(node, mid - start + 1, end - mid);
        // 查询左右子树是否被覆盖
        bool ans = true;
        if (l <= mid) ans = ans && query(node->left, start, mid, l, r);
        if (r > mid) ans = ans && query(node->right, mid + 1, end, l, r);
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