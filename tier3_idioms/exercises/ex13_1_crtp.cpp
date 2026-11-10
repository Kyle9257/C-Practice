#include <iostream>

// CRTP 基类：T 是派生类自身
template <typename T>
struct Base {
    void interface() {
        // 静态分发：编译期就确定调用哪个实现，无虚函数开销
        static_cast<T*>(this)->implementation();
    }
};

struct DerivedA : Base<DerivedA> {
    void implementation() { std::cout << "DerivedA 实现\n"; }
};

struct DerivedB : Base<DerivedB> {
    void implementation() { std::cout << "DerivedB 实现\n"; }
};

// 编译期多态：不需要虚函数
template <typename T>
void use(Base<T>& b) {
    b.interface();
}

int main() {
    DerivedA a;
    DerivedB b;
    use(a);
    use(b);
}
