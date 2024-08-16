// 树状数组
template<typename T>
struct BIT {
    const int n;
    std::vector<T> tree;
    BIT(int n) : n(n), tree(n + 1) {};
    // 查询 [1, x] 的前缀和
    T query(int x) {
        T res = 0;
        for (int i = x; i > 0; i -= (i & -i)) {
            res += tree[i];
        }
        return res;
    }
    // 下标为 l 的位置加上 x
    void add(int l, T x) {
        if (l <= 0) return;
        for (int i = l; i <= n; i += (i & -i)) {
            tree[i] += x;
        }
    }
    // 查询 l ~ r 的和
    T rangeQuery(int l, int r) {
        return query(std::min(n, r)) - query(std::max(0, l - 1));
    }
};




