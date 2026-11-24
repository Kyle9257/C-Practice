---
tags: [术语卡片]
---

# CRTP

## 定义

Curiously Recurring Template Pattern：基类模板的参数是派生类自身，实现编译期静态多态。

## 要点

- 结构：`struct Derived : Base<Derived>`，基类里 `static_cast<T*>(this)` 静态分发到派生类实现。
- 相对虚函数的取舍：无虚函数表（vtable）开销、可内联，但类型在编译期固定，不能放进同质容器做运行期多态。
- 典型用途：`std::enable_shared_from_this`、Eigen 的表达式模板、基类注入公共接口。

## 代码示例

```cpp
template <typename T>
struct Base {
    void interface() { static_cast<T*>(this)->implementation(); }
};

struct DerivedA : Base<DerivedA> {
    void implementation() { std::cout << "A\n"; }
};
```

## 关联

- [[模板特化]] · [[静态多态]]
- 学习路径：[[tier3-惯用法]]
