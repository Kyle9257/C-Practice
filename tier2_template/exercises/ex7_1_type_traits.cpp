#include <iostream>
#include <string>
#include <type_traits>

// type traits + if constexpr 做编译期分派
template <typename T>
void describe(T) {
    if constexpr (std::is_integral_v<T>)
        std::cout << "整型\n";
    else if constexpr (std::is_floating_point_v<T>)
        std::cout << "浮点型\n";
    else if constexpr (std::is_pointer_v<T>)
        std::cout << "指针\n";
    else
        std::cout << "其他\n";
}

int main() {
    describe(42);                 // 整型
    describe(3.14);               // 浮点型
    int x = 0;
    describe(&x);                 // 指针
    describe(std::string("s"));   // 其他
}
