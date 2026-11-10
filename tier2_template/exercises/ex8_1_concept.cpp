#include <concepts>
#include <cstddef>
#include <iostream>
#include <string>

// 定义一个 concept：要求类型有 .size() 成员，且返回值可转 size_t
template <typename T>
concept HasSize = requires(T t) {
    t.size();
    { t.size() } -> std::convertible_to<std::size_t>;
};

// 用 concept 约束模板（替代 SFINAE 的 enable_if）
template <HasSize T>
void show_size(const T& v) {
    std::cout << "size = " << v.size() << "\n";
}

int main() {
    show_size(std::string("hello"));  // string 有 size()
    // show_size(42);                 // 取消注释：int 不满足 HasSize，编译错误
}
