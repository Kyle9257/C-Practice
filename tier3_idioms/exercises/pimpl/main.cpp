#include "widgetPractice.h"
#include <iostream>

int main() {
    widgetPractice w(20, "str");
    std::cout << "w.counter = " << w.getCounter() << ", w.name = " << w.getName() << "\n";

    widgetPractice w2 = w;                 // 拷贝构造
    std::cout << "w2.counter = " << w2.getCounter() << ", w2.name = " << w2.getName() << "\n";

    widgetPractice w3 = std::move(w);      // 移动构造
    std::cout << "w3.counter = " << w3.getCounter() << ", w3.name = " << w3.getName() << "\n";

    widgetPractice w4;
    w4 = w2;                               // 拷贝赋值
    std::cout << "w4.counter = " << w4.getCounter() << ", w4.name = " << w4.getName() << "\n";

    w4 = std::move(w3);                    // 移动赋值
    std::cout << "w4.counter = " << w4.getCounter() << ", w4.name = " << w4.getName() << "\n";
}
