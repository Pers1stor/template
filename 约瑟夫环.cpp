// 约瑟夫环
int cir(int n, int m) {
    int p = 0;
    for (int i = 2; i <= n; i++) {
        p = (p + m) % i;
    }
    return p;  // 返回数组的下标
}