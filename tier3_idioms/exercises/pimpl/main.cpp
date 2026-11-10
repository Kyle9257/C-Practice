#include "widget.h"
#include <iostream>

int main() {
    Widget w(10);
    std::cout << "w.value = " << w.value() << "\n";
    w.set_value(20);

    Widget w2 = w;                 // 拷贝
    std::cout << "w2.value = " << w2.value() << "\n";

    Widget w3 = std::move(w);      // 移动
    std::cout << "w3.value = " << w3.value() << "\n";
}
