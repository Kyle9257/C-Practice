#include <iostream>
#include <deque>
#include <algorithm>

// ============================================================
// 容器练习 · deque
// 双端队列，头尾插入/删除 O(1)，支持随机访问，中间插入 O(n)
// 运行：g++ -std=c++20 -Wall -Wextra -O2 -o out deque.cpp && ./out
// ============================================================

template <typename C>
void print(const char* tag, const C& c) {
    std::cout << tag;
    for (const auto& x : c) std::cout << ' ' << x;
    std::cout << '\n';
}

int main() {
    std::deque<int> d;
    
    // ---- 增 ----
    d.push_back(3);                       // 尾插
    d.push_front(1);                      // 头插（vector 没有）
    d.push_back(5);
    d.emplace_front(1);                   // 原地构造头插
    d.insert(d.begin() + 2, 200);           // 中间插入（支持随机访问，可 +n）
    print("增后:", d);                    // 0 1 2 3 5

    // ---- 查 / 取 ----
    std::cout << "d[2]=" << d[2] << " at(1)=" << d.at(1)
              << " front=" << d.front() << " back=" << d.back() << '\n';

    // ---- 改 ----
    d[0] = 10;
    d.at(1) = 20;
    print("改后:", d);

    // ---- 删 ----
    d.pop_front();                        // 头删（vector 没有）
    d.pop_back();                         // 尾删
    d.erase(d.begin() + 1);               // 中间删
    print("删后:", d);                    // 20 2 3

    // ---- 遍历 ----
    std::cout << "下标遍历:";
    for (size_t i = 0; i < d.size(); ++i) std::cout << ' ' << d[i];
    std::cout << '\n';

    // ---- 排序 ----
    // 支持随机访问，可用 <algorithm> 的 sort
    std::sort(d.begin(), d.end());
    print("升序:", d);
}
