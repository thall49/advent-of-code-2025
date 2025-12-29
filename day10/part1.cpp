#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Machine {
  private:
    std::vector<bool> pattern;
    std::vector<std::vector<uint>> buttons;
    size_t N;

    bool dfs(size_t, uint, uint, std::vector<bool> &);

  public:
    uint fewest_presses();
    Machine(std::vector<bool>, std::vector<std::vector<uint>>, size_t);
    void test();
};

Machine::Machine(std::vector<bool> p, std::vector<std::vector<uint>> b, size_t n) {
    pattern = p;
    buttons = b;
    N = n;
}

std::vector<Machine> read_file(std::ifstream &fin) {
    std::vector<Machine> machs;
    std::string line, block;

    while (std::getline(fin, line)) {
        std::istringstream sin(line);
        std::vector<bool> pattern;
        std::vector<std::vector<uint>> buttons;

        std::getline(sin, block, ' ');
        block = block.substr(1, block.length() - 2);
        pattern.reserve(block.length());

        for (const char &c : block) {
            if (c == '.') {
                pattern.push_back(false);
            } else {
                pattern.push_back(true);
            }
        }

        while (std::getline(sin, block, ' ')) {
            if (block[0] == '{') {
                break;
            }

            block = block.substr(1, block.length() - 2);
            std::vector<uint> b((block.length() + 1) / 2);

            for (size_t i = 0; i < block.length(); i += 2) {
                b[i / 2] = block[i] - '0';
            }

            buttons.push_back(b);
        }

        machs.push_back({pattern, buttons, buttons.size()});
    }

    return machs;
}

void Machine::test() {
    for (const bool b : pattern) {
        std::cout << b << " ";
    }
    std::cout << "\n";

    for (const auto &v : buttons) {
        for (const uint &u : v) {
            std::cout << u << " ";
        }
        std::cout << " ";
    }
    std::cout << "\n\n";
}

void press(std::vector<uint> buttons, std::vector<bool> &lights) {
    for (const uint &b : buttons) {
        lights[b] = !lights[b];
    }
}

bool Machine::dfs(size_t ind, uint used, uint max, std::vector<bool> &lights) {
    if (used > max) {
        return false;
    }

    if (lights == pattern) {
        return true;
    }

    if (ind == N) {
        return false;
    }

    if (dfs(ind + 1, used, max, lights)) {
        return true;
    }

    press(buttons[ind], lights);

    bool ok = dfs(ind + 1, used + 1, max, lights);

    press(buttons[ind], lights);

    return ok;
}

uint Machine::fewest_presses() {
    std::vector<bool> lights(pattern.size(), false);

    for (uint max = 0; max < buttons.size(); max++) {
        if (dfs(0, 0, max, lights)) {
            return max;
        }
    }

    // Max uint, as long as the problems is solvable, should be good
    return -1;
}

int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open " << fname << "\n";
        return -1;
    }

    size_t total = 0;

    std::vector<Machine> machs = read_file(fin);
    for (Machine &m : machs) {
        total += m.fewest_presses();
    }

    std::cout << "Total: " << total << "\n";
}
