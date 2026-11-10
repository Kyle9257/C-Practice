#include <iostream>
#include <string>
#include <string_view>
#include <span>
#include <vector>

// string_view：不拷贝，只借视图（C++17）
void print_prefix(std::string_view sv, std::size_t n) {
    std::cout << sv.substr(0, n) << "\n";
}

// span：对连续内存的视图，数组和 vector 都能传（C++20）
int sum(std::span<const int> s) {
    int total = 0;
    for (int x : s) total += x;
    return total;
}

int main() {
    std::string s = "hello world";
    print_prefix(s, 5);        // 不拷贝原字符串

    std::vector<int> v = {1, 2, 3, 4, 5};
    int arr[] = {6, 7, 8};
    std::cout << "sum(vector) = " << sum(v) << "\n";
    std::cout << "sum(array) = " << sum(arr) << "\n";
}
