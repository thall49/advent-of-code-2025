#include <algorithm>
#include <cctype>
#include <functional>
#include <iosfwd>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <sstream>
#include <vector>

size_t last_line(std::ifstream& f, std::vector<std::string>& v) {
    std::string line, op;
    size_t lnum = 0;
    while(std::getline(f, line)) {
        lnum++;
    }

    std::istringstream sin(line);
    while (sin >> op) {
        v.push_back(op);
    }
    f.clear();
    f.seekg(0, std::ios::beg);

    return lnum - 1;
}

size_t get_maxsize(std::vector<std::vector<char>>& v) {
    return std::max_element(v.begin(), v.end(),
        [](auto const& a, auto const &b) {
            return a.size() < b.size();
        })->size();
}

int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open " << fname << std::endl;
        return -1;
    }

    std::string line, sval;
    std::vector<std::string> ops;
    std::vector<size_t> vals;
    std::vector<std::vector<char>> mat;
    size_t lnum = last_line(fin, ops);
    mat.resize(lnum);
    vals.resize(ops.size());

    size_t c = 0;
    while (std::getline(fin, line)) {
        if (!std::isalnum(line[0]) && !isspace(line[0])) {
            break;
        }
        mat[c].assign(line.begin(), line.end());

        c++;
    }

    lnum = get_maxsize(mat);
    for (auto &v : mat) {
        for (size_t i = v.size(); i < lnum; i++) {
            v.push_back(' ');
        }
    }

    c = 0;
    std::string num;
    bool next = true;
    std::vector<size_t> curr;

    for (size_t i = 0; i < lnum; i++) {
        num = "";
        next = true;

        for (auto v : mat) {
            if (v[i] != ' ') {
                num.push_back(v[i]);
                next = false;
            }
        }
        if (!next) {
            curr.push_back(std::stoull(num));
        }
        if (next || i == lnum - 1){
            for (auto s : curr) {
                std::cout << s << " ";
            }
            if (ops[c] == "+") {
                vals[c] = std::accumulate(curr.begin(), curr.end(), 0ULL);
            }
            else {
                vals[c] = std::accumulate(curr.begin(), curr.end(), 1ULL, std::multiplies<>());
            }
            curr.clear();
            c++;
        }
    }

    size_t total = std::accumulate(vals.begin(), vals.end(), 0UL);
    std::cout << "Total: " << total << std::endl;
}