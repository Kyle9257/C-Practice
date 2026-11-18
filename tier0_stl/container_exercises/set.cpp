#include <iostream>
#include <set>
#include <string>

// ============================================================
// 容器练习 · set
// 有序唯一元素集合，红黑树实现，自动去重 + 自动排序，操作 O(log n)
// 运行：g++ -std=c++20 -Wall -Wextra -O2 -o out set.cpp && ./out
// ============================================================

int main() {
    std::set<int> s;

    // ---- 增 ----
    s.insert(3);
    s.insert(1);
    s.insert(3);                          // 重复插入被忽略
    s.emplace(2);
    auto [it, ok] = s.insert(1);          // 1 已存在
    std::cout << "重复插入 1 成功? " << (ok ? "是" : "否") << '\n';

    // ---- 查 / 取 ----
    std::cout << "find(2):" << (s.find(2) != s.end() ? "命中" : "未命中") << '\n';
    std::cout << "count(3)=" << s.count(3) << "（set 中只有 0 或 1）\n";

    // ---- 删 ----
    s.erase(1);                           // 按值删
    std::cout << "删 1 后 size=" << s.size() << '\n';

    // ---- 遍历 ----
    std::cout << "遍历(自动升序):";
    for (int x : s) std::cout << ' ' << x;
    std::cout << '\n';

    // ---- 排序 / 范围查找 ----
    // set 天然有序，无需 sort；范围查找用 lower_bound / upper_bound
    auto lo = s.lower_bound(2);           // 第一个 >= 2
    auto hi = s.upper_bound(2);           // 第一个 >  2
    std::cout << "lower_bound(2)=" << (lo != s.end() ? *lo : -1)
              << " upper_bound(2)=" << (hi != s.end() ? *hi : -1) << '\n';

    // ---- 注意：set 不支持修改元素 ----
    // 不能写 *it = x，因为修改会破坏红黑树有序性；只能先删再加
}
