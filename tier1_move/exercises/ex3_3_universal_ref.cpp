#include <iostream>
#include <type_traits>

// T&& 是不是万能引用，取决于 T 是否被「推导」出来
template <typename T>
void f(T&&) {
    if constexpr (std::is_lvalue_reference_v<T>)
        std::cout << "  T 推导为左值引用，T&& 折叠成 T&\n";
    else
        std::cout << "  T 推导为值类型，T&& 是右值引用\n";
}

int main() {
    int x = 0;

    std::cout << "f(x):\n"; f(x);   // T 推导为 int&
    std::cout << "f(5):\n"; f(5);   // T 推导为 int

    std::cout << "--- 显式指定 T，万能引用失效 ---\n";
    // f<int>(x);  // 取消注释会编译错误：T 被指定为 int，T&& 就是 int&&，不能绑左值 x
    std::cout << "f<int>(5):\n"; f<int>(5);    // T&& = int&&，只接受右值

    std::cout << "结论：万能引用的前提是「T 由实参推导」。一旦手动指定 T，就退化成普通右值引用。\n";
}
