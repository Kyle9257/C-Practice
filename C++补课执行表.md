# C++ 补课执行表

> 按依赖顺序执行，**一项验收不过，不进下一项**。标「会」后把该项勾掉。
> 资源缩写：
> - **MCT** = 《现代 C++ 教程》(changkun/modern-cpp-tutorial)，在线阅读 https://changkun.de/modern-cpp/
> - **EMC++** = 《Effective Modern C++》(Scott Meyers)
> - **Primer** = 《C++ Primer》第 5 版 (中文版)
> - **cppref** = cppreference.com
> - **Effective STL** = 《Effective STL》(Scott Meyers)

## 第一梯队 · 移动语义链（地基，不补后面全白搭）

| # | 节点 | 资源 · 章节 | 验收标准（达标才算会） |
|---|---|---|---|
| 1 | 值类别 lvalue / rvalue / xvalue | MCT §3.3 | 能判断任意表达式属于哪个类别；能说出「右值引用变量本身是左值」这一反直觉结论 |
| 2 | 移动语义 | MCT §3.3 + EMC++ Item 23 | 能说明 `std::move` 本质是 `static_cast<T&&>`，它本身不移动任何东西 |
| 3 | std::move / std::forward · 完美转发 | MCT §3.3 + EMC++ Item 24/25 | 能写出一个正确的转发工厂函数；说清 `std::forward<T>(u)` 为何必须带模板参数 T |
| 4 | noexcept | MCT §9.2 + EMC++ Item 14 | 能解释移动构造/赋值为何要标 `noexcept`（`vector` 重分配时 `move_if_noexcept` 的取舍） |

## 第二梯队 · 模板与类型系统（高级能力入口）

| # | 节点 | 资源 · 章节 | 验收标准 |
|---|---|---|---|
| 5 | 变参模板 + 折叠表达式 | MCT §2.5 | 手写一个 `sizeof...` 递归版本 + 一个折叠表达式版本，都能编译 |
| 6 | 模板全特化 / 偏特化 | Primer §16.5 | 各写一个全特化与偏特化；说明为什么函数模板不能偏特化（用重载替代） |
| 7 | type-traits / SFINAE | Primer §16 + cppref「SFINAE」 | 用 `std::enable_if` 做一次编译期分支；讲清「替换失败不是错误」的含义 |
| 8 | concepts (C++20) | MCT §10.1 | 把上面一段 SFINAE 改写成 `requires` 约束；写出一个「约束有 `.size()` 成员」的 concept |

## 第三梯队 · 工程惯用法 Idiom（直接改善现有代码）

| # | 节点 | 资源 · 章节 | 验收标准 |
|---|---|---|---|
| 9 | pimpl（**最优先**） | EMC++ Item 22 + Qt 头文件 `Q_DECLARE_PRIVATE` | 把一个多依赖头文件重构为 pimpl，编译时间下降；能看懂 `Q_D` / `Q_Q` 宏展开 |
| 10 | Rule of Three / Five / Zero | Primer §13 + cppref「Rule of three/five/zero」 | 能说明 Rule of Zero 的适用条件，以及什么时候必须退回到 Rule of Five |
| 11 | copy-and-swap | Primer §13.3 + cppref「Copy-and-swap」 | 手写一个异常安全的 `operator=`（copy-and-swap 版） |
| 12 | non-copyable / erase-remove | cppref + Effective STL Item 32 | 用 `= delete` 实现 non-copyable；写对 `remove_if` + `erase` 惯用法 |
| 13 | CRTP / copy-on-write | cppref「Curiously recurring template pattern」 | 用 CRTP 实现一个静态多态示例；copy-on-write 说出原理即可 |

## 第四梯队 · 工具链

| # | 节点 | 资源 · 章节 | 验收标准 |
|---|---|---|---|
| 14 | CMake | lefticus/cpp_starter_project + CMake 官方教程 | 把 `TransFormCore` 建成一个 `add_library` target 并跑通 build |
| 15 | gtest/gmock | GoogleTest 官方 Quickstart | 给坐标变换模块写 3~5 个单测并全部跑绿 |

> `boost` 当前项目用不上，**跳过**，不必硬学。
