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
};

typedef long double ld;
const ld EPS = 1E-9;

ll cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

// 0: colinear, -1: turn right, 1: turn left
int ccw(Point a, Point b, Point c) {
    ll res = cross(b - a, c - a);
    if (res == 0) return 0;
    return res < 0 ? -1 : 1;
}

struct Line {
    ld a, b, c;
    Line() {}
    Line(Point s, Point t) {
        a = s.y - t.y;
        b = t.x - s.x;
        c = -a * s.x - b * s.y;
        norm();
    }
    void norm() {
        ld z = sqrt(a * a + b * b);
        if (abs(z) > EPS) a /= z, b /= z, c /= z;
    }
    // can be negative
    ld dist(Point p) const { return a * p.x + b * p.y + c; }
};

inline bool intersect_1d(ld a, ld b, ld c, ld d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d) + EPS;
}
bool segmentIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    if (ccw(c, a, d) == 0 && ccw(c, b, d) == 0)
        return intersect_1d(a.x, b.x, c.x, d.x) && intersect_1d(a.y, b.y, c.y, d.y);
    return ccw(a, b, c) != ccw(a, b, d) && ccw(c, d, a) != ccw(c, d, b);
}

// 0: outside, 1: inside, 2: boundary
int pointInPolygon(Point* a, int n, Point pt) {    // O(n)
    bool intersect = 0;
    for (int i = 0; i < n; ++i) {
        if (segmentIntersect(pt, pt, a[i], a[(i + 1) % n])) return 2;    // boundary
        intersect ^= segmentIntersect(pt, Point(2e9, pt.y), a[i], a[(i + 1) % n]);
        intersect ^= a[i].y != a[(i + 1) % n].y && pt.y == a[i].y &&
                     pt.x < a[i].x;    // intersect at a point of polygon
        // cout << i << ' ' << intersect << '\n';
    }
    return intersect & 1;
}

const int N = 1e3 + 5;
Point a[N];
int n, m;

void Input() {
    cin >> n >> m;
    FOR(i, 0, n - 1) cin >> a[i].x >> a[i].y;
}

void Solve() {
    while (m--) {
        Point p;
        cin >> p.x >> p.y;
        int res = pointInPolygon(a, n, p);
        if (res == 0) cout << "OUTSIDE\n";
        else if (res == 1) cout << "INSIDE\n";
        else cout << "BOUNDARY\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (fopen(input_file, "r")) {
        freopen(input_file, "r", stdin);
        freopen(output_file, "w", stdout);
    }
    int t = 1;
    while (t--)
        Input(), Solve();
    return 0;
}