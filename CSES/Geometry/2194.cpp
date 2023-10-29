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
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
    bool operator<(const Point& other) const {
        return (x == other.x && y < other.y) || x < other.x;
    }
    ll norm() const { return x * x + y * y; }    // x^2 + y^2
};

int n;
const int N = 2e5 + 5;
vector<Point> a;

void Input() {
    cin >> n;
    a.resize(n);
    FOR(i, 0, n - 1) cin >> a[i].x >> a[i].y;
}

const int MAX = 1e9;
// return squared distance
ll closestPair(vector<Point> pt, Point& p, Point& q) {
    if (a.size() < 2) return -1;
    // sort by y
    sort(pt.begin(), pt.end(),
         [](const Point& a, const Point& b) { return (a.y == b.y && a.x < b.x) || a.y < b.y; });
    ll sqrDist = (a[1] - a[0]).norm();
    p = a[0], q = a[1];

    set<Point> st;    // ordered set by x
    for (Point a : pt) {
        ll d = sqrt(sqrDist);
        Point cur(a.x - d, -MAX - 1);
        while (1) {
            auto it = st.upper_bound(cur);
            if (it == st.end()) break;
            cur = *it;
            if (cur.x > a.x + d) break;
            if (cur.y < a.y - d) {
                st.erase(it);
                continue;
            }
            if (minimize(sqrDist, (a - cur).norm())) p = a, q = cur;
        }
        st.insert(a);
    }
    return sqrDist;
}

void Solve() {
    Point p, q;
    ll dist = closestPair(a, p, q);
    cout << dist;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (fopen(input_file, "r")) {
        freopen(input_file, "r", stdin);
        freopen(output_file, "w", stdout);
    }
    Input(), Solve();
    return 0;
}