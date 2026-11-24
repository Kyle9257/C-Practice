# std::unordered_set

## 定义

无序、无重复元素的集合容器，底层是[[哈希表]]，平均 O(1) 查找。

## 要点

- 元素唯一，重复插入会被忽略。
- 点查均摊 O(1)，但最坏 O(n)。
- 遍历顺序按桶结构，与插入/排序无关，不可依赖。
- rehash 会使所有迭代器/引用失效。
- 要求元素支持 `==` 和 `std::hash`。

## 代码示例

```cpp
std::unordered_set<std::string> us;
us.insert("apple");
us.insert("banana");
us.insert("apple");   // 重复，被忽略

us.count("apple");    // 1（存在与否）
us.erase("apple");
```

## 关联

- [[std-set]]（对比）
- [[哈希表]]
- [[std-unordered-map]]
