#include <iostream>
#include <unordered_map>
#include <string>

// ============================================================
// 容器练习 · unordered_map
// 无序键值对，哈希表实现，点查平均 O(1)，不保证顺序、不支持范围查找
// 运行：g++ -std=c++20 -Wall -Wextra -O2 -o out unordered_map.cpp && ./out
// ============================================================

int main() {
    std::unordered_map<std::string, int> um;

    // ---- 增 ----
    um["apple"] = 1;
    um["banana"] = 2;
    um.emplace("cherry", 3);

    auto [it, ok] = um.insert({"apple", 999});
    std::cout << "重复插入 apple 成功? " << (ok ? "是" : "否") << '\n';

    // ---- 查 / 取 ----
    std::cout << "um[\"apple\"]=" << um["apple"]
              << " at(banana)=" << um.at("banana") << '\n';

    auto f = um.find("cherry");
    std::cout << "find(cherry):" << (f != um.end() ? "命中" : "未命中") << '\n';

    // ---- 改 ----
    um["apple"] = 100;
    f->second = 30;
    std::cout << "改后 apple=" << um["apple"] << " cherry=" << um["cherry"] << '\n';

    // ---- 删 ----
    um.erase("banana");
    std::cout << "删后 size=" << um.size() << '\n';

    // ---- 遍历 ----
    // 无序：顺序与插入/排序无关，且 rehash 后可能变化
    std::cout << "遍历(无序):";
    for (const auto& [k, v] : um) std::cout << "  " << k << "->" << v;
    std::cout << '\n';

    // ---- 排序 / 范围查找 ----
    // 无序容器没有 sort，也没有 lower_bound/upper_bound，只能点查
    std::cout << "unordered_map 只支持点查，不支持范围查找/排序\n";
}
