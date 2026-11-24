/*
学习目标：
1. 掌握 lambda 的基本语法：[捕获列表](参数列表) { 函数体 }。
2. 区分按值捕获和按引用捕获。
3. 学会把 lambda 作为 STL 算法的行为参数。

练习方法：
1. 先预测 count、sum 和 multiply 的输出，再运行程序。
2. 把 [threshold] 改成 [&threshold]，观察代码仍能工作，但捕获语义发生变化。
3. 尝试将 threshold 改成 4，验证谓词会影响 count_if 的结果。

知识点：
- [threshold] 会把当前值复制进闭包对象，lambda 内默认不能修改这份副本。
- [&sum] 保存外部变量的引用，因此 lambda 对 sum 的修改会反映到外部。
- [] 不捕获任何外部变量，适合无状态的小函数。
- 引用捕获要求被引用对象在 lambda 使用期间仍然存活，否则会产生悬空引用。
*/
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    const int threshold = 4;
    std::vector<int> values{1, 2, 3, 4, 5};

    // count_if 会对每个元素调用谓词；返回 true 的元素会被计数。
    const auto count = std::count_if(values.begin(), values.end(),
                                     [threshold](int value) { return value > threshold; });

    int sum = 0;
    // 按引用捕获 sum，使 lambda 可以累加到外部变量。这里lambda生成的operator()是const成员函数
    std::for_each(values.begin(), values.end(), [&sum](int value) { sum += value; });

    // 无捕获 lambda 可以看作一个局部定义的轻量函数对象。
    const auto multiply = [](int left, int right) { return left * right; };
    std::cout << "大于 " << threshold << " 的元素数: " << count << '\n';
    std::cout << "总和: " << sum << '\n';
    std::cout << "3 * 4 = " << multiply(3, 4) << '\n';
}
