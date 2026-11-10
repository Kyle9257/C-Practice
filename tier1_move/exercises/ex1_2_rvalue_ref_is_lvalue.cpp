#include <iostream>
#include <utility>

void f(int&)  { std::cout << "  匹配 int&  （左值）\n"; }
void f(int&&) { std::cout << "  匹配 int&& （右值）\n"; }

int main() {
    int x = 0;

    std::cout << "f(x):\n";            f(x);            // 左值
    std::cout << "f(5):\n";            f(5);            // 纯右值
    std::cout << "f(std::move(x)):\n"; f(std::move(x)); // xvalue

    std::cout << "--- 关键反直觉点 ---\n";
    int&& r = 5;          // r 是右值引用，但 r 本身有名字
    std::cout << "f(r):\n";            f(r);            // r 是左值 → int&
    std::cout << "f(std::move(r)):\n"; f(std::move(r)); // 转回 xvalue → int&&
}
