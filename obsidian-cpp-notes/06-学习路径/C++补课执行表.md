# C++ 补课执行表

> 来源：`C-Practice/C++补课执行表.md`。按依赖顺序执行，一项验收不过不进下一项。

## 资源缩写

- **MCT** = 《现代 C++ 教程》changkun/modern-cpp-tutorial，https://changkun.de/modern-cpp/
- **EMC++** = 《Effective Modern C++》Scott Meyers
- **Primer** = 《C++ Primer》第 5 版
- **cppref** = cppreference.com
- **Effective STL** = 《Effective STL》Scott Meyers

## 四梯队节点与验收标准

### 第一梯队 · 移动语义链（地基）

| # | 节点 | 资源·章节 | 验收标准 |
|---|---|---|---|
| 1 | 值类别 lvalue/rvalue/xvalue | MCT §3.3 | 判断任意表达式类别；说出「右值引用变量本身是左值」 |
| 2 | 移动语义 | MCT §3.3 + EMC++ Item 23 | 说明 `std::move` 本质是 `static_cast<T&&>`，本身不移动 |
| 3 | move/forward · 完美转发 | MCT §3.3 + EMC++ Item 24/25 | 写出正确的转发工厂；说清 `forward<T>` 为何带 T |
| 4 | noexcept | MCT §9.2 + EMC++ Item 14 | 解释移动构造为何标 noexcept（vector 的 move_if_noexcept） |

### 第二梯队 · 模板与类型系统

| # | 节点 | 资源·章节 | 验收标准 |
|---|---|---|---|
| 5 | 变参模板 + 折叠表达式 | MCT §2.5 | 手写 sizeof... 递归版 + 折叠版 |
| 6 | 全特化 / 偏特化 | Primer §16.5 | 各写一个；说明函数模板不能偏特化 |
| 7 | type-traits / SFINAE | Primer §16 + cppref | 用 enable_if 做编译期分支 |
| 8 | concepts (C++20) | MCT §10.1 | 把 SFINAE 改写为 requires 约束 |

### 第三梯队 · 工程惯用法

| # | 节点 | 资源·章节 | 验收标准 |
|---|---|---|---|
| 9 | pimpl（最优先） | EMC++ Item 22 + Qt Q_DECLARE_PRIVATE | 重构为 pimpl；看懂 Q_D/Q_Q 宏 |
| 10 | Rule of Three/Five/Zero | Primer §13 + cppref | 说明 Rule of Zero 适用条件 |
| 11 | copy-and-swap | Primer §13.3 + cppref | 手写异常安全的 operator= |
| 12 | non-copyable / erase-remove | cppref + Effective STL Item 32 | 用 =delete 实现 non-copyable |
| 13 | CRTP / copy-on-write | cppref | 用 CRTP 实现静态多态 |

### 第四梯队 · 工具链

| # | 节点 | 资源·章节 | 验收标准 |
|---|---|---|---|
| 14 | CMake | cpp_starter_project + CMake 官方教程 | 把 TransFormCore 建成 add_library target |
| 15 | gtest/gmock | GoogleTest 官方 Quickstart | 给坐标变换写 3~5 个单测跑绿 |

> `boost` 当前项目用不上，跳过。

## 关联

- [[C++学习路径总纲]]
