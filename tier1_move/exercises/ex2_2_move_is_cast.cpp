#include <iostream>
#include <string>
#include <utility>

// std::move 的实现本质（去掉 constexpr/noexcept 等修饰后就是这一行）：
// template<class T> remove_reference_t<T>&& move(T&& t) {
//     return static_cast<remove_reference_t<T>&&>(t);
// }

int main() {
    // 证明 1：std::move 单独出现，什么都不发生
    std::string c = "xyz";
    (void)std::move(c);                 // 这一行没有效果（(void) 压掉 nodiscard 警告）
    std::cout << "单独 std::move(c) 后 c = \"" << c << "\"\n"; // 仍是 "xyz"
    
    int a = 22;
    (void)std::move(a);
    
    std::cout<<"单独std::move(a)后，a = " << a << std::endl;

    int b= std::move(a);    //这里int没有移动构造函数，退化位普通拷贝
    std::cout<< "a = " << a <<std::endl;
    std::cout<< "b = "<< b <<std::endl;
    // 证明 2：真正发生移动的是「移动构造函数被调用」，不是 std::move
    std::string src = "old value";
    std::string dst = std::move(src);   // 这里调用 string 的移动构造，src 被搬空
    std::cout << "移动构造后 src = \"" << src << "\"\n";        // 通常为空
    std::cout << "移动构造后 dst = \"" << dst << "\"\n";        // "old value"

    // 证明 3：移动后的对象仍是「合法但未指定」，可以继续赋值
    src = "reassigned";
    std::cout << "移动后重新赋值 src = \"" << src << "\"\n";    // "reassigned"
}
