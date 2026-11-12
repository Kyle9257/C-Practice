#include <iostream>
#include <vector>

struct Safe {
    Safe() { std::cout << "  Safe() 构造\n"; }
    Safe(const Safe&) { std::cout << "  Safe(copy)\n"; }
    Safe(Safe&&) noexcept { std::cout << "  Safe(move)\n"; }   // 移动构造标了 noexcept
};
//加了noexcept。没有noexcept，std::move_if_noexcept()会退化位copy构造。保障异常安全，搬旧元素的时候若抛出异常，需要旧缓冲区完好
//，原地回滚，而移动会把原对象掏空

struct Unsafe {
    Unsafe() { std::cout << "  Unsafe()构造\n"; }
    Unsafe(const Unsafe&) { std::cout << "  Unsafe(copy)\n"; }
    Unsafe(Unsafe&&) { std::cout << "  Unsafe(move)\n"; }       // 移动构造没标 noexcept
};

int main() {
    std::cout << "== vector<Safe> 扩容：搬旧元素应走 move ==\n";
    std::vector<Safe> a;//
    a.reserve(3);
    a.push_back(Safe());
    a.push_back(Safe());
    a.push_back(Safe());   
    a.push_back(Safe());   // 原本大小是3，这里需要增加到4，触发扩容

    std::cout << "\n== vector<Unsafe> 扩容：搬旧元素应走 copy ==\n";
    std::vector<Unsafe> b;
    b.reserve(3);
    b.push_back(Unsafe());
    b.push_back(Unsafe());
   // b.push_back(Unsafe()); // 触发扩容
}
