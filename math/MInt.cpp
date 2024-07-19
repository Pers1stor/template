#include <bits/stdc++.h>


using namespace std;
using ll = long long;

template <int T>
struct MInt {
    constexpr static int MD = T;
    int x;
    MInt() : x(0) {}
    MInt(int _) : x(norm(_ % MD)) {}
    MInt(ll _) : x(norm(_ % MD)) {}
    MInt(double _) : MInt(ll(_)) {}
    constexpr int norm(int a) const {
        if (a >= MD) a = a - MD;
        if (a < 0) a = a + MD;
        return a;
    }
    constexpr int get() const { return x; }
    constexpr MInt operator+(const int that) const {
        return MInt(norm(x + that));
    }
    constexpr MInt operator-(const int that) const {
        return MInt(norm(x - that));
    }
    constexpr MInt operator*(const int that) const {
        return MInt((ll)x * that % MD);
    }
    constexpr MInt operator/(const int that) const {
        assert(that != 0);  
        return *this / MInt<MD>(that);
    }

    constexpr MInt operator+(const MInt& that) const {
        return MInt(norm(x + that.x));
    }
    constexpr MInt operator-(const MInt& that) const {
        return MInt(norm(x - that.x));
    }
    constexpr MInt operator*(const MInt& that) const {
        return MInt((ll)x * that.x % MD);
    }
    constexpr MInt operator-() const { return MInt(norm(-x)); }
    constexpr MInt operator/(const MInt& that) const {
        assert(that.x != 0);
        return *this * that.inverse();
    }
    constexpr MInt inverse() const {
        int a = x, b = MD, u = 1, v = 0;
        while (b) {
            int t = a / b;
            std::swap(a -= t * b, b);
            std::swap(u -= t * v, v);
        }
        return norm(u);
    }
    void operator+=(const int that) { x = norm(x + that); }
    void operator-=(const int that) { x = norm(x - that); }
    void operator*=(const int that) { x = norm((ll)x * that % MD); }
    void operator/=(const int that) { *this = *this / that; }
    
    void operator+=(const MInt& that) { x = norm(x + that.x); }
    void operator-=(const MInt& that) { x = norm(x - that.x); }
    void operator*=(const MInt& that) { x = norm((ll)x * that.x % MD); }
    void operator/=(const MInt& that) { *this = *this / that; }
    void operator--() { x = norm(x - 1); }
    void operator++() { x = norm(x + 1); }
    friend constexpr bool operator<(const MInt& A, const MInt& B) { return A.get() < B.get(); }
    friend constexpr bool operator>(const MInt& A, const MInt& B) { return A.get() > B.get(); }
    friend constexpr bool operator<=(const MInt& A, const MInt& B) { return A.get() <= B.get(); }
    friend constexpr bool operator>=(const MInt& A, const MInt& B) { return A.get() >= B.get(); }
    friend constexpr bool operator==(const MInt& A, const MInt& B) { return A.get() == B.get(); }
    friend constexpr bool operator!=(const MInt& A, const MInt& B) { return A.get() != B.get(); }
    friend constexpr std::istream& operator>>(istream &is, MInt& A) {
        ll v; is >> v;
        A = MInt(v); return is;
    }
    friend constexpr std::ostream& operator<<(ostream& os, const MInt& x) {
        return os << x.get();
    }
};
constexpr int mod = 1e9 + 7;
using Mint = MInt<mod>;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Mint a = 4, b = 1, c = 2, d = 3;
    cout << b / 3 << endl;
    return 0;
}