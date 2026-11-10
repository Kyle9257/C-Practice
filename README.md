# C++ 学习练习目录

> 基于 `salmer/CppDeveloperRoadmap` 的 Middle→Senior 缺口，按四梯队组织的**可运行练习**。
> 所有代码均已用 g++ 13.2.0 实测通过（`-Wall -Wextra` 零警告），CMake 项目已用 cmake 3.29.2 构建验证。

## 目录结构

```
C++Practice/
├── tier0_stl/                 # 容器、算法、迭代器失效、现代 STL（8 练习）
│   ├── README.md
│   ├── 验收清单.md
│   └── exercises/
├── tier1_move/                # 值类别、移动语义、完美转发、noexcept（11 练习）
│   ├── README.md              # 练习说明 + 代码 + 输出 + 验收点
│   ├── 验收清单.md            # checkbox，逐项打勾
│   └── exercises/             # 11 个独立 .cpp
├── tier2_template/            # 变参模板、特化、SFINAE、concepts（8 练习）
│   ├── README.md
│   ├── 验收清单.md
│   └── exercises/
├── tier3_idioms/              # pimpl、Rule of Five、copy-and-swap、CRTP（7 练习）
│   ├── README.md
│   ├── 验收清单.md
│   └── exercises/
├── tier4_toolchain/           # CMake、gtest（2 项目）
│   ├── README.md
│   ├── 验收清单.md
│   └── exercises/
├── C++补课执行表.md           # 总纲（15 项 → 四梯队）
├── C++路线图标注清单.md        # 缺口标注（Middle 103 + Senior 46）
└── CppDeveloperRoadmap-zh.drawio.svg
```

## 学习顺序

**梯队 0 → 1 → 2 → 3 → 4**，每个梯队内按练习编号（ex01 → ex02 → …）顺序。

每个梯队的流程：读 `README.md` 敲练习 → 对照输出 → 勾 `验收清单.md` → 全勾完进下一梯队。

## 编译命令速查

```bash
# 单个练习（梯队 1~3）
g++ -std=c++17 -Wall -Wextra -O2 -o out 文件名.cpp && ./out

# STL 练习（梯队0，span 需要 C++20）
g++ -std=c++20 -Wall -Wextra -O2 -o out 文件名.cpp && ./out

# concepts 练习需要 C++20
g++ -std=c++20 -Wall -Wextra -O2 -o out ex8_1_concept.cpp && ./out

# pimpl 多文件
g++ -std=c++17 -Wall -Wextra -O2 -o pimpl pimpl/widget.cpp pimpl/main.cpp && ./pimpl

# CMake（注意：本机默认 cmake 4.2.0-rc2 会崩，请用稳定版）
CM=/c/Strawberry/c/bin/cmake
"$CM" -B build -G Ninja && "$CM" --build build && ctest --test-dir build
```
