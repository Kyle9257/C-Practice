---
tags: [术语卡片]
---

# type-traits

## 定义

`<type_traits>` 里的一批编译期类型查询/变换工具，用于在编译期判断或修改类型属性。

## 要点

- 查询类（`is_*`）：`std::is_integral_v<T>`、`std::is_floating_point_v<T>`、`std::is_pointer_v<T>` 等，返回 bool 常量。
- 变换类：`std::remove_reference_t<T>`、`std::decay_t<T>`、`std::enable_if_t<...>` 等，返回新类型。
- 常与 `if constexpr` 搭配做编译期分派，或与 `std::enable_if` 搭配做 SFINAE 约束。
- 底层靠模板特化实现：为每种类型模式写一个偏特化，如 `is_pointer<T*>` 返回 true。

## 代码示例

```cpp
template <typename T>
void describe(T) {
    if constexpr (std::is_integral_v<T>)
        std::cout << "整型\n";
    else if constexpr (std::is_floating_point_v<T>)
        std::cout << "浮点\n";
    else
        std::cout << "其他\n";
}
```

## 关联

- [[SFINAE]] · [[concept]] · [[模板特化]] · [[noexcept]]
- 学习路径：[[tier2-模板]]
