#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 3, 2, 4, 2, 5};

    std::cout << "原始: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    // erase-remove 惯用法：真正删除所有 2
    // 只写 remove 不写 erase 是经典错误——remove 只把元素前移，不缩小容器
    v.erase(std::remove(v.begin(), v.end(), 2), v.end());

    std::cout << "删除所有 2 后: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
}
