#include <iostream>
#include <list>
#include <algorithm>

// ============================================================
// 容器练习 · list
// 双向链表，任意位置插入/删除 O(1)，无随机访问，遍历只能顺序
// 运行：g++ -std=c++20 -Wall -Wextra -O2 -o out list.cpp && ./out
// ============================================================

template <typename C>
void print(const char* tag, const C& c) {
    std::cout << tag;
    for (const auto& x : c) std::cout << ' ' << x;
    std::cout << '\n';
}

int main() {
    std::list<int> l;

    // ---- 增 ----
    l.push_back(2);
    l.push_front(1);                      // 头插，vector 没有
    l.push_back(4);
    l.insert(std::next(l.begin()), 3);    // 第二个位置插入（list 不能用 +n，用 next）
    print("增后:", l);                    // 1 3 2 4

    // ---- 查 / 取 ----
    std::cout << "front=" << *(++(l.begin()) ) << " back=" << l.back() << '\n';


    // list 无随机访问，不能用 l[0] 或 l.begin()+n，只能顺序走

    // ---- 改 ----
    *l.begin() = 10;                      // 解引用迭代器改
    print("改后:", l);

    // ---- 删 ----
    l.pop_front();
    l.pop_back();
    l.erase(std::next(l.begin()));
    print("删后:", l);                    // 3

    // ---- 遍历 ----
    l.assign({5, 3, 8, 1, 6});
    std::cout << "迭代器遍历:";
    for (auto it = l.begin(); it != l.end(); ++it) std::cout << ' ' << *it;
    std::cout << '\n';

    // ---- 排序 ----
    l.sort();                             // 成员函数，不是 <algorithm> 的 sort
    print("升序:", l);
    l.sort(std::greater<>{});
    print("降序:", l);

    // ---- list 特有操作 ----
    // splice：O(1) 把另一链表整体搬过来，另一链表变空
    std::list<int> l2 = {1, 2, 3};
    l.splice(l.end(), l2);
    print("splice 后:", l);
    std::cout << "l2 现在 empty=" << l2.empty() << '\n';

    // unique：去除相邻重复，需先排序
    std::list<int> dup = {1, 1, 2, 2, 2, 3};
    dup.unique();
    print("unique 后:", dup);             // 1 2 3
}
