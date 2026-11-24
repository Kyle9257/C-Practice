/*
学习目标：
1. 区分 constexpr 的“可以在编译期求值”和 consteval 的“必须在编译期求值”。
2. 掌握 constexpr 函数同时服务编译期与运行期输入的方式。
3. 使用 static_assert 验证编译期结果。

练习方法：
1. 修改 factorial(5) 并同步修改 static_assert 的期望结果。
2. 尝试写 checked_size(input)，阅读 consteval 对运行期实参的编译错误。
3. 给 factorial 增加负数输入处理，并思考编译期错误应如何表达。

知识点：
- constexpr 函数在实参是常量表达式且上下文要求常量时，可在编译期执行。
- 同一个 constexpr 函数也可以接收运行期变量，此时按普通函数执行。
- consteval 声明立即函数，每次潜在求值的调用都必须产生编译期常量。
- static_assert 在编译阶段检查条件，不产生运行期开销。
- 编译期求值适合常量生成和约束检查，但不应为了“炫技”替代清晰的运行时代码。
*/
#include <array>
#include <iostream>

constexpr int factorial(int value) {
    // C++14 起 constexpr 函数可以包含循环和局部变量。
    int result = 1;
    for (int i = 2; i <= value; ++i) {
        result *= i;
    }
    return result;
}

consteval int checked_size(int value) {
    // 立即函数的调用结果可直接用于要求常量表达式的数组长度。
    return value > 0 ? value : 1;
}

int main() {
    constexpr int compile_time = factorial(5);
    static_assert(compile_time == 120);

    int input = 6;
    // input 不是编译期常量，因此 factorial 在运行期执行。
    const int run_time = factorial(input);
    std::array<int, checked_size(4)> values{};

    std::cout << "编译期 factorial(5): " << compile_time << '\n';
    std::cout << "运行期 factorial(6): " << run_time << '\n';
    std::cout << "consteval 生成数组长度: " << values.size() << '\n';
}
