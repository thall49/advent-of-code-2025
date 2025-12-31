#include <cctype>
#include <iosfwd>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <sstream>
#include <vector>

// 988091112 Low

void last_line(std::ifstream& f, std::vector<std::string>& v) {
    std::string line, op;
    while(std::getline(f, line));

    std::istringstream sin(line);
    while (sin >> op) {
        v.push_back(op);
    }
    f.clear();
    f.seekg(0, std::ios::beg);
}

int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open " << fname << std::endl;
        return -1;
    }

    std::string line, sval;
    std::vector<size_t> vals;
    std::vector<std::string> ops;
    last_line(fin, ops);

    std::getline(fin, line);
    std::istringstream sin(line);

    while (sin >> sval) {
        vals.emplace_back(std::stoull(sval));
    }

    size_t c = 0;
    while (std::getline(fin, line)) {
        if (!std::isalnum(line[0]) && !isspace(line[0])) {
            break;
        }
        c = 0;
        std::istringstream ss(line);
        while (ss >> sval) {
            if (ops[c] == "+") {
                vals[c] += std::stoull(sval);
            }
            else {
                vals[c] *= std::stoull(sval);
            }
            c++;
        }
        std::cout << vals[0] << std::endl;
    }

    size_t total = std::accumulate(vals.begin(), vals.end(), 0UL);
    std::cout << "Total: " << total << std::endl;
}