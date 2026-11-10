#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 手写循环：统计偶数的平方和
    int hand = 0;
    for (int x : v)
        if (x % 2 == 0)
            hand += x * x;
    std::cout << "手写循环: " << hand << "\n";

    // STL 算法版：更声明式、更少边界错误
    std::vector<int> evens;
    std::copy_if(v.begin(), v.end(), std::back_inserter(evens),
                 [](int x) { return x % 2 == 0; });
    std::transform(evens.begin(), evens.end(), evens.begin(),
                   [](int x) { return x * x; });
    int stl = std::accumulate(evens.begin(), evens.end(), 0);
    std::cout << "STL 算法: " << stl << "\n";

    std::cout << "结论：能用算法就别手写循环，边界条件由算法保证\n";
}
