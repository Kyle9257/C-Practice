#include <iostream>
#include <string>
#include <utility>
#include <vector>

//移动还是复制

struct Widget {
    std::string data;
    Widget(const std::string& s) : data(s) {}

    Widget(const Widget& o) : data(o.data) { std::cout << "  copy ctor\n"; }
    Widget(Widget&& o) noexcept : data(std::move(o.data)) { std::cout << "  move ctor\n"; }
};

int main() {
    std::vector<Widget> v;
    v.reserve(4);

    std::cout << "push 临时对象（右值）:\n";
    v.push_back(Widget("hello"));

    std::cout << "push 左值:\n";
    Widget w("world");
    v.push_back(w);

    std::cout << "push std::move(左值):\n";
    v.push_back(std::move(w));
}
