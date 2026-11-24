#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

int main() {

    std::map<std::string, int> map;             // 有序：红黑树，操作 O(log n)

    std::unordered_map<std::string, int> um;  // 无序：哈希表，平均 O(1)
    // 1. 有序性 —— map 按键升序遍历；unordered_map 不保证顺序
    //    （同一份数据在同一次运行内遍历顺序是稳定的，但不保证按插入/排序，
    //     且可能因哈希种子随机化、rehash 或不同实现而变化）
    map["banana"] = 2;
    map["apple"] = 1;
    map["cherry"] = 3;
    map["c0"] = 0;
    map["c1"] = 1;
    map["a2"] = 4;
    map["a3"] = 5;

    um["banana"] = 2;
    um["apple"] = 1;
    um["cherry"] = 3;

    std::cout << "map 按键升序遍历：\n";
    for (const auto& [k, v] : map)
        std::cout << "  " << k << " -> " << v << "\n";
    // 输出：apple cherry banana 按字典序

    std::cout << "unordered_map 遍历（按桶结构，与插入/排序无关）：\n";
    for (const auto& [k, v] : um)
        std::cout << "  " << k << " -> " << v << "\n";

    // 2. 范围查找 —— 只有 map 支持 lower_bound / upper_bound
    //    找 "a" 到 "c" 区间内的所有键，unordered_map 做不到
    std::cout << "\nmap 范围查找 [a, c)：\n";

    auto lo = map.lower_bound("a");   //>=,第一个大于等于
    auto hi = map.lower_bound("c");   //>，第一个大于

    for (auto it = lo; it != hi; ++it){
        std::cout << "  " << it->first << " -> " << it->second << "\n";
    }
    // 输出 apple、banana

    // 3. 指针/引用稳定性 —— 插入新元素后：
    //    map 的迭代器/引用依然有效；unordered_map 可能因 rehash 全部失效
    int& ref = map["apple"];                    // 先持有 map 中元素的引用
    for (int i = 0; i < 1000; ++i)            // 大量插入触发 unordered_map rehash
        {
            um["key" + std::to_string(i)] = i;
        }
    map["zebra"] = 26;                          // map 再插入不影响已有引用
    std::cout << "\nmap 插入后原引用仍有效：m[\"apple\"] = " << ref << "\n";

    std::cout << "\n结论：\n"
              << "  需要有序遍历/范围查找/稳定引用 -> map\n"
              << "  只按 key 点查、追求均摊 O(1)   -> unordered_map\n";
}
