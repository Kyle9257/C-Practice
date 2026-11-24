---
tags: [术语卡片]
---

# concept

## 定义

C++20 的编译期约束，用 `requires` 表达式声明模板参数必须满足的条件，替代 SFINAE 的约束写法。

## 要点

- 定义语法：`template <typename T> concept HasSize = requires(T t) { t.size(); };`
- 约束返回值：`{ t.size() } -> std::convertible_to<std::size_t>`。
- 使用方式：`template <HasSize T> void f(const T&)`，或 `requires` 子句内联约束。
- 相比 SFINAE 两大优势：约束声明位置直观、编译报错信息清晰可读。
- `<concepts>` 提供现成标准 concept：`std::integral`、`std::floating_point`、`std::convertible_to` 等。

## 代码示例

```cpp
template <typename T>
concept HasSize = requires(T t) {
    t.size();
    { t.size() } -> std::convertible_to<std::size_t>;
};

template <HasSize T>
void show_size(const T& v) { std::cout << v.size() << "\n"; }
```

## 关联

- [[SFINAE]] · [[type-traits]] · [[模板特化]]
- 学习路径：[[tier2-模板]]
