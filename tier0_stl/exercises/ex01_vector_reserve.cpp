#include <iostream>
#include <vector>

int main() {
    std::vector<int> v;
    v.reserve(4);   // 预留容量，避免反复扩容

    std::cout << "预留后 size=" << v.size() << " capacity=" << v.capacity() << "\n";

    for (int i = 0; i < 5; ++i)
        v.push_back(i);   // 第 5 个元素超过预留，触发一次扩容

    std::cout << "push 5 个后 size=" << v.size() << " capacity=" << v.capacity() << "\n";
    std::cout << "结论：capacity 按倍数增长（通常 2 倍），reserve 可提前避免反复拷贝\n";
}
