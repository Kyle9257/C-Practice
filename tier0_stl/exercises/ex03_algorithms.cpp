#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::vector<int> v = {5, 2, 8, 1, 9, 3};

    std::sort(v.begin(), v.end());
    std::cout << "排序后: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    auto it = std::find_if(v.begin(), v.end(), [](int x) { return x > 5; });
    if (it != v.end()) std::cout << "第一个 >5 的是: " << *it << "\n";

    std::vector<int> doubled(v.size());
    std::transform(v.begin(), v.end(), doubled.begin(), [](int x) { return x * 2; });
    std::cout << "乘 2 后: ";
    for (int x : doubled) std::cout << x << " ";
    std::cout << "\n";

    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "求和: " << sum << "\n";
}
