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
struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
    Point operator+(const Point& other) const { return Point(other.x + x, other.y + y); }
    Point operator-(const Point& other) const { return Point(other.x - x, other.y - y); }
    ll cross(const Point& other) const { return (x * other.y) - (y * other.x); }
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
};

Point a, b, c;

void Input() {
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
}

void Solve() {
    ll res = (b - a).cross(c - b);
    if (res == 0)
        cout << "TOUCH\n";
    else if (res > 0)
        cout << "LEFT\n";
    else
        cout << "RIGHT\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (fopen(input_file, "r")) {
        freopen(input_file, "r", stdin);
        freopen(output_file, "w", stdout);
    }
    int t;
    cin >> t;
    while (t--)
        Input(), Solve();
    return 0;
}