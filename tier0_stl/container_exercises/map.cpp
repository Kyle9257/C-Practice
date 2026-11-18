#include <iostream>
#include <map>
#include <string>

// ============================================================
// 容器练习 · map
// 有序键值对，红黑树实现，操作 O(log n)，按键升序遍历
// 运行：g++ -std=c++20 -Wall -Wextra -O2 -o out map.cpp && ./out
// ============================================================

int main() {
    std::map<std::string, int> m;

    // ---- 增 ----
    m["apple"] = 1;                       // [] 不存在则插入
    m.insert({"banana", 2});              // insert 已存在则忽略，返回 pair<迭代器,bool>
    m.emplace("cherry", 3);               // 原地构造

    auto [it, ok] = m.insert({"apple", 999}); // apple 已存在，插入失败
    std::cout << "重复插入 apple 成功? " << (ok ? "是" : "否")
              << "（值保持 " << it->second << "）\n";

    // ---- 查 / 取 ----
    std::cout << "m[\"apple\"]=" << m["apple"]
              << " m.at(\"banana\")=" << m.at("banana") << '\n';
    // 区别：m["xx"] 若不存在会插入一个默认值；at 不存在则抛异常

    auto f = m.find("cherry");
    std::cout << "find(cherry):" << (f != m.end() ? "命中" : "未命中") << '\n';

    // ---- 改 ----
    m["apple"] = 100;                     // 改已有 key
    f->second = 30;                       // 用 find 返回的迭代器改
    std::cout << "改后 apple=" << m["apple"] << " cherry=" << m["cherry"] << '\n';

    // ---- 删 ----
    m.erase("banana");                    // 按 key 删
    std::cout << "删 banana 后 size=" << m.size() << '\n';

    // ---- 遍历 ----
    std::cout << "遍历(按键升序):";
    for (const auto& [k, v] : m) std::cout << "  " << k << "->" << v;
    std::cout << '\n';

    // ---- 排序 / 范围查找 ----
    // map 天然有序，无需 sort；范围查找用 lower_bound / upper_bound
    auto lo = m.lower_bound("a");         // 第一个 >= "a"
    auto hi = m.upper_bound("c");         // 第一个 >  "c"
    std::cout << "范围[a,c]:";
    for (auto i = lo; i != hi; ++i) std::cout << "  " << i->first;
    std::cout << '\n';
}
