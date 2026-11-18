# lower_bound 与 upper_bound

## 定义

有序容器上的二分查找，返回迭代器：
- `lower_bound(k)`：第一个 `key >= k`。
- `upper_bound(k)`：第一个 `key > k`。

## 要点

- 仅适用于有序容器（[[std-map]]、有序数组）；[[std-unordered-map]] 无此成员。
- 两者配合取区间：`[lower_bound(a), upper_bound(b))` = 键在 `[a, b]` 内，左闭右开。
- key 不存在时两者返回同一位置；仅当 key 存在才有差别。

## 代码示例

```cpp
std::map<std::string,int> m{{"apple",1},{"banana",2},{"cherry",3}};
m.lower_bound("b");  // -> banana（第一个 >= b）
m.upper_bound("b");  // -> cherry（第一个 > b）
```

## 关联

- [[std-map]]
- [[二分查找]]
