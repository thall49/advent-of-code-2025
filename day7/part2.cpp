#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

size_t timelines_from(size_t r, size_t c, std::vector<std::string>& mfold, std::vector<std::vector<size_t>>& memo) {
    if (memo[r][c] != std::numeric_limits<size_t>::max()) {
        return memo[r][c];
    }

    size_t count;
    if (mfold[r][c] == '^') {
        if (r == mfold.size() - 1) {
            count = 1;
        }

        if (c != 0 && c != mfold[r].size() - 1) {
            return timelines_from(r, c - 1, mfold, memo) + timelines_from(r, c + 1, mfold, memo);
        }
        else if (c != 0) {
            count = timelines_from(r, c - 1, mfold, memo);
        }
        else {
            count = timelines_from(r, c + 1, mfold, memo);
        }

    }
    else if (r == mfold.size() - 1) {
        count = 1;
    }
    else {
        count = timelines_from(r + 1, c, mfold, memo);
    }

    memo[r][c] = count;
    return count;
}


int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open " << fname << "\n";
        return -1;
    }

    std::vector<std::string> mfold;
    std::string line;
    while(std::getline(fin, line)) {
        mfold.push_back(line);
    }

    size_t spos = std::find(mfold[0].begin(), mfold[0].end(), 'S') - mfold[0].begin();
    std::vector<std::vector<size_t>> memo;
    memo.reserve(mfold.size());
    for (size_t i = 0; i < mfold.size(); i++) {
        memo.emplace_back(mfold[0].size(), std::numeric_limits<size_t>::max());
    }
    size_t total = timelines_from(0, spos, mfold, memo);

    std::cout << "Total: " << total << "\n";
}
