#include <iostream>

// C++17 折叠表达式：一元右折叠
template <typename... Args>
auto sum(Args... args) {
    return (args + ...);   // 展开为 ((a1 + a2) + ... + an)
}

// 逗号折叠：依次打印每个参数
template <typename... Args>
void print_all(Args... args) {
    ((std::cout << args << " "), ...);
}

int main() {
    std::cout << "sum(1,2,3,4,5) = " << sum(1, 2, 3, 4, 5) << "\n";
    print_all(1, 2.5, 'x', "str");
    std::cout << "\n";
}
