#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

struct Node {
    std::string name;
    size_t index;
};

class Device {
  private:
    size_t you, out;
    std::unordered_map<std::string, size_t> labels;
    std::unordered_map<size_t, std::list<size_t>> adj_list;
    size_t dfs(size_t, std::vector<size_t> &);

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

    you = labels["you"];
    out = labels["out"];
}

void Device::add_edge(const std::string start, const std::string end) {
    size_t i = labels[start], j = labels[end];

    adj_list[i].push_back(j);
}

size_t Device::dfs(size_t u, std::vector<size_t> &memo) {
    if (u == out) {
        return 1;
    }

    if (memo[u] != std::numeric_limits<size_t>::max()) {
        return memo[u];
    }

    size_t paths = 0;
    for (size_t v : adj_list[u]) {
        paths += dfs(v, memo);
    }

    memo[u] = paths;
    return paths;
}

size_t Device::get_paths() {
    std::vector<size_t> memo(labels.size(), std::numeric_limits<size_t>::max());

    return dfs(you, memo);
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
