/*
学习目标：
1. 理解 ADL 会根据函数实参类型，到相关命名空间查找函数。
2. 掌握泛型代码中 using std::swap; swap(a, b); 的标准写法。
3. 理解用户类型如何提供更高效或更合适的同命名空间 swap。

练习方法：
1. 运行程序，确认调用的是 geometry::swap。
2. 暂时删除 geometry::swap，观察模板如何回退到 std::swap。
3. 给 Point 增加成员，再在自定义 swap 中完整交换它。

知识点：
- 普通名称查找会看到 using 引入的 std::swap。
- ADL 还会因为参数类型 geometry::Point 而查找 geometry 命名空间。
- 不要直接写 std::swap(left, right)，否则用户类型的同命名空间重载没有参与机会。
- 自定义 swap 应与类型放在同一命名空间，并尽可能标记 noexcept。
- 函数参数中的未限定名称 swap 正是 ADL 发挥作用的位置。
*/
#include <iostream>
#include <utility>

namespace geometry {
struct Point {
    int x;
    int y;
};

void swap(Point& left, Point& right) noexcept {
    // 自定义类型可以只交换其成员，避免不必要的整对象临时值。
    std::cout << "geometry::swap（由 ADL 找到）\n";
    std::swap(left.x, right.x);
    std::swap(left.y, right.y);
}
}  // namespace geometry

template <typename T>
void generic_swap(T& left, T& right) noexcept(noexcept(swap(left, right))) {
    // 先提供 std::swap 作为回退，再让未限定调用参与 ADL。
    using std::swap;
    swap(left, right);
}

int main() {
    geometry::Point first{1, 2};
    geometry::Point second{3, 4};
    generic_swap(first, second);
    std::cout << "first = (" << first.x << ", " << first.y << ")\n";
}
