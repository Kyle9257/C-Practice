#include <iostream>
#include <vector>
#include <map>

int main() {
    // vector 扩容导致迭代器失效
    std::vector<int> v = {1, 2, 3};
    auto it = v.begin();
    std::cout << "插入前 *it = " << *it << "\n";

    v.push_back(4);   // 可能触发扩容，it 失效
    // 之后再用 it 是未定义行为！

    auto it2 = v.begin();   // 正确做法：重新获取
    std::cout << "重新获取 *it2 = " << *it2 << "\n";

    // map 删除单个元素：被删元素迭代器失效，其余不受影响
    std::map<int, std::string> m = {{1, "a"}, {2, "b"}, {3, "c"}};
    m.erase(2);   // 只删除 key=2
    std::cout << "map 删除后 size = " << m.size() << "\n";

    std::cout << "结论：容器插入/删除后不要复用旧迭代器，重新获取才安全\n";
}
