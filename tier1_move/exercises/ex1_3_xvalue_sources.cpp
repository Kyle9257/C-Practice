#include <iostream>
#include <type_traits>
#include <utility>

int&& foo() { static int x = 0; return std::move(x); }

struct S { int m; };

int main() {
    int a = 0;

    // xvalue 的三个来源：
    // 1. std::move(x)
    static_assert(std::is_rvalue_reference_v<decltype(std::move(a))>);

    // 2. 返回 T&& 的函数调用
    static_assert(std::is_rvalue_reference_v<decltype(foo())>);

    // 3. 访问右值对象的成员：S{}.m 是 xvalue
    //    注意：decltype 对「未加括号的成员访问」也有特例，返回成员的声明类型 int；
    //    所以要加括号 (S{}.m) 才能拿到值类别 int&&
    static_assert(std::is_rvalue_reference_v<decltype((S{}.m))>);

    std::cout << "1.3 全部断言通过：xvalue 的三类来源已确认\n";
}
