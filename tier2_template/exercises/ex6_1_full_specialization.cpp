#include <iostream>

// 通用主模板
template <typename T>
struct TypeName {
    static const char* get() { return "unknown"; }
};

// 全特化：T = int
template <>
struct TypeName<int> {
    static const char* get() { return "int"; }
};

// 全特化：T = double
template <>
struct TypeName<double> {
    static const char* get() { return "double"; }
};

int main() {
    std::cout << TypeName<float>::get() << "\n";   // unknown（走主模板）
    std::cout << TypeName<int>::get() << "\n";     // int
    std::cout << TypeName<double>::get() << "\n";  // double
}
