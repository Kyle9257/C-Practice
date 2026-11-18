# C++ 学习路径（来自 C-Practice 项目）

> 来源：`D:/Git2/C-Practice`，基于 `salmer/CppDeveloperRoadmap` 的 Middle→Senior 缺口整理的四梯队练习。
> 原项目用 g++ 13.2.0 实测通过，CMake 用 3.29.2 验证。

## 学习顺序

**梯队 0 → 1 → 2 → 3 → 4**，梯队内按练习编号顺序。

| 梯队 | 主题 | 笔记 | 练习数 |
|---|---|---|---|
| 0 | STL 应用 | [[tier0-STL应用]] | 8 |
| 1 | 移动语义链 | [[tier1-移动语义]] | 11 |
| 2 | 模板与类型系统 | [[tier2-模板]] | 8 |
| 3 | 工程惯用法 Idiom | [[tier3-惯用法]] | 7 |
| 4 | 工具链 | [[tier4-工具链]] | 2 项目 |

## 学习流程

读 README 敲练习 → 对照输出 → 勾验收清单 → 全勾完进下一梯队。

## 编译命令速查

```bash
# 单文件练习（梯队 1~3）
g++ -std=c++17 -Wall -Wextra -O2 -o out 文件名.cpp && ./out

# STL / concepts 需要 C++20
g++ -std=c++20 -Wall -Wextra -O2 -o out 文件名.cpp && ./out

# CMake（本机默认 cmake 4.2.0-rc2 会崩，用稳定版）
CM=/c/Strawberry/c/bin/cmake
"$CM" -B build -G Ninja && "$CM" --build build && ctest --test-dir build
```

## 通关判断标准

> 能脱离 IDE 补全、一次性写对，并能给别人讲清原理，才算「会」。

## 关联

- [[std-map]] · [[红黑树]] · [[移动语义]] · [[完美转发]] · [[SFINAE]] · [[pimpl]]
