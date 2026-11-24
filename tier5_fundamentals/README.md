# 梯队 5 · C++ 基础补全练习

这套练习补齐 `缺口整理清单.md` 中原先没有配套代码的 13 个主题。每个源文件都包含一个 `main`，可以独立编译运行。

## 使用方式

```powershell
./build_all.ps1
./build/ex01_lambda.exe
```

单独编译：

```powershell
g++ -std=c++23 -Wall -Wextra -Wpedantic -O2 -pthread -static exercises/ex01_lambda.cpp -o ex01.exe
```

Windows 脚本使用 `-static`，避免运行练习时依赖 MinGW DLL 搜索路径。Linux/macOS 通常可以去掉该参数。

`std::expected`、`std::format` 和 `std::print` 不只取决于语言标准，也取决于标准库实现。当前 g++ 13.2 缺少其中部分实现，相关练习会编译兼容分支并输出提示；换用实现完整的 C++23 工具链后会自动启用标准组件。

## 练习索引

| 编号 | 文件 | 核心内容 |
|---|---|---|
| 01 | `ex01_lambda.cpp` | 捕获列表、按值捕获、按引用捕获、泛型算法 |
| 02 | `ex02_weak_ptr.cpp` | 非拥有观察、`expired`/`lock`、打破循环引用的基础 |
| 03 | `ex03_multiple_inheritance.cpp` | 多接口继承、虚析构、基类视图 |
| 04 | `ex04_diamond_inheritance.cpp` | 菱形继承、虚继承、最派生类初始化虚基类 |
| 05 | `ex05_optional_expected.cpp` | “无值”与“成功或错误”两种返回模型 |
| 06 | `ex06_dynamic_cast.cpp` | 多态层次中的安全向下转型 |
| 07 | `ex07_reinterpret_cast.cpp` | 对象表示、字节视图、为什么恢复数据应使用 `memcpy` |
| 08 | `ex08_format_print.cpp` | `format`/`print` 与旧工具链兼容方式 |
| 09 | `ex09_string_view_span.cpp` | 只读字符串视图、连续内存视图及生命周期责任 |
| 10 | `ex10_multithreading.cpp` | `thread`、`join`、互斥量、原子计数器 |
| 11 | `ex11_cpp20.cpp` | ranges、三路比较、`numbers`、constexpr lambda |
| 12 | `ex12_adl.cpp` | 参数依赖查找与 `using std::swap; swap(a, b)` 惯用法 |
| 13 | `ex13_constexpr_consteval.cpp` | 可选编译期求值与强制编译期求值 |
| 14 | `ex14_inheritance_access.cpp` | 继承访问控制、`public` 继承与 is-a 关系 |
| 15 | `ex15_construction_destruction.cpp` | 基类/成员/派生类的构造析构顺序、虚析构 |
| 16 | `ex16_virtual_override_hiding.cpp` | 运行时多态、`override`、重载隐藏与 `using` |
| 17 | `ex17_abstract_polymorphism.cpp` | 抽象类、纯虚函数、异构对象统一管理 |
| 18 | `ex18_slicing_and_composition.cpp` | 对象切片、引用多态、继承与组合的选择 |

## 独立专题

- [`multithreading/`](multithreading/)：从线程创建与销毁，到协作停止、同步、消息队列、`future` 和线程池的 9 个渐进练习。

## 学习要求

先预测输出，再编译运行，然后修改输入验证边界。不要只记语法：每个练习都应能解释“什么时候该用”和“错误使用会产生什么风险”。完成后逐项检查 `验收清单.md`。
