#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

// 17403

int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if(!fin.is_open()) {
        std::cerr << "Unable to open " << fname << std::endl;
        return -1;
    }

    std::string line, jolt;
    jolt.resize(2);
    int total = 0;
    std::string::iterator first, second;
    while (getline(fin, line)) {
        first = std::max_element(line.begin(), std::prev(line.end()));
        second = std::max_element(std::next(first), line.end());

        total += (10 * (*first - '0') + (*second - '0'));
    }

    std::cout << "Joltage: " << total << std::endl;
}
