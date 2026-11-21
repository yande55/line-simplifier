// Ramer-Douglas-Peucker line simplification. Header-only, C++17.
#pragma once
#include <cmath>
#include <vector>

namespace ls {

struct Point { double x, y; };

// Distance from p to the segment a-b.
inline double segment_distance(Point p, Point a, Point b) {
    double dx = b.x - a.x, dy = b.y - a.y;
    double len2 = dx * dx + dy * dy;
    if (len2 == 0.0) return std::hypot(p.x - a.x, p.y - a.y);
    double t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / len2;
    t = t < 0 ? 0 : (t > 1 ? 1 : t);
    return std::hypot(p.x - (a.x + t * dx), p.y - (a.y + t * dy));
}

// Keep the fewest points so no removed point is further than `epsilon`
// from the simplified line. Endpoints are always kept.
inline std::vector<Point> simplify(const std::vector<Point>& pts, double epsilon) {
    const size_t n = pts.size();
    if (n < 3) return pts;
    std::vector<bool> keep(n, false);
    keep[0] = keep[n - 1] = true;
    // Explicit stack instead of recursion, so long lines cannot overflow the call stack.
    std::vector<std::pair<size_t, size_t>> stack{{0, n - 1}};
    while (!stack.empty()) {
        auto [lo, hi] = stack.back();
        stack.pop_back();
        double worst = 0.0;
        size_t idx = lo;
        for (size_t i = lo + 1; i < hi; ++i) {
            double d = segment_distance(pts[i], pts[lo], pts[hi]);
            if (d > worst) { worst = d; idx = i; }
        }
        if (worst > epsilon) {
            keep[idx] = true;
            stack.push_back({lo, idx});
            stack.push_back({idx, hi});
        }
    }
    std::vector<Point> out;
    for (size_t i = 0; i < n; ++i) if (keep[i]) out.push_back(pts[i]);
    return out;
}

} // namespace ls
