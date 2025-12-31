#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

// 66157522141
// 75951623021
// 44854383294
// 31097235287

int main() {
    std::string fname = "input.txt";
    std::string line;

    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open " << fname << std::endl;
        return -1;
    }

    size_t pos, len;
    std::string left, right, curr, sub, repeat;
    long long total = 0, num, min, max;
    bool done = false;
    std::unordered_set<long long> seen;

    while (std::getline(fin, line, ',')) {
        std::cout << line << std::endl;
        pos = line.find('-');

        left = line.substr(0, pos);
        min = std::stol(left);

        right = line.substr(pos + 1);
        max = std::stol(right);

        for (auto i = min; i <= max; i++) {
            curr = std::to_string(i);
            len = curr.length();
            done = false;

            for (size_t j = 1; j <= len / 2 && !done; j++) {
                if (len % j != 0) {
                    continue;
                }
                sub = "";
                repeat = curr.substr(0, j);
                for (size_t k = 0; k < len / j; k++) {
                    sub += repeat;
                }

                if (curr == sub) {
                    if (seen.find(std::stol(curr)) == seen.end()) {
                        total += std::stol(curr);
                        seen.insert(std::stol(curr));
                    }
                    done = true;
                }
            }
        }
    }
    std::cout << "Total: " << total << std::endl;
}