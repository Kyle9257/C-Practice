#include <iostream>
#include <optional>
#include <variant>
#include <string>

// optional：表示「可能有值，可能没有」
std::optional<int> find_divisor(int n) {
    for (int i = 2; i < n; ++i)
        if (n % i == 0) return i;
    return std::nullopt;   // 无值
}

int main() {
    if (auto d = find_divisor(15)) {
        std::cout << "15 的一个因数: " << *d << "\n";
    }
    if (!find_divisor(7)) {
        std::cout << "7 是质数（无因数）\n";
    }

    // variant：同一变量可在多种类型间切换
    std::variant<int, double, std::string> v;
    v = 42;
    std::cout << "v 是 int: " << std::get<int>(v) << "\n";
    v = 3.14;
    std::cout << "v 是 double: " << std::get<double>(v) << "\n";
    v = "hello";
    std::cout << "v 是 string: " << std::get<std::string>(v) << "\n";
}
