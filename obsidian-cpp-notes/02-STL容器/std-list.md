# std::list

## 定义

双向链表容器，任意位置插入/删除 O(1)，无随机访问，只能顺序遍历。

## 要点

- 双向链表，任意位置插入/删除 O(1)，但不能用下标 `[]` 随机访问。
- 不支持 `vec.begin() + n`，定位要用 `std::next(it, n)`。
- 插入/删除不使其他元素的迭代器失效（与 [[std-vector容器]] 不同）。
- 构造：`assign`；插入：`push_front` / `push_back` / `insert`；删除：`pop_front` / `pop_back` / `erase`。

## 代码示例

```cpp
std::list<int> l;
l.push_front(1);
l.push_back(2);
l.insert(std::next(l.begin()), 3);   // 在第二个位置插入 3
// l = {1, 3, 2}

for (auto it = l.begin(); it != l.end(); ++it)
    std::cout << *it << " ";
```

## 应用场景

- 中间频繁增删、且需要迭代器稳定的场景（如 LRU 缓存链表）。

## 关联

- [[std-vector容器]]（对比）
- [[std-deque]]（对比）
