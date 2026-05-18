#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

// 17341688984758 -- Too Low

int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if(!fin.is_open()) {
        std::cerr << "Unable to open " << fname << std::endl;
        return -1;
    }

    std::string line, jolt;
    jolt.resize(12);
    size_t total = 0;
    std::string::iterator curr, first, last;
    while (getline(fin, line)) {
        last = std::prev(line.end(), 11);
        curr = std::max_element(line.begin(), last);
        jolt[0] = *curr;

        for (int i = 1; i < 12; i++) {
            curr = std::max_element(std::next(curr), ++last);
            jolt[i] = *curr;
        }

        total += std::stoull(jolt);
    }

    std::cout << "Joltage: " << total << std::endl;
}
