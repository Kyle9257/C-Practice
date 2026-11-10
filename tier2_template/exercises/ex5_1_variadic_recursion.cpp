#include <iostream>

// 递归基：无参数时返回 0
int sum() { return 0; }

// 递归：取第一个 + 递归剩余
template <typename T, typename... Rest>
int sum(T first, Rest... rest) {
    return first + sum(rest...);
}

// 用 sizeof... 统计参数个数
template <typename... Args>
void show_count(Args... args) {
    std::cout << "参数个数: " << sizeof...(args) << "\n";
}

int main() {
    std::cout << "sum(1,2,3,4,5) = " << sum(1, 2, 3, 4, 5) << "\n";
    show_count(1, 2.0, 'a', "hello");
}
