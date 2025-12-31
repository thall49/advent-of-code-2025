#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>

typedef std::array<long, 2> point;

struct Edge {
    long lower;
    long upper;
    long axis;
};

bool comp(const Edge& a, const Edge& b) {
    if (a.axis != b.axis) {
        return a.axis < b.axis;
    }
    if (a.lower != b.lower) {
        return a.lower < b.lower;
    }

    return a.upper < b.upper;
}

class Shape {
    private:
        std::vector<point> points;
        std::vector<Edge> v_edges;
        std::vector<Edge> h_edges;
        bool cast_left(const point&, const point&);
        bool cast_up(const point&, const point&);
        bool in_shape(const point, const point);
        bool in_edge(long, const Edge&);
        bool cast_in(point&, point&);

    public:
        Shape(std::ifstream&);
        long area(size_t, size_t);
        size_t N;
};

Shape::Shape(std::ifstream& fin) {
    std::string line;
    long x, y, px, py;
    char c;

    std::getline(fin, line);
    std::istringstream s(line);
    s >> x >> c >> y;
    points.push_back({x, y});
    px = x;
    py = y;

    while (std::getline(fin, line)) {
        std::istringstream sin(line);
        sin >> x >> c >> y;
        points.push_back({x, y});

        if (px == x) {
            v_edges.push_back({std::min(y, py), std::max(y, py), x});
        }
        else {
            h_edges.push_back({std::min(x, px), std::max(x, px), y});
        }

        px = x;
        py = y;
    }

    if (px == points[0][0]) {
        v_edges.push_back({std::min(points[0][1], py), std::max(points[0][1], py), px});
    }
    else {
        h_edges.push_back({std::min(points[0][0], px), std::max(points[0][0], px), py});
    }

    std::sort(v_edges.begin(), v_edges.end(), comp);
    std::sort(h_edges.begin(), h_edges.end(), comp);
    N = points.size();
}

bool Shape::in_edge(long c, const Edge& e) {
    return c >= e.lower && c <= e.upper;
}

bool Shape::cast_left(const point& a, const point& b) {
    std::array<point, 4> test;
    std::array<size_t, 4> counts = {0, 0, 0, 0};

    test[0] = a;
    test[1] = {b[0], a[1]};
    test[2] = {a[0], b[1]};
    test[3] = b;

    for (size_t i = 0; i < 4; ++i) {
        for (const Edge& v : v_edges) {
            if (v.axis > test[i][0]) {
                break;
            }

            if (in_edge(test[i][1], v)) {
                counts[i]++;
            }
        }
    }

    if (counts[0] != counts[1] || counts[2] != counts[3]) {
        return false;
    }

    if (counts[0] % 2 != 1 || counts[2] % 2 != 1) {
        return false;
    }

    return true;
}

bool Shape::cast_up(const point& a, const point& b) {
    std::array<point, 4> test;
    std::array<size_t, 4> counts = {0, 0, 0, 0};

    test[0] = a;
    test[1] = {a[0], b[1]};
    test[2] = {b[0], a[1]};
    test[3] = b;

    for (size_t i = 0; i < 4; ++i) {
        for (const Edge& h : h_edges) {
            if (h.axis > test[i][1]) {
                break;
            }

            if (in_edge(test[i][0], h)) {
                counts[i]++;
            }
        }
    }

    if (counts[0] != counts[1] || counts[2] != counts[3]) {
        return false;
    }

    if (counts[0] % 2 != 1 || counts[2] % 2 != 1) {
        return false;
    }

    return true;
}

bool Shape::cast_in(point &a, point &b) {
    if (a[0] == b[0] || a[1] == b[1]) {
        return false;
    }

    if (a[0] < b[0]) {
        a[0]++;
        b[0]--;
    }
    else {
        a[0]--;
        b[0] ++;
    }

    if (a[1] < b[1]) {
        a[1]++;
        b[1]--;
    }
    else {
        a[1]--;
        b[1]++;
    }

    return true;
}

bool Shape::in_shape(const point a, const point b) {
    return cast_left(a, b) && cast_up(a, b);
}

long Shape::area(size_t i, size_t j) {
    point a = points[i];
    point b = points[j];

    if (!cast_in(a, b)) {
        return -1;
    }

    if (!in_shape(a, b)) {
        return -1;
    }

    return (std::abs(points[i][0] - points[j][0]) + 1) * (std::abs(points[i][1] - points[j][1]) + 1);
}

int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open " << fname << "\n";
        return -1;
    }

    Shape s(fin);

    long max = -1, a;

    size_t ind = 0;
    for (size_t i = 0; i < s.N; ++i) {
        for (size_t j = i + 1; j < s.N; ++j) {
            a = s.area(i, j);
            if (a > max) {
                max = a;
            }
        }
    }

    std::cout << "Max area: " << max << "\n";
}