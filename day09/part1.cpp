#include <cstdlib>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>

ssize_t area(std::array<ssize_t, 2> a, std::array<ssize_t, 2> b) {
    return (std::abs(a[0] - b[0]) + 1) * (std::abs(a[1] - b[1]) + 1);
}

int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if(!fin.is_open()) {
        std::cerr << "Unable to open " << fname << "\n";
        return -1;
    }

    std::vector<std::array<ssize_t, 2>> coords;
    std::string line, val1, val2;
    while (std::getline(fin, line)) {
        std::istringstream sin(line);

        std::getline(sin, val1, ',');
        std::getline(sin, val2, ',');

        coords.push_back({std::stoll(val1), std::stoll(val2)});
    }

    std::vector<ssize_t> areas(coords.size() * (coords.size() - 1) / 2);

    size_t ind = 0;
    for (size_t i = 0; i < coords.size(); ++i) {
        for (size_t j = i + 1; j < coords.size(); ++j) {
            areas[ind++] = (area(coords[i], coords[j]));
        }
    }
    std::partial_sort(areas.begin(), areas.begin() + 1, areas.end(), std::greater<>());

    std::cout << "Max area: " << areas[0] << "\n";
}