#include <iostream>
#include <utility>

class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;             // 禁拷贝构造
    NonCopyable& operator=(const NonCopyable&) = delete;  // 禁拷贝赋值

    NonCopyable(NonCopyable&&) = default;                 // 允许移动
    NonCopyable& operator=(NonCopyable&&) = default;
};

int main() {
    NonCopyable a;
    NonCopyable b = std::move(a);   // 移动 OK
    (void)b;

    // NonCopyable c = a;           // 取消注释：拷贝被删除，编译错误
    std::cout << "non-copyable 但可移动\n";
}
