#include <iosfwd>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open " << fname << std::endl;
        return -1;
    }

    std::string line;
    std::vector<std::string> ranges;
    std::unordered_set<size_t> fresh;
    do {
        std::getline(fin, line);
        ranges.push_back(line);

    } while (line != "");

    ranges.pop_back();
    std::streampos pos = fin.tellg();
    size_t dash, left, right, curr;
    for (auto s : ranges) {
        dash = s.find("-");
        left = std::stoull(s.substr(0, dash));
        right = std::stoull(s.substr(dash + 1));
        fin.clear();
        fin.seekg(pos);

        while (std::getline(fin, line)) {
            curr = std::stoull(line);
            if (curr >= left && curr <= right) {
                fresh.insert(curr);
            }
        }
    }
    std::cout << "Num Spoiled: " << fresh.size() << std::endl;

}






