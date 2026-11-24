---
tags: [术语卡片]
---

# copy-and-swap

## 定义

用「按值传参 + swap」实现赋值运算符的惯用法，一条 `operator=` 同时覆盖拷贝赋值和移动赋值，并保证强异常安全。

## 要点

- 核心：`Vec& operator=(Vec other)`，实参处按值传参，编译器自动选拷贝或移动构造出 `other`，再 swap。
- 传左值 → `other` 是副本（拷贝）；传右值 → `other` 被移动构造（移动）。
- swap 不抛异常，赋值操作要么完全成功要么保持原状，实现强异常安全。
- 注意：手写了 `operator=` 会抑制隐式拷贝/移动构造，需显式 `= default` 补回，否则触发 `-Wdeprecated-copy`。

## 代码示例

```cpp
class Vec {
    std::vector<int> data_;
public:
    Vec(const Vec&) = default;   // 显式保留
    Vec(Vec&&) = default;

    Vec& operator=(Vec other) {  // 按值传参
        data_.swap(other.data_);
        return *this;
    }
};
```

## 关联

- [[Rule of Five]] · [[移动语义]]
- 学习路径：[[tier3-惯用法]]
