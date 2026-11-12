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
//Args&&:参数包与万能引用的组合，展开后每个形参各自独立推导

template <typename T, typename... Args>
std::unique_ptr<T> make_left(Args&&... args){

    return std::unique_ptr<T>(new T(args...));//这里没有推导，直接全部按照左值，
}

template <typename T, typename... Args>
std::unique_ptr<T> make_right(Args&&...args){
    return std::unique_ptr<T>(new T(std::move(args)...));   //全部按照右值,这样写当让会被搬空，都有std::move了
}


int main() {
    std::string s = "world";

    auto p1 = make<MyClass>(42, "hello");   // 转发右值
    auto p2 = make<MyClass>(7, s);          // 转发左值，s 不会被搬空

    std::cout << "p1: " << p1->a << ", " << p1->b << "\n";
    std::cout << "p2: " << p2->a << ", " << p2->b << "\n";
    std::cout << "左值 s 仍为: \"" << s << "\"\n";


    std::string ss = "hello 你好";
    auto p3 = make_left<MyClass>(12,"hell0");
    std::cout << "p3:" << p3->a <<"," << p3->b <<"\n";

    auto p4 = make_right<MyClass>(10,ss);
    std::cout << "p4:" << p4->a <<"," << p4->b <<"\n";
    std::cout << "ss :" << ss << "\n";
}
