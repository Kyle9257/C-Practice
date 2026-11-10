#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct MyClass {
    int a;
    std::string b;
    MyClass(int a_, std::string b_) : a(a_), b(std::move(b_)) {}
};

// 完美转发工厂：把参数原样转发给 T 的构造
template <typename T, typename... Args>
std::unique_ptr<T> make(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {
    std::string s = "world";

    auto p1 = make<MyClass>(42, "hello");   // 转发右值
    auto p2 = make<MyClass>(7, s);          // 转发左值，s 不会被搬空

    std::cout << "p1: " << p1->a << ", " << p1->b << "\n";
    std::cout << "p2: " << p2->a << ", " << p2->b << "\n";
    std::cout << "左值 s 仍为: \"" << s << "\"\n";
}
