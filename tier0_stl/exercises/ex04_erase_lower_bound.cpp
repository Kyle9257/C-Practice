#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};

    // remove_if + erase：删除所有偶数
    v.erase(std::remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), v.end());
    std::cout << "删偶数后: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    // lower_bound：在有序序列中找「不小于给定值」的第一个位置
    std::vector<int> sorted = {1, 3, 5, 7, 9};
    auto it = std::lower_bound(sorted.begin(), sorted.end(), 6);
    std::cout << "6 应插入到下标: " << (it - sorted.begin()) << "\n";
}
