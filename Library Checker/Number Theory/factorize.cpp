// Created by BJMinhNhut
#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define ALL(a) (a).begin(), (a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define MASK(i) (1ll << (i))
#define BIT(t, i) (((t) >> (i)) & 1)
#define input_file "inputf.in"
#define output_file "outputf.in"

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;
typedef pair<int, int> ii;

/***Common Functions***/
template <class T>
bool minimize(T& a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
bool maximize(T& a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

/***End of Template***/
const int rounds = 20;

long long modPow(ll a, ll b, ll MOD) {
    ll res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % MOD;
        a = 1ll * a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long modMul(long long a, long long b, long long mod) {
    long long result = 0;
    while (b) {
        if (b & 1) result = (result + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return result;
}

// checks whether a is a witness that n is not prime, 1 < a < n
bool witness(long long a, long long n) {
    // check as in Miller Rabin Primality Test described
    long long u = n - 1;
    int t = 0;
    while (u % 2 == 0) {
        t++;
        u >>= 1;
    }
    long long next = modPow(a, u, n);
    if (next == 1) return false;
    long long last;
    for (int i = 0; i < t; ++i) {
        last = next;
        next = modMul(last, last, n);
        if (next == 1) {
            return last != n - 1;
        }
    }
    return next != 1;
}

// Checks if a number is prime with prob 1 - 1 / (2 ^ it)
//  D(miller_rabin(99999999999999997LL) == 1);
//  D(miller_rabin(9999999999971LL) == 1);
//  D(miller_rabin(7907) == 1);
bool miller_rabin(long long n, int it = rounds) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 0; i < it; ++i) {
        long long a = rand() % (n - 1) + 1;
        if (witness(a, n)) {
            return false;
        }
    }
    return true;
}

long long pollard_rho(long long n) {
    long long x, y, i = 1, k = 2, d;
    x = y = rand() % n;
    while (1) {
        ++i;
        x = modMul(x, x, n);
        x += 2;
        if (x >= n) x -= n;
        if (x == y) return 1;
        d = __gcd(abs(x - y), n);
        if (d != 1) return d;
        if (i == k) {
            y = x;
            k *= 2;
        }
    }
    return 1;
}

// Returns a list with the prime divisors of n
vector<long long> factorize(long long n) {
    vector<long long> ans;
    if (n == 1) return ans;
    if (miller_rabin(n)) {
        ans.push_back(n);
    } else {
        long long d = 1;
        while (d == 1)
            d = pollard_rho(n);
        vector<long long> dd = factorize(d);
        ans = factorize(n / d);
        for (int i = 0; i < (int)dd.size(); ++i)
            ans.push_back(dd[i]);
    }
    return ans;
}

ll n;

void Input() {
    cin >> n;
}

void Solve() {
    vll ans = factorize(n);
    reverse(ALL(ans));
    cout << ans.size() << ' ';
    for (ll f : ans)
        cout << f << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (fopen(input_file, "r")) {
        freopen(input_file, "r", stdin);
        freopen(output_file, "w", stdout);
    }
    srand(time(NULL));
    int t;
    cin >> t;
    while (t--)
        Input(), Solve();
    return 0;
}

// not yet AC