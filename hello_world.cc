#include <absl/strings/str_split.h>
#include <absl/strings/string_view.h>
#include <fmt/core.h>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<absl::string_view> container = absl::StrSplit("Hello World", ' ');
    for (auto str : container) {
        fmt::print("{} ", str);
    }
    fmt::print("\n");
}
