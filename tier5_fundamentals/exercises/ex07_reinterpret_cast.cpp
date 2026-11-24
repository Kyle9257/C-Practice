/*
学习目标：
1. 理解 reinterpret_cast 只改变编译器看待地址的类型，不转换底层数据。
2. 观察整数的对象表示和机器端序。
3. 知道复制对象字节时优先使用 memcpy 或 C++20 的 bit_cast。

练习方法：
1. 运行程序，判断当前机器使用小端序还是大端序。
2. 修改 value，预测并核对输出的字节顺序。
3. 不要把 bytes 强转为不相关类型后解引用；思考对齐和严格别名规则风险。

知识点：
- char、unsigned char 和 std::byte 可以合法观察任意对象的字节表示。
- reinterpret_cast 不保证目标地址满足新类型的对齐要求。
- 通过不相关类型指针读写对象可能违反严格别名规则，导致未定义行为。
- memcpy 按字节复制对象表示，不会触发类型别名问题。
- 本例用于认识底层表示，不代表业务代码应大量使用 reinterpret_cast。
*/
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

int main() {
    const std::uint32_t value = 0x12345678U;
    // unsigned char 指针是观察任意对象原始字节的合法方式。
    const auto* bytes = reinterpret_cast<const unsigned char*>(&value);

    std::cout << "对象的原始字节（顺序取决于端序）:";
    for (std::size_t i = 0; i < sizeof(value); ++i) {
        std::cout << ' ' << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<unsigned int>(bytes[i]);
    }
    std::cout << '\n';

    std::uint32_t copy;
    // 使用 memcpy 恢复对象值，避免通过不相关类型指针直接解引用。
    std::memcpy(&copy, bytes, sizeof(copy));
    std::cout << "memcpy 后恢复: 0x" << std::hex << copy << '\n';
}
