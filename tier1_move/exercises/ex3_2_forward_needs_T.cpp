#include <iostream>
#include <utility>

void g(int&)  { std::cout << "  g(int&)\n"; }
void g(int&&) { std::cout << "  g(int&&)\n"; }

// 正确：用 std::forward<T> 保留原始值类别
template <typename T>
void relay(T&& t) {
    g(std::forward<T>(t));
}

// 错误示范：用 std::move 会把左值也强制变右值
template <typename T>
void relay_wrong(T&& t) {
    g(std::move(t));
}

int main() {
    int x = 0;

    std::cout << "relay(x)   [左值]:\n";  relay(x);
    std::cout << "relay(5)   [右值]:\n";  relay(5);

    std::cout << "--- 用 move 的错误版本 ---\n";
    std::cout << "relay_wrong(x) [左值被破坏]:\n"; relay_wrong(x);
    std::cout << "relay_wrong(5) [右值]:\n";       relay_wrong(5);
}
