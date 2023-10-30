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
vi primes;
const int MAX = 5e8 + 5;
bitset<MAX> isPr;

void oddSieve() {    // Source: RR
    isPr.flip();
    isPr[0] = isPr[1] = 0;
    for (int i = 3; i * i < MAX; i += 2) {
        if (isPr[i]) {
            int i2 = i + i;
            for (int j = i * i; j < MAX; j += i2)
                isPr[j] = 0;
        }
    }
    primes.push_back(2);
    for (int i = 3; i < MAX; i += 2)
        if (isPr[i]) primes.push_back(i);
}

ll N, A, B;

void Input() {
    cin >> N >> A >> B;
}

void Solve() {
    cout << upper_bound(ALL(primes), N) - primes.begin() << ' ';
    vi ans;
    for (ll i = B; i < (int)primes.size() && primes[i] <= N; i += A) {
        ans.push_back(primes[i]);
    }
    cout << ans.size() << '\n';
    for (int p : ans)
        cout << p << ' ';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (fopen(input_file, "r")) {
        freopen(input_file, "r", stdin);
        freopen(output_file, "w", stdout);
    }
    oddSieve();
    Input(), Solve();
    return 0;
}