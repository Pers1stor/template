#include <bits/stdc++.h>

using namespace std;


struct Comb {
    using ll = long long;
    const int N;
    const int mod = 1e9 + 7;
    vector<ll> fac, invfac;
    // n为组合数的最大值
    Comb(int n) : N(n), fac(n + 2), invfac(n + 2) { init(); };
    ll qpow(ll x, ll p) {
        ll res = 1 % mod; x %= mod;
        for (; p; p >>= 1, x = x * x % mod)
            if (p & 1) res = res * x % mod;
        return res;
    }
    ll inv(ll x) { return qpow(x, mod - 2); };
    void init() {
        fac[0] = 1;
        for (int i = 1; i <= N; ++i) fac[i] = fac[i - 1] * i % mod;
        invfac[N] = inv(fac[N]);
        for (int i = N - 1; i >= 0; --i) invfac[i] = (invfac[i + 1] * (i + 1)) % mod;
    }
    ll C(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
    }
    ll A(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac[n] * invfac[n - m] % mod;
    }
};

int main() {
    Comb comb(1000);
    cout << comb.A(4, 2);
}