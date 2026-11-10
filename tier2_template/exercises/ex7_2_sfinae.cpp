#include <iostream>
#include <type_traits>

// SFINAE：用 enable_if 按类型「启用/禁用」重载
// 版本1：只对整型启用
template <typename T>
std::enable_if_t<std::is_integral_v<T>, void>
print_kind(T) {
    std::cout << "整型重载\n";
}

// 版本2：只对浮点启用
template <typename T>
std::enable_if_t<std::is_floating_point_v<T>, void>
print_kind(T) {
    std::cout << "浮点重载\n";
}

int main() {
    print_kind(42);       // 整型重载
    print_kind(3.14);     // 浮点重载
    // print_kind("x");   // 取消注释：两个重载都不匹配，编译错误
}
