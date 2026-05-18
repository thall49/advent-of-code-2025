#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <numeric>

ssize_t dist(std::array<ssize_t, 3> a, std::array<ssize_t, 3> b) {
    return
        (std::get<0>(a) - std::get<0>(b)) * (std::get<0>(a) - std::get<0>(b)) +
        (std::get<1>(a) - std::get<1>(b)) * (std::get<1>(a) - std::get<1>(b)) +
        (std::get<2>(a) - std::get<2>(b)) * (std::get<2>(a) - std::get<2>(b));
}

void merge(size_t i, size_t j, std::vector<size_t>& circ, std::vector<size_t>& count) {
    size_t a, b;
    if (count[j] > count[i]) {
        a = circ[j];
        b = circ[i];
    }
    else {
        a = circ[i];
        b = circ[j];
    }

    if (a == b) {
        return;
    }

    std::replace(circ.begin(), circ.end(), b, a);
    count[a] += count[b];
    count[b] = 0;
}

int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open" << fname << "\n";
        return -1;
    }

    std::vector<std::array<ssize_t, 3>> junctions;

    std::string line, val;
    ssize_t one, two, three;
    while (std::getline(fin, line)) {
        std::istringstream sin(line);

        std::getline(sin, val, ',');
        one = std::stoll(val);
        std::getline(sin, val, ',');
        two = std::stoll(val);
        std::getline(sin, val, ',');
        three = std::stoll(val);

        junctions.push_back({one, two, three});
    }

    std::vector<size_t> circuits(junctions.size());
    std::iota(circuits.begin(), circuits.end(), size_t{0});
    std::vector<size_t> counts(junctions.size(), size_t{1});

    size_t num_rounds = 1000, num_chosen = 3;

    ssize_t min_d, d, max_d = 0;
    size_t min1, min2;
    while (num_rounds--) {
        min_d = SSIZE_MAX;
        for (size_t i = 0; i < junctions.size() - 1; i++) {
            for (size_t j = i + 1; j < junctions.size(); j++) {
                d = dist(junctions[i], junctions[j]);
                if (d < min_d && d > max_d) {
                    min1 = i;
                    min2 = j;
                    min_d = d;
                }
            }
        }

        max_d = min_d;
        merge(min1, min2, circuits, counts);
    }

    std::partial_sort(counts.begin(), counts.begin() + num_chosen, counts.end(), std::greater<>());

    size_t total = 1;
    for (size_t i = 0; i < num_chosen; i++) {
        total *= counts[i];
    }

    std::cout << "\nTotal: " << total << "\n";
}