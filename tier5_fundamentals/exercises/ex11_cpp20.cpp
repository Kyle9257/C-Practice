/*
学习目标：
1. 通过一个小程序认识常用 C++20 特性。
2. 掌握 ranges 视图的惰性过滤与变换。
3. 认识默认三路比较、数学常量和 constexpr lambda。

练习方法：
1. 修改 filter 条件和 transform 操作，观察 ranges 管道结果。
2. 比较不同 Version 对象，验证默认生成的字典序比较。
3. 用 static_assert 增加一个 square 的编译期测试。

知识点：
- views::filter 和 views::transform 创建惰性视图，遍历时才执行计算。
- 管道中的 lambda 和 view 不拥有 values，values 必须保持有效。
- operator<=> = default 会按成员声明顺序生成比较逻辑。
- std::numbers::pi 提供类型安全的标准数学常量。
- constexpr lambda 可同时用于编译期和运行期计算。
*/
#include <algorithm>
#include <compare>
#include <iostream>
#include <numbers>
#include <ranges>
#include <vector>

struct Version {
    int major;
    int minor;
    // 默认三路比较同时支持 <、<=、>、>= 和相等性比较。
    auto operator<=>(const Version&) const = default;
};

int main() {
    constexpr auto square = [](int value) { return value * value; };
    static_assert(square(5) == 25);

    std::vector<int> values{1, 2, 3, 4, 5, 6};
    std::cout << "偶数平方:";
    // filter 与 transform 都是惰性执行，不创建中间 vector。
    for (const int value : values | std::views::filter([](int x) { return x % 2 == 0; }) |
                               std::views::transform(square)) {
        std::cout << ' ' << value;
    }
    std::cout << "\nVersion{1, 2} < Version{2, 0}: " << std::boolalpha
              << (Version{1, 2} < Version{2, 0}) << '\n';
    std::cout << "pi = " << std::numbers::pi << '\n';
}
