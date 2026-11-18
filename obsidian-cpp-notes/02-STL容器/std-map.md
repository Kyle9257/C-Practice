# std::map

## 定义

有序键值容器，底层是[[红黑树]]，按键自动排序。

## 要点

- 插入/查找/删除均为 O(log n)。
- 按键升序遍历，支持范围查找（[[lower_bound 与 upper_bound]]）。
- 迭代器/引用稳定：插入删除其他元素不影响已有迭代器。
- 要求 key 支持 `<` 比较，或提供自定义比较器。
- ==🔴增加==------insert(); emplace_back()
- ==🟠查找==------find()
- ==🟡删除==------erase()
- ==🟢条件查找==---lower_bound(); upper_bound()

## 代码示例

```cpp
std::map<std::string, int> m;
m["banana"] = 2;
m["apple"]  = 1;   // 自动按键排序：apple 排在 banana 前
```

## 关联

- [[std-unordered-map]]（对比）
- [[红黑树]]
- [[lower_bound 与 upper_bound]]
