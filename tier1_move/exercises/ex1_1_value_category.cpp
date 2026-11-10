#include <iostream>
#include <type_traits>
#include <utility>

// 判断值类别的工具：decltype + type_traits
// 规则：decltype(expr)
//   - expr 是「未加括号的变量名」→ 返回其声明类型（特例）
//   - expr 是 xvalue            → T&&
//   - expr 是 lvalue            → T&
//   - expr 是 prvalue           → T
int main() {
    int x = 0;
    int y = 1;
    

    //编译期断言static_assert：编译期间，用于编译期间判断条件是否成立，如果不成立，会输出后面的信息

    // (x) 加括号后按「表达式」处理，x 是左值 → int&
    static_assert(std::is_lvalue_reference_v<decltype((x))>, "(x) 应是左值");
    static_assert(std::is_lvalue_reference_v<decltype((y))>, "(y) 应是左值");

    // 未加括号的 x 走特例，返回声明类型 int（非引用）
    static_assert(!std::is_reference_v<decltype(x)>, "x 不加括号返回声明类型 int");

    // 42 是纯右值 → int（非引用）
    static_assert(!std::is_reference_v<decltype(42)>, "42 是纯右值");

    // std::move(x) 是 xvalue → int&&
    static_assert(std::is_rvalue_reference_v<decltype(std::move(x))>, "std::move(x) 是 xvalue");

    std::cout << "1.1 全部断言通过\n";
    std::cout << "小结：加括号 (x) 才能拿到「表达式的值类别」；不加括号是 decltype 特例。\n";
}
