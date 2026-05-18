#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
// Max 1689
// 1432 Too Low 1581
// line 14

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

    std::queue<size_t> pos;
    pos.push(std::find(mfold[0].begin(), mfold[0].end(), 'S') - mfold[0].begin());

    size_t total = 0, cmax = mfold[0].size() - 1, len, p;
    std::vector<bool> in(cmax + 1, false);
    in[pos.front()] = true;

    for (size_t i = 1; i < mfold.size(); ++i) {
        len = pos.size();
        while (len--) {
            p = pos.front();
            pos.pop();
            in[p] = false;

            if (mfold[i][p] == '.') {
                mfold[i][p] = '|';
                pos.push(p);
                in[p] = true;
            }
            else if (mfold[i][p] == '^') {
                ++total;
                if (p != cmax) {
                    mfold[i][p + 1] = '|';
                    if (!in[p + 1]) {
                        pos.push(p + 1);
                        in[p + 1] = true;
                    }
                }
                if (p != 0) {
                    mfold[i][p - 1] = '|';
                    if (!in[p - 1]) {
                        pos.push(p - 1);
                        in[p - 1] = true;
                    }
                }
            }
            else {
                pos.push(p);
                in[p] = true;
            }
        }
    }
    std::cout << "Total: " << total << "\n";
}
