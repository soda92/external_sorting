#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>


template <typename T>
void merge(std::vector<T> &array, int low, int middle, int high) {
    std::deque<T> buffer1, buffer2;

    for (auto i = low; i <= middle; i++)
        buffer1.push_back(array.at(i));
    for (auto i = middle + 1; i <= high; i++)
        buffer2.push_back(array.at(i));

    auto index = low;

    while ((buffer1.size() != 0) && (buffer2.size() != 0)) {
        if (buffer1.front() <= buffer2.front()) {
            array.at(index) = buffer1.front();
            index += 1;
            buffer1.pop_front();
        } else {
            array.at(index) = buffer2.front();
            index += 1;
            buffer2.pop_front();
        }
    }

    auto buffer_left = (buffer1.size() != 0) ? buffer1 : buffer2;
    while (buffer_left.size() != 0) {
        array.at(index) = buffer_left.front();
        index += 1;
        buffer_left.pop_front();
    }
}

template <typename T> void mergesort(std::vector<T> &array, int low, int high) {
    if (low < high) {
        auto middle = (low + high) / 2;
        mergesort(array, low, middle);
        mergesort(array, middle + 1, high);
        merge(array, low, middle, high);
    }
}

std::vector<int> read_data() {
    auto in = std::ifstream("data.txt", std::ios_base::in);
    auto line = std::string();
    auto data = std::vector<int>();
    while (std::getline(in, line)) {
        auto sstream = std::stringstream(line);
        auto number = int{0};
        while (sstream >> number) {
            data.push_back(number);
        }
    }
    return data;
}

int main() {
    auto data = read_data();
    mergesort(data, 0, data.size() - 1);

    if (std::is_sorted(std::begin(data), std::end(data))) {
        std::cout << "sorted\n";
    }
}