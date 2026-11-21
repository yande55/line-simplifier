#include <cassert>
#include <cstdio>
#include "../src/simplify.hpp"
using namespace ls;

int main() {
    // A straight line collapses to its two endpoints.
    std::vector<Point> straight{{0,0},{1,1},{2,2},{3,3},{4,4}};
    auto s = simplify(straight, 0.01);
    assert(s.size() == 2 && s.front().x == 0 && s.back().x == 4);

    // A sharp corner is kept.
    std::vector<Point> corner{{0,0},{5,0},{5,5}};
    assert(simplify(corner, 0.5).size() == 3);

    // Fewer than 3 points are returned unchanged.
    assert(simplify({{0,0},{1,1}}, 1.0).size() == 2);
    assert(simplify({}, 1.0).empty());

    // No removed point is further than epsilon from the result.
    std::vector<Point> wave;
    for (int i = 0; i < 200; ++i) wave.push_back({double(i), 50 * std::sin(i * 0.1)});
    double eps = 2.0;
    auto r = simplify(wave, eps);
    for (auto& p : wave) {
        double best = 1e18;
        for (size_t i = 0; i + 1 < r.size(); ++i) best = std::fmin(best, segment_distance(p, r[i], r[i+1]));
        assert(best <= eps + 1e-9);
    }
    // Zero-length segment does not divide by zero.
    assert(segment_distance({3,4},{0,0},{0,0}) == 5.0);

    std::puts("all tests passed");
}
