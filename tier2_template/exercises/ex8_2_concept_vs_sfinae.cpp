#include <concepts>
#include <iostream>

// 用 concepts 重写 ex7_2 的 SFINAE 版本，约束更直观、报错更清晰
template <std::integral T>
void print_kind(T) {
    std::cout << "整型（concept 约束）\n";
}

template <std::floating_point T>
void print_kind(T) {
    std::cout << "浮点（concept 约束）\n";
}

int main() {
    print_kind(42);       // 整型
    print_kind(3.14);     // 浮点
    // print_kind("x");   // 取消注释：报错信息比 SFINAE 可读得多
}
