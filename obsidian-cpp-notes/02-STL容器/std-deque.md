# std::deque

## 定义

双端队列，支持两端 O(1) 插入删除，也支持下标随机访问，介于 [[std-vector容器]] 和 [[std-list]] 之间。

## 要点

- 双端插入：`push_front` / `push_back` / `emplace_front` / `emplace_back`，中间插入用 `insert`。
- 支持 `[]` 和 `at()` 随机访问。
- 两端增删不会使已有元素/引用失效（与 [[std-vector容器]] 扩容失效不同）。
- 底层分块存储，元素较大或需稳定引用时优于 vector。

## 代码示例

```cpp
std::deque<int> d;
d.push_back(2);
d.push_front(1);   // d = {1, 2}
d.emplace_back(3); // d = {1, 2, 3}

std::cout << d[0] << "\n";   // 随机访问
```

## 应用场景

- 经典应用：滑动窗口（两端进出、保持稳定引用）。

## 关联

- [[std-vector容器]]（对比）
- [[std-list]]（对比）
