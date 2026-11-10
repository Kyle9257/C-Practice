#include <iostream>

// 主模板
template <typename T>
struct Kind {
    static const char* name() { return "值类型"; }
};

// 偏特化：T 是左值引用
template <typename T>
struct Kind<T&> {
    static const char* name() { return "左值引用"; }
};

// 偏特化：T 是指针
template <typename T>
struct Kind<T*> {
    static const char* name() { return "指针"; }
};

// 注意：函数模板不能偏特化，只能用重载。
// 下面这种写法是「重载」不是「偏特化」：
//   template <typename T> void f(T) {}
//   template <typename T> void f(T*) {}

int main() {
    std::cout << Kind<int>::name() << "\n";    // 值类型
    std::cout << Kind<int&>::name() << "\n";   // 左值引用
    std::cout << Kind<int*>::name() << "\n";   // 指针
}
