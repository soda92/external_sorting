#include <algorithm>
#include <fstream>
#include <random>
#include <vector>
#include <iostream>

std::vector<int> generate_random(int n = 50, int range_max = 1e9) {
    if (n > range_max)
        n = range_max;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, range_max);

    auto results = std::vector<int>();
    auto exists = [&](int val) {
        return std::find(results.begin(), results.end(), val) != results.end();
    };
    for (auto i = 0; i < n; i++) {
        auto val = dist(gen);
        while (exists(val))
            val = dist(gen);
        results.push_back(val);
    }
    return results;
}

void write_file(std::vector<int> data) {
    auto out = std::ofstream("data.txt");
    for (auto number : data) {
        out << number << " ";
    }
}

int main() {
    auto n = int{0};
    auto range_max = int{0};
    std::cout << "input n and range max:\n";
    std::cin >> n >> range_max;
    auto data = generate_random(n, range_max);
    write_file(data);
}