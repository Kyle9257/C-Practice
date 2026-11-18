#include <iostream>
#include <vector>
#include <algorithm>

// ============================================================
// 容器练习 · vector
// 动态数组，随机访问 O(1)，尾插/尾删均摊 O(1)，中间插入 O(n)
// 运行：g++ -std=c++20 -Wall -Wextra -O2 -o out vector.cpp && ./out
// ============================================================

template <typename C>
void print(const char* tag, const C& c) {
    std::cout << tag;
    for (const auto& x : c) std::cout << ' ' << x;
    std::cout << '\n';
}

int main() {
    std::vector<int> v;

    // ---- 增 ----
    v.push_back(3);                       // 尾插
    v.emplace_back(1);                    // 原地构造，比 push_back 少一次拷贝
    v.emplace_back(5);
    v.insert(v.begin(), 2);               // 开头插入
    v.insert(v.end(), {4, 6});            // 批量尾插
    print("增后:", v);                    // 2 3 1 5 4 6

    // ---- 查 / 取 ----
    std::cout << "v[0]=" << v[0]
              << " v.at(1)=" << v.at(1)            // at 越界抛异常，[] 不检查
              << " front=" << v.front()
              << " back=" << v.back() << '\n';

    // ---- 改 ----
    v[0] = 20;
    v.at(1) = 30;
    print("改后:", v);                    // 20 30 1 5 4 6

    // ---- 删 ----
    v.erase(v.begin());                   // 删第一个
    v.erase(v.begin() + 1, v.begin() + 3); // 删区间 [1,3)
    v.pop_back();                         // 删最后一个
    print("删后:", v);                    // 30 4

    // ---- 遍历 ----
    std::cout << "下标遍历:";
    for (size_t i = 0; i < v.size(); ++i) std::cout << ' ' << v[i];
    std::cout << "\n迭代器遍历:";
    for (auto it = v.begin(); it != v.end(); ++it) std::cout << ' ' << *it;
    std::cout << '\n';

    // ---- 排序 ----
    std::sort(v.begin(), v.end());
    print("升序:", v);
    std::sort(v.begin(), v.end(), std::greater<>{});
    print("降序:", v);

    // ---- 其他常用 ----
    std::cout << "size=" << v.size()
              << " empty=" << v.empty()
              << " 是否有5=" << (std::find(v.begin(), v.end(), 5) != v.end()) << '\n';
    v.clear();                            // 清空，size=0 但 capacity 不变
    std::cout << "clear 后 size=" << v.size() << '\n';
}
