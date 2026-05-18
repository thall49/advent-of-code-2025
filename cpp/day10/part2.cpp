#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>
#include <z3++.h>
#include <z3_api.h>

class Machine {
  private:
    std::vector<int> target;
    std::vector<std::vector<int>> buttons;
    std::vector<z3::expr> names;
    std::vector<int> max_presses;
    std::vector<std::vector<int>> eq;
    z3::context ctx;

    void set_equations(z3::optimize &);
    void set_bounds(z3::optimize &);

  public:
    int fewest_presses();
    Machine(std::vector<int>, std::vector<std::vector<int>>);
    void test();
};

Machine::Machine(std::vector<int> t, std::vector<std::vector<int>> b) {
    target = t;
    buttons = b;

    max_presses.reserve(buttons.size());
    names.reserve(buttons.size());
    eq.resize(target.size());

    for (size_t i = 0; i < buttons.size(); ++i) {
        int m = std::numeric_limits<int>::max();
        for (int &u : buttons[i]) {
            eq[u].push_back(i);
            m = std::min(m, target[u]);
        }
        max_presses.push_back(m);
        names.emplace_back(ctx.int_const(("x" + std::to_string(i)).c_str()));
    }
}

std::vector<int> string_to_int_vec(std::string &s) {
    std::vector<int> v;
    std::istringstream sin(s);
    std::string num;

    while (std::getline(sin, num, ',')) {
        v.emplace_back(std::stoi(num));
    }

    return v;
}

std::vector<std::unique_ptr<Machine>> read_file(std::ifstream &fin) {
    std::vector<std::unique_ptr<Machine>> machs;
    std::string line, block;

    while (std::getline(fin, line)) {
        std::istringstream sin(line);
        std::vector<std::vector<int>> buttons;

        std::getline(sin, block, ' ');

        while (std::getline(sin, block, ' ')) {
            if (block[0] == '{') {
                block = block.substr(1, block.length() - 2);
                break;
            }

            block = block.substr(1, block.length() - 2);

            buttons.emplace_back(string_to_int_vec(block));
        }

        machs.push_back(std::make_unique<Machine>(string_to_int_vec(block), buttons));
    }

    return machs;
}

void Machine::test() {
    for (const uint j : target) {
        std::cout << j << " ";
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

void Machine::set_equations(z3::optimize &opt) {
    for (size_t i = 0; i < eq.size(); ++i) {
        z3::expr sum = ctx.int_val(0);

        for (size_t j = 0; j < eq[i].size(); ++j) {
            sum = sum + names[eq[i][j]];
        }

        opt.add(sum == target[i]);
    }
}

void Machine::set_bounds(z3::optimize &opt) {
    for (size_t i = 0; i < names.size(); ++i) {
        opt.add(names[i] >= 0 && names[i] <= max_presses[i]);
    }
}

int Machine::fewest_presses() {
    z3::optimize opt(ctx);
    set_bounds(opt);
    set_equations(opt);

    z3::expr sum = ctx.int_val(0);
    for (const auto &n : names) {
        sum = sum + n;
    }

    opt.minimize(sum);
    int total = 0;
    if (opt.check() == z3::sat) {
        auto mod = opt.get_model();

        Z3_get_numeral_int(mod.ctx(), mod.eval(sum), &total);
    }

    return total;
}

int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open " << fname << "\n";
        return -1;
    }

    int total = 0;

    std::vector<std::unique_ptr<Machine>> machs = read_file(fin);
    for (auto &m : machs) {
        total += m->fewest_presses();
    }

    std::cout << "Total: " << total << "\n";
}
