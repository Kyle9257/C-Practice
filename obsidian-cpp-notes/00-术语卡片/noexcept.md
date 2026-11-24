---
tags: [术语卡片]
---

# noexcept

## 定义

C++ 的异常规格声明，告诉编译器某函数不会抛出异常，可用作说明符或运算符。

## 要点

- 两个 `noexcept` 要区分：
  - **说明符**：`void f() noexcept { ... }`，修饰函数声明。
  - **运算符**：`noexcept(expr)`，编译期求值，返回 bool。
- C++17 起 `noexcept` 是函数类型的一部分，`void(*)()` 与 `void(*)() noexcept` 是不同类型。
- 移动构造应标 `noexcept`：`std::vector` 扩容时用 `move_if_noexcept` 判断，移动构造会抛异常则退化为拷贝，保强异常安全。
- 条件形式：`noexcept(bool 常量表达式)`，常配合 `std::is_nothrow_move_constructible_v` 等 type-traits。

## 代码示例

```cpp
void f() noexcept { /* 不抛异常 */ }

std::cout << std::boolalpha;
std::cout << noexcept(f()) << "\n";   // true（运算符）

template <typename T>
void my_swap(T& a, T& b)
    noexcept(std::is_nothrow_move_constructible_v<T> &&
             std::is_nothrow_move_assignable_v<T>);
```

## 关联

- [[移动语义]] · [[type-traits]] · [[Rule of Five]]
- 学习路径：[[tier1-移动语义]]
