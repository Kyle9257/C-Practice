#include <iostream>
#include <string>

// 通用主模板，这里需要声明
template <typename T>
struct TypeName {
    static const char* get() { return "unknown"; }
};

//全特化：T = std::string
template <>
struct TypeName <std::string>{
    static const char* get() { return "std::string"; }  
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
    std::cout << TypeName<std::string>::get() << "\n";
}
