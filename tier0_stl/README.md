# 梯队0 · STL 应用 —— 可运行练习

> 已用 g++ 13.2.0（`-std=c++20 -Wall -Wextra`）实测通过，下方「输出」均为真实运行结果。
> STL 容器/算法/迭代器是 junior 级、却在工程里天天用，这里补「应用」层面（选型 + 熟练度 + 失效规则）。
> 编译运行：`g++ -std=c++20 -Wall -Wextra -O2 -o out 文件名.cpp && ./out`

学习顺序在四梯队之前，作为地基。

---

## 练习 1 vector 的 reserve 与容量增长

**源码** `exercises/ex01_vector_reserve.cpp`：

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v;
    v.reserve(4);   // 预留容量，避免反复扩容

    std::cout << "预留后 size=" << v.size() << " capacity=" << v.capacity() << "\n";

    for (int i = 0; i < 5; ++i)
        v.push_back(i);   // 第 5 个元素超过预留，触发一次扩容

    std::cout << "push 5 个后 size=" << v.size() << " capacity=" << v.capacity() << "\n";
}
```

**输出**：

```
预留后 size=0 capacity=4
push 5 个后 size=5 capacity=8
```

**验收点**：
- [ ] 能区分 `size`（元素数）和 `capacity`（已分配容量）
- [ ] 能说出 reserve 的意义：提前分配，避免多次扩容拷贝

## 练习 2 map vs unordered_map

**源码** `exercises/ex02_map_vs_unordered.cpp`（见源文件）。**输出**：

```
map 按 key 有序遍历:
  apple -> 1
  banana -> 2
unordered_map 遍历顺序不确定:
  apple -> 1
  banana -> 2
```

**验收点**：
- [ ] 能说出 map（红黑树 O(log n)、有序）与 unordered_map（哈希、平均 O(1)、无序）的取舍

## 练习 3 泛型算法四件套

**源码** `exercises/ex03_algorithms.cpp`（sort / find_if / transform / accumulate）。**输出**：

```
排序后: 1 2 3 5 8 9
第一个 >5 的是: 8
乘 2 后: 2 4 6 10 16 18
求和: 28
```

**验收点**：
- [ ] 能写出 sort、find_if、transform、accumulate 四个算法的调用
- [ ] 能说出 accumulate 在 `<numeric>` 而非 `<algorithm>`

## 练习 4 remove_if + erase 与 lower_bound

**源码** `exercises/ex04_erase_lower_bound.cpp`。**输出**：

```
删偶数后: 1 3 5 7
6 应插入到下标: 3
```

**验收点**：
- [ ] 能写对 `remove_if` + `erase` 组合
- [ ] 能说清 lower_bound 返回「不小于给定值的第一个位置」

## 练习 5 迭代器失效

**源码** `exercises/ex05_iterator_invalidation.cpp`。**输出**：

```
插入前 *it = 1
重新获取 *it2 = 1
map 删除后 size = 2
```

**验收点**：
- [ ] 能说出 vector 扩容后旧迭代器失效的原因
- [ ] 能记住「插入/删除后重新获取迭代器才安全」这条铁律

## 练习 6 optional 与 variant

**源码** `exercises/ex06_optional_variant.cpp`。**输出**：

```
15 的一个因数: 3
7 是质数（无因数）
v 是 int: 42
v 是 double: 3.14
v 是 string: hello
```

**验收点**：
- [ ] 能用 `std::optional` 表示「可能无值」的返回（替代哨兵值 -1）
- [ ] 能用 `std::variant` 在同一变量存多种类型（替代 union）

## 练习 7 string_view 与 span

**源码** `exercises/ex07_string_view_span.cpp`。**输出**：

```
hello
sum(vector) = 15
sum(array) = 21
```

**验收点**：
- [ ] 能说明 string_view / span 是「视图」，不拷贝数据
- [ ] 能说明 span 让数组和 vector 统一传参（span 需 C++20）

## 练习 8 用 STL 改写手写循环

**源码** `exercises/ex08_stl_rewrite.cpp`（偶数平方和，两种写法对比）。**输出**：

```
手写循环: 220
STL 算法: 220
```

**验收点**：
- [ ] 能用 copy_if + transform + accumulate 组合出声明式写法
- [ ] 认同「能用算法就别手写循环」，边界条件由算法保证

---

STL 应用过关后，进入 `tier1_move/`。
