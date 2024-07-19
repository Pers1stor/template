
#include <bits/stdc++.h>


using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
// leetcode 2376模板
int digit_dp(int n) {
    auto s = to_string(n);
    int m = s.length(), memo[m][1 << 10];
    memset(memo, -1, sizeof(memo)); // -1 表示没有计算过
    // is_num 为 true 表示得到了一个合法数字
    // is_limit 为 true 表示之前填的数字都和 n 的一样，那么当前位至多填数字 s[i]（否则就超过 n 啦）
    // mask 用来标记选了哪些数字，有些题目用不到
    function<int(int, int, bool, bool)> f = [&](int i, int mask, bool is_limit, bool is_num) -> int {
        if (i == m)
            return is_num; 
        if (!is_limit && is_num && memo[i][mask] != -1)
            return memo[i][mask];
        int res = 0;
        if (!is_num) // 可以跳过当前数位
            res = f(i + 1, mask, false, false);
        int up = is_limit ? s[i] - '0' : 9; 
        for (int d = 1 - is_num; d <= up; ++d) {// 枚举要填入的数字 d
            if ((mask >> d & 1) == 0) // d 不在 mask 中
                res += f(i + 1, mask | (1 << d), is_limit && d == up, true);
        }
        if (!is_limit && is_num)
            memo[i][mask] = res;
        return res;
    };
    return f(0, 0, true, false);
}


vector<int> countNumbers(int n, int num) {
    auto s = to_string(n);
    int m = s.length(), memo[m];
    vector<int> ans(10);
   
    auto f = [&](auto &&f, int i, bool is_limit, bool is_num) -> int {
        if (i == m)
            return cnt; // is_num 为 true 表示得到了一个合法数字
        if (!is_limit && is_num && memo[i][mask] != -1)
            return memo[i];
        int res = 0;
        if (!is_num) // 可以跳过当前数位
            res = f(f, i + 1, mask, false, false, cnt);
        int up = is_limit ? s[i] - '0' : 9; // 如果前面填的数字都和 n 的一样，那么这一位至多填数字 s[i]（否则就超过 n 啦）
        for (int d = 1 - is_num; d <= up; ++d) {// 枚举要填入的数字 d
            res += f(f, i + 1, is_limit && d == up, true);
        }
            
        if (!is_limit && is_num)
            memo[i] = res;
        return f(f, 0, 0, true, false, 0);
    };
    
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int a, b;
    cin >> a >> b;
   
    
    return 0;
}

