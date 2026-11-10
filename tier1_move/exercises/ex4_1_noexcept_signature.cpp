#include <iostream>

void f1() noexcept { std::cout << "f1 (noexcept)\n"; }
void f2() { std::cout << "f2 (可能抛异常)\n"; }

int main() {
    // C++17 起，noexcept 是函数类型的一部分
    void (*p1)() noexcept = f1;   // OK：类型匹配
    void (*p2)()          = f2;   // OK：类型匹配

    // 下面两条在 C++17 是编译错误，先注释掉，自行取消注释体验：
    // void (*p3)()          = f1;   // 错误：noexcept 函数不能赋给非 noexcept 指针
    // void (*p4)() noexcept = f2;   // 错误：非 noexcept 函数不能赋给 noexcept 指针

    std::cout << std::boolalpha;
    std::cout << "noexcept(f1()) = " << noexcept(f1()) << "\n"; // true
    std::cout << "noexcept(f2()) = " << noexcept(f2()) << "\n"; // false

    p1();
    p2();
}
