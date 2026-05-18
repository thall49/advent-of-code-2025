#include <array>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
    std::string name;
    size_t index;
};

class Device {
  private:
    size_t svr, out, dac, fft;
    std::unordered_map<std::string, size_t> labels;
    std::unordered_map<size_t, std::list<size_t>> adj_list;
    size_t dfs(size_t, size_t, std::vector<std::array<size_t, 4>> &);

  public:
    Device(std::ifstream &);
    void add_edge(const std::string, const std::string);
    size_t get_paths();
};

Device::Device(std::ifstream &fin) {
    size_t ind = 0;
    std::string line, label, adj;

    while (std::getline(fin, line)) {
        std::istringstream sin(line);
        std::getline(sin, label, ':');

        if (labels.find(label) == labels.end()) {
            labels.insert({label, ind});
            ++ind;
        }

        while (sin >> adj) {
            if (labels.find(adj) == labels.end()) {
                labels.insert({adj, ind});
                ++ind;
            }

            add_edge(label, adj);
        }
    }

    svr = labels["svr"];
    out = labels["out"];
    dac = labels["dac"];
    fft = labels["fft"];
}

void Device::add_edge(const std::string start, const std::string end) {
    size_t i = labels[start], j = labels[end];

    adj_list[i].push_back(j);
}

size_t Device::dfs(size_t u, size_t mask, std::vector<std::array<size_t, 4>> &memo) {
    if (u == out) {
        return static_cast<size_t>(mask == 0b11);
    }

    if (memo[u][mask] != SIZE_MAX) {
        return memo[u][mask];
    }

    size_t paths = 0;
    for (size_t v : adj_list[u]) {
        int new_mask = mask;
        if (v == dac) {
            new_mask |= 0b01;
        } else if (v == fft) {
            new_mask |= 0b10;
        }
        paths += dfs(v, new_mask, memo);
    }

    memo[u][mask] = paths;
    return paths;
}

size_t Device::get_paths() {
    std::vector<std::array<size_t, 4>> memo(labels.size(),
                                            {SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX});
    size_t start_mask = 0;

    return dfs(svr, start_mask, memo);
}

int main() {
    std::string fname = "input.txt";
    std::ifstream fin(fname);
    if (!fin.is_open()) {
        std::cerr << "Unable to open " << fname << "\n";
        return -1;
    }

    Device dev(fin);
    size_t total = dev.get_paths();

    std::cout << "Total: " << total << "\n";
}
