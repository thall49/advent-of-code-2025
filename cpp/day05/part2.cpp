#include <iosfwd>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

bool pair_comp(std::pair<size_t, size_t>& a, std::pair<size_t, size_t>& b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}


int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open " << fname << std::endl;
        return -1;
    }

    std::string line;
    size_t dash, left, right;
    std::vector<std::pair<size_t, size_t>> ranges;

    while (std::getline(fin, line)) {
        if (line == "") {
            break;
        }

        dash = line.find("-");
        left = std::stoull(line.substr(0, dash));
        right = std::stoull(line.substr(dash + 1));

        ranges.emplace_back(left, right);
    }

    std::sort(ranges.begin(), ranges.end(), pair_comp);
    std::vector<bool> valid(ranges.size(), true);
    for (auto it = ranges.begin(); it != std::prev(ranges.end()); ++it) {
        auto next = std::next(it);
        if (it->second >= next->first) {
            next->first = it->first;
            next->second = std::max(next->second, it->second);
            valid.at(it - ranges.begin()) = false;
        }
    }

    size_t total = 0;
    for (size_t i = 0; i < ranges.size(); i++) {
        if (!valid[i]) {
            continue;
        }

        total += ranges[i].second - ranges[i].first + 1;
    }

    std::cout << "Total: " << total << std::endl;
}