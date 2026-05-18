#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int main() {
    std::string fname = "cpinput.txt";
    std::string line;

    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open " << fname << std::endl;
    }

    size_t pos, len;
    std::string left, right, start, repeat;
    long long total = 0, num, min, max;

    while(std::getline(fin, line, ',')) {
        std::cout << line << std::endl;
        pos = line.find('-');

        left = line.substr(0, pos);
        min = std::stol(left);

        right = line.substr(pos + 1);
        max = std::stol(right);

        len = std::max(left.length() / 2, static_cast<size_t>(1));
        start = left.substr(0, len);
        repeat = start;
        num = std::stol(repeat + repeat);

        while (num < min) {
            repeat = std::to_string(std::stol(repeat) + 1);
            num = std::stol(repeat + repeat);
        }
        while (num <= max) {
            total += num;
            repeat = std::to_string(std::stol(repeat) + 1);
            num = std::stol(repeat + repeat);
        }

    }
    std::cout << "Total: " << total << std::endl;
}