#include <iostream>
#include <map>
#include <unordered_map>

int main() {
    std::map<std::string, int> m;             // 有序（红黑树，O(log n)）
    std::unordered_map<std::string, int> um;  // 无序（哈希表，平均 O(1)）

    m["banana"] = 2; m["apple"] = 1;
    um["banana"] = 2; um["apple"] = 1;

    std::cout << "map 按 key 有序遍历:\n";
    for (const auto& [k, v] : m) std::cout << "  " << k << " -> " << v << "\n";

    std::cout << "unordered_map 遍历顺序不确定:\n";
    for (const auto& [k, v] : um) std::cout << "  " << k << " -> " << v << "\n";

    std::cout << "结论：需要有序遍历/范围查找用 map，只查单个 key 用 unordered_map\n";
}
