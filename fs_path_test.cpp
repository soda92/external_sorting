#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <random>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector<std::string> random_strings(int len = 50, int records = 1000) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 26);

    auto random_char = [&]() { return 'a' + dist(gen); };

    std::vector<std::string> vec;
    for (auto j = 0; j < records; j++) {
        std::stringstream ss;
        for (auto i = 0; i < len; i++) {
            ss << random_char();
        }
        vec.push_back(ss.str());
    }
    return vec;
}

int main() {
    auto data_path = fs::path{"large_data.bin"};
    std::ofstream out{data_path.string()};
    uintmax_t target_size = 1024 * 1024 * 1024 * 3ull;
    while (fs::file_size(data_path) < target_size) {
        auto vec = random_strings();
        for(auto str: vec) {
            out << str;
        }
        out << '\n' << std::flush;
    }
}