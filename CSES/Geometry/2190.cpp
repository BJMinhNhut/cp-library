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
typedef long double ld;
const ld EPS = 1E-9;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
    Point operator+(const Point& other) const { return Point(other.x + x, other.y + y); }
    Point operator-(const Point& other) const { return Point(other.x - x, other.y - y); }
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
    bool operator<(const Point& other) const {
        return x < other.x - EPS || (std::abs(x - other.x) < EPS && y < other.y - EPS);
    }
    // for vectors
    ll norm() const { return x * x + y * y; }    // x^2 + y^2
    ld abs() const { return sqrt(norm()); }
};

// vector functions
ll dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}
ll cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}
ld proj(Point a, Point b) {    // projection of a onto b
    return dot(a, b) / b.abs();
}
ld angle(Point a, Point b) {
    return acos(dot(a, b) / a.abs() / b.abs());
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

ld det(ld a, ld b, ld c, ld d) {
    return a * d - b * c;
}
inline bool between(ld l, ld r, ld x) {
    return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}
/*
- Intersection of segments a-b and c-d
- left, right: return intersection endpoints
- If intersect at a single point, left == right
*/
bool segmentIntersection(Point a, Point b, Point c, Point d, Point& left, Point& right) {
    if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y)) return false;
    Line m(a, b);
    Line n(c, d);
    double zn = det(m.a, m.b, n.a, n.b);
    if (abs(zn) < EPS) {
        if (abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS) return false;
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        left = max(a, c);
        right = min(b, d);
        return true;
    } else {
        left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn;
        left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;
        return between(a.x, b.x, left.x) && between(a.y, b.y, left.y) &&
               between(c.x, d.x, left.x) && between(c.y, d.y, left.y);
    }
}

Point a, b, c, d;

void Input() {
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
}

void Solve() {
    cout << (segmentIntersect(a, b, c, d) ? "YES\n" : "NO\n");
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