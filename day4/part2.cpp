#include <iostream>
#include <fstream>
#include <string>
#include <array>

// 1419

#define N 138

constexpr std::array<std::pair<int, int>, 8> check  = {{
    {-1, -1},
    {-1,  0},
    {-1,  1},
    { 0, -1},
    { 0,  1},
    { 1, -1},
    { 1,  0},
    { 1,  1}
}};

size_t check_pos(std::array<std::array<char, N>, N> &g, int r, int c) {
    size_t total = 0;
    if (g[r][c] != '@') {
        return 0;
    }

    int ro, co;
    for (auto o: check) {
        ro = r + o.first;
        co = c + o.second;

        if ((ro > -1 && ro < N) && (co > -1 && co < N)) {
            if (g[ro][co] == '@') {
                total++;
            }
        }
    }

    return total < 4;
}

int main () {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open " << fname <<std::endl;
        return -1;
    }

    std::array<std::array<char, N>, N> g;
    std::string line;
    int count = 0;
    while (std::getline(fin, line)) {
        for (size_t i = 0; i < line.length(); i++) {
            g[count][i] = line[i];
        }
        count++;
    }
    size_t total = 0, run;

    do {
        run = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                run += check_pos(g, i, j);
                if (check_pos(g, i, j)) {
                    g[i][j] = '.';
                }
            }
        }
        total += run;
    } while (run > 0);
    std::cout << "Total: " << total << std::endl;
}
