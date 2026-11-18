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

## 练习 3 泛型算法六大类

**源码** `exercises/ex03_algorithms.cpp`，覆盖排序 / 查找 / 修改拷贝 / 重排 / 数值 / C++20 ranges。**输出**：

```
sort 升序:       1 2 3 5 6 8 9
sort 降序:       9 8 6 5 3 2 1
stable_sort(key): (1,b) (1,d) (2,a) (2,c)   // key 相同保持原顺序
partial_sort 前3: 1 2 4 9 8 7 5
按末位数字排序: 31 22 15 7 48
find(7):        命中
lower_bound(7) 下标 = 3   upper_bound(7) 下标 = 4
6 应插入下标 = 3   // 保持有序
transform 平方:  1 4 9 16 25
copy_if 偶数:    4 16
partition 偶数前置: 8 2 6 4  |   5 3 7 1
next_permutation: [123] [132] [213] [231] [312] [321]
sum = 15   prod = 120   前缀和: 1 3 6 10 15   min = 1   max = 5
ranges 管道:     90 80 60
```

**验收点**：
- [ ] 能说清 `sort` / `stable_sort` / `partial_sort` 的取舍（稳定 / 只排前 k 个）
- [ ] 能写出 `lower_bound` / `upper_bound` / `equal_range` 二分三件套，并懂「未命中给出插入位置」
- [ ] 能组合 `transform` + `copy_if` + `back_inserter` 做声明式数据变换
- [ ] 能说清 `partition` 与 `next_permutation` 的用途
- [ ] 能说出 `accumulate` / `partial_sum` 在 `<numeric>`，以及 `min/max_element` 在 `<algorithm>`
- [ ] 能读懂 `ranges::filter | transform | take` 管道写法（C++20）

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

## 练习 9 容器常用操作

**目录** `container_exercises/`，每个容器一个独立文件，统一按「增→查→改→删→遍历→排序」演示：

| 文件 | 容器 | 要点 |
|------|------|------|
| `vector.cpp` | vector | 随机访问 O(1)，尾插均摊 O(1)，中间插入 O(n) |
| `list.cpp` | list | 头尾插删 O(1)，无随机访问，成员 `sort`/`splice`/`unique` |
| `map.cpp` | map | 红黑树有序，`[]` 会插入、`at`/`find` 不会，支持范围查找 |
| `unordered_map.cpp` | unordered_map | 哈希点查 O(1)，无序，不支持范围查找/排序 |
| `set.cpp` | set | 自动去重+有序，不支持修改元素 |
| `deque.cpp` | deque | 头尾插删 O(1)，支持随机访问，中间插入 O(n) |

**验收点**：
- [ ] 能写出 vector 的 push_back / emplace_back / insert / erase / at / sort
- [ ] 能说出 list 与 vector 差异：头插 O(1)、无随机访问、成员 sort/splice/unique
- [ ] 能说清 map 的 `[]` 会插入不存在的 key，`find`/`at` 不会
- [ ] 能说清 unordered_map / set 不支持范围查找，set 不支持修改元素

---

STL 应用过关后，进入 `tier1_move/`。
