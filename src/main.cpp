// Generates a noisy wave, simplifies it, and writes before/after to out.svg.
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "simplify.hpp"

static void write_path(FILE* f, const std::vector<ls::Point>& p, const char* colour) {
    std::fprintf(f, "<polyline fill=\"none\" stroke=\"%s\" stroke-width=\"1.5\" points=\"", colour);
    for (auto& q : p) std::fprintf(f, "%.2f,%.2f ", q.x, q.y);
    std::fprintf(f, "\"/>\n");
}

int main(int argc, char** argv) {
    double eps = argc > 1 ? std::atof(argv[1]) : 3.0;
    std::vector<ls::Point> line;
    for (int i = 0; i <= 400; ++i) {
        double x = i * 2.0;
        double noise = std::sin(i * 12.9898) * 2.0;  // deterministic "noise"
        line.push_back({x, 100 + 60 * std::sin(i * 0.05) + noise});
    }
    auto simple = ls::simplify(line, eps);
    std::printf("epsilon=%.2f  points: %zu -> %zu\n", eps, line.size(), simple.size());

    FILE* f = std::fopen("out.svg", "w");
    if (!f) return 1;
    std::fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"200\">\n");
    write_path(f, line, "#bbb");
    write_path(f, simple, "#d33");
    std::fprintf(f, "</svg>\n");
    std::fclose(f);
}
