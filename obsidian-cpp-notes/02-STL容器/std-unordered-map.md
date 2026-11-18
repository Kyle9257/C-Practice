# std::unordered_map

## 定义

无序键值容器，底层是哈希表，平均 O(1) 查找。

## 要点

- 点查均摊 O(1)，但最坏 O(n)。
- 遍历顺序按桶结构，与插入/排序无关；同一份数据同一次运行内稳定，但不可依赖。
- rehash 会使所有迭代器/引用失效。
- 要求 key 支持 `==` 和 `std::hash`。
- 不能插入重复值
- 取用就用，["apple"]
- ==🔴删除==，erase("apple")

## 代码示例

```cpp
std::unordered_map<std::string, int> um;
um["banana"] = 2;
um["apple"]  = 1;
um["cherry"] = 3 //um[].emplace_back({"cherry,30})
```

## 关联

- [[std-map]]（对比）
- [[哈希表]]
