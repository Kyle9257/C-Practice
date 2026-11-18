# 梯队0 · STL 应用

> 来源：`tier0_stl/`。容器/算法/迭代器是 junior 级却在工程里天天用，这里补「应用」层面：选型 + 熟练度 + 失效规则。
> 编译：`g++ -std=c++20 -Wall -Wextra -O2 -o out 文件名.cpp && ./out`

---

## 练习 1 vector 的 reserve 与容量增长

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

---

## 练习 2 map vs unordered_map

见 [[std-map]]、[[std-unordered-map]] 术语卡。核心取舍：有序 O(log n)（红黑树）vs 哈希平均 O(1)（无序）。

**验收点**：
- [ ] 能说出两者取舍：需要有序遍历/范围查找/稳定引用用 map，只点查用 unordered_map

---

## 练习 3 泛型算法四件套

```cpp
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {5, 3, 8, 1, 9, 2};

    std::sort(v.begin(), v.end());
    std::cout << "排序后: ";
    for (int x : v) std::cout << x << " ";

    auto it = std::find_if(v.begin(), v.end(), [](int x) { return x > 5; });
    std::cout << "\n第一个 >5 的是: " << *it << "\n";

    std::vector<int> out;
    std::transform(v.begin(), v.end(), std::back_inserter(out), [](int x) { return x * 2; });
    std::cout << "乘 2 后: ";
    for (int x : out) std::cout << x << " ";

    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "\n求和: " << sum << "\n";
}
```

**输出**：

```
排序后: 1 2 3 5 8 9
第一个 >5 的是: 8
乘 2 后: 2 4 6 10 16 18
求和: 28
```

**验收点**：
- [ ] 能写出 sort、find_if、transform、accumulate 四个算法的调用
- [ ] 能说出 accumulate 在 `<numeric>` 而非 `<algorithm>`

---

## 练习 4 remove_if + erase 与 lower_bound

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};

    v.erase(std::remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), v.end());
    std::cout << "删偶数后: ";
    for (int x : v) std::cout << x << " ";

    auto pos = std::lower_bound(v.begin(), v.end(), 6);
    std::cout << "\n6 应插入到下标: " << std::distance(v.begin(), pos) << "\n";
}
```

**输出**：

```
删偶数后: 1 3 5 7
6 应插入到下标: 3
```

**验收点**：
- [ ] 能写对 `remove_if` + `erase` 组合
- [ ] 能说清 lower_bound 返回「不小于给定值的第一个位置」（见 [[lower_bound 与 upper_bound]]）

---

## 练习 5 迭代器失效

```cpp
#include <iostream>
#include <map>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3};
    auto it = v.begin();
    std::cout << "插入前 *it = " << *it << "\n";

    for (int i = 0; i < 100; ++i) v.push_back(i);  // 触发扩容，it 失效

    auto it2 = v.begin();   // 重新获取
    std::cout << "重新获取 *it2 = " << *it2 << "\n";

    std::map<int, int> m{{1, 1}, {2, 2}, {3, 3}};
    m.erase(2);
    std::cout << "map 删除后 size = " << m.size() << "\n";
}
```

**输出**：

```
插入前 *it = 1
重新获取 *it2 = 1
map 删除后 size = 2
```

**验收点**：
- [ ] 能说出 vector 扩容后旧迭代器失效的原因（底层重新分配内存）
- [ ] 记住铁律：插入/删除后重新获取迭代器才安全

---

## 练习 6 optional 与 variant

```cpp
#include <iostream>
#include <optional>
#include <string>
#include <variant>

std::optional<int> factor(int n) {
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return i;
    return std::nullopt;   // 质数无因数
}

int main() {
    auto f = factor(15);
    if (f) std::cout << "15 的一个因数: " << *f << "\n";

    auto g = factor(7);
    if (!g) std::cout << "7 是质数（无因数）\n";

    std::variant<int, double, std::string> v;
    v = 42;    std::cout << "v 是 int: " << std::get<int>(v) << "\n";
    v = 3.14;  std::cout << "v 是 double: " << std::get<double>(v) << "\n";
    v = "hello"; std::cout << "v 是 string: " << std::get<std::string>(v) << "\n";
}
```

**输出**：

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

---

## 练习 7 string_view 与 span

```cpp
#include <iostream>
#include <span>
#include <string_view>
#include <vector>

int sum(std::span<const int> s) {
    int t = 0;
    for (int x : s) t += x;
    return t;
}

int main() {
    std::string_view sv = "hello";
    std::cout << sv << "\n";

    std::vector<int> v = {1, 2, 3, 4, 5};
    std::cout << "sum(vector) = " << sum(v) << "\n";

    int arr[] = {1, 2, 3, 4, 5, 6};
    std::cout << "sum(array) = " << sum(arr) << "\n";
}
```

**输出**：

```
hello
sum(vector) = 15
sum(array) = 21
```

**验收点**：
- [ ] 能说明 string_view / span 是「视图」，不拷贝数据
- [ ] 能说明 span 让数组和 vector 统一传参（span 需 C++20）

---

## 练习 8 用 STL 改写手写循环

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 手写循环
    int s1 = 0;
    for (int x : v) if (x % 2 == 0) s1 += x * x;
    std::cout << "手写循环: " << s1 << "\n";

    // STL 算法
    std::vector<int> evens;
    std::copy_if(v.begin(), v.end(), std::back_inserter(evens), [](int x) { return x % 2 == 0; });
    std::transform(evens.begin(), evens.end(), evens.begin(), [](int x) { return x * x; });
    int s2 = std::accumulate(evens.begin(), evens.end(), 0);
    std::cout << "STL 算法: " << s2 << "\n";
}
```

**输出**：

```
手写循环: 220
STL 算法: 220
```

**验收点**：
- [ ] 能用 copy_if + transform + accumulate 组合出声明式写法
- [ ] 认同「能用算法就别手写循环」，边界条件由算法保证

---

## 关联

- [[std-map]] · [[std-unordered-map]] · [[lower_bound 与 upper_bound]] · [[红黑树]] · [[哈希表]]
- 资源对照：[[C++补课执行表]]
- 下一梯队 → [[tier1-移动语义]]
