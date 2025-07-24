#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0): x(x), y(y) {}
    
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    ld cross(const Point& p) const { return x * p.y - y * p.x; }
    ld dot(const Point& p) const { return x * p.x + y * p.y; }
    ld dist2() const { return x * x + y * y; }
    ld dist() const { return sqrt(dist2()); }
};

// 🔹 Producto cruz entre (b - a) y (c - a)
ld cross(Point a, Point b, Point c) {
    return (b - a).cross(c - a);
}

// 🔹 Área de triángulo ABC
ld triangle_area(Point a, Point b, Point c) {
    return abs(cross(a, b, c)) / 2;
}

// 🔹 Determinar si punto p está dentro de triángulo abc
bool in_triangle(Point a, Point b, Point c, Point p) {
    ld A = triangle_area(a, b, c);
    ld A1 = triangle_area(p, b, c);
    ld A2 = triangle_area(a, p, c);
    ld A3 = triangle_area(a, b, p);
    return abs((A1 + A2 + A3) - A) < 1e-9;
}

// 🔹 Determina si los segmentos AB y CD se intersectan
bool intersect(Point a, Point b, Point c, Point d) {
    ld d1 = cross(c, d, a);
    ld d2 = cross(c, d, b);
    ld d3 = cross(a, b, c);
    ld d4 = cross(a, b, d);
    return (d1 * d2 < 0) && (d3 * d4 < 0);
}

// 🔹 Convex Hull (Graham Scan o Monotone Chain)
vector<Point> convex_hull(vector<Point>& pts) {
    sort(pts.begin(), pts.end(), [](Point a, Point b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });
    vector<Point> lower, upper;
    for (Point p : pts) {
        while (lower.size() >= 2 && cross(lower[lower.size()-2], lower.back(), p) <= 0)
            lower.pop_back();
        lower.push_back(p);
    }
    for (int i = pts.size() - 1; i >= 0; i--) {
        Point p = pts[i];
        while (upper.size() >= 2 && cross(upper[upper.size()-2], upper.back(), p) <= 0)
            upper.pop_back();
        upper.push_back(p);
    }
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}
