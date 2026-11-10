# 第四梯队 · 工具链 —— 可运行练习

> **本机 cmake 注意**：系统默认 `cmake` 是 4.2.0-rc2（RC 版有崩溃 bug，exit 0xC0000409）。
> 请使用稳定版 `C:\Strawberry\c\bin\cmake.exe`（3.29.2），或把 PATH 里的 cmake 换成稳定版 3.x。

对应执行表第 14~15 项。两个练习：

- `cmake_demo/`：完整 CMake 项目（静态库 + 可执行 + 测试），**本地可直接构建验证**。
- `gtest_demo/`：GoogleTest 的 FetchContent 配置，首次配置需联网拉取 gtest。

---

## 第 14 项 · CMake（重点）

### 项目结构

```
cmake_demo/
├── CMakeLists.txt          # 顶层：项目 + 标准 + enable_testing + 三个子目录
├── src/
│   ├── CMakeLists.txt      # add_library(vec3 STATIC ...)
│   ├── vec3.h
│   └── vec3.cpp
├── app/
│   ├── CMakeLists.txt      # add_executable(demo ...) + 链接 vec3
│   └── main.cpp
└── tests/
    ├── CMakeLists.txt      # add_executable(test_vec3 ...) + add_test
    └── test_vec3.cpp       # 极简自写断言，无需外部框架
```

### 核心概念：target 即边界

CMake 的核心不是「一堆编译选项」，而是 **target（目标）**。每个 target 声明三件事：

1. 它是什么：`add_library(vec3 STATIC ...)` 或 `add_executable(demo ...)`
2. 它暴露什么：`target_include_directories(vec3 PUBLIC ...)`
3. 它依赖什么：`target_link_libraries(demo PRIVATE vec3)`

顶层 `CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.15)
project(TransFormCoreDemo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)
```

`src/CMakeLists.txt`（静态库 target）：

```cmake
add_library(vec3 STATIC
    vec3.cpp
)
target_include_directories(vec3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

`app/CMakeLists.txt`（可执行 target）：

```cmake
add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE vec3)
```

`tests/CMakeLists.txt`（测试 target）：

```cmake
add_executable(test_vec3 test_vec3.cpp)
target_link_libraries(test_vec3 PRIVATE vec3)
add_test(NAME vec3_tests COMMAND test_vec3)
```

### 构建运行

```bash
# 用稳定版 cmake（本机 4.2.0-rc2 会崩）
CM=/c/Strawberry/c/bin/cmake

"$CM" -B build -G Ninja        # 1 配置
"$CM" --build build             # 2 构建
./build/app/demo.exe            # 3 运行可执行
"$CM" --build build --target test   # 4 跑测试（或 ctest --test-dir build）
```

**真实输出**（已实测）：

```
=== 运行 demo ===
a+b = (3, 4, 0)
a dot b = 0
normalize(1,2,2) length = 1

=== ctest ===
1/1 Test #1: vec3_tests .......................   Passed    0.06 sec
100% tests passed, 0 tests failed out of 1
```

**验收点**：
- [ ] 能解释 target 的三要素（是什么 / 暴露什么 / 依赖什么）
- [ ] 能说出 `PUBLIC` 和 `PRIVATE` 的区别：`PUBLIC` 会传递给依赖者，`PRIVATE` 只本 target 用
- [ ] 能独立完成「配置 → 构建 → 运行 → ctest」四连
- [ ] 能把你的 `TransFormCore` 静态库套进这个结构（`add_library(TransFormCore STATIC ...)` + `PUBLIC` 头文件）

---

## 第 15 项 · GoogleTest（gtest）

### 配置（FetchContent 自动拉取）

`gtest_demo/CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.15)
project(GTestDemo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(test_calc test_calc.cpp)
target_link_libraries(test_calc PRIVATE gtest gtest_main)
add_test(NAME calc_tests COMMAND test_calc)
```

`test_calc.cpp`：

```cpp
#include <gtest/gtest.h>

int add(int a, int b) { return a + b; }

TEST(CalcTest, Add) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
    EXPECT_EQ(add(0, 0), 0);
}
```

### 构建运行

```bash
CM=/c/Strawberry/c/bin/cmake
cd gtest_demo
"$CM" -B build -G Ninja        # 首次配置会从 GitHub 克隆 gtest，需联网
"$CM" --build build
./build/test_calc.exe
```

> 注：首次配置要联网拉 googletest。国内网络若 GitHub 不通，可改用镜像：
> 把 `GIT_REPOSITORY` 换成 `https://gitee.com/mirrors/googletest.git`，或改用 vcpkg/conan 装 gtest。

**验收点**：
- [ ] 能写出 FetchContent 拉取第三方库的配置
- [ ] 能写 `TEST(套件名, 用例名)` 宏和 `EXPECT_EQ` 断言
- [ ] 能说明 `gtest_main` 的作用（自动生成 main 函数）
- [ ] 能给 `TransFormCore` 的坐标变换函数写 3~5 个单测并跑绿

---

四梯队全部通关后，回填 `C++补课执行表.md` 和 `C++路线图标注清单.md`。
