using ll = long long;
ll ksm(ll base, ll power, ll mod) {
    ll res = 1;
    while (power) {
        if (power % 2) res = res * base % mod;
        base = base * base % mod;
        power >>= 1;
    }
    return res;
}