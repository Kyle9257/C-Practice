#include <iostream>
#include <vector>

struct Safe {
    Safe() { std::cout << "  Safe()\n"; }
    Safe(const Safe&) { std::cout << "  Safe(copy)\n"; }
    Safe(Safe&&) noexcept { std::cout << "  Safe(move)\n"; }   // 移动构造标了 noexcept
};

struct Unsafe {
    Unsafe() { std::cout << "  Unsafe()\n"; }
    Unsafe(const Unsafe&) { std::cout << "  Unsafe(copy)\n"; }
    Unsafe(Unsafe&&) { std::cout << "  Unsafe(move)\n"; }       // 移动构造没标 noexcept
};

int main() {
    std::cout << "== vector<Safe> 扩容：搬旧元素应走 move ==\n";
    std::vector<Safe> a;
    a.push_back(Safe());
    a.push_back(Safe());
    a.push_back(Safe());   // 触发扩容

    std::cout << "\n== vector<Unsafe> 扩容：搬旧元素应走 copy ==\n";
    std::vector<Unsafe> b;
    b.push_back(Unsafe());
    b.push_back(Unsafe());
    b.push_back(Unsafe()); // 触发扩容
}
