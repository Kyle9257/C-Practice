#include "widget.h"
#include <iostream>

// Impl 的完整定义只出现在 .cpp 里，头文件的用户看不到
struct Widget::Impl {
    int value;
    explicit Impl(int v) : value(v) { std::cout << "  Impl 构造\n"; }
};

Widget::Widget(int value) : pImpl(std::make_unique<Impl>(value)) {}

Widget::~Widget() = default;   // 必须在 Impl 完整定义之后才能 default

Widget::Widget(const Widget& o) : pImpl(std::make_unique<Impl>(o.pImpl->value)) {
    std::cout << "  赋值构造函数\n";
}
Widget::Widget(Widget&&) noexcept = default;

Widget& Widget::operator=(const Widget& o) {
    if (this != &o) pImpl->value = o.pImpl->value;
    std::cout << "  copy assign\n";
    return *this;
}
Widget& Widget::operator=(Widget&&) noexcept = default;

int Widget::value() const { return pImpl->value; }
void Widget::set_value(int v) { pImpl->value = v; }
