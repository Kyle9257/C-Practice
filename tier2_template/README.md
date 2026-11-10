# 第二梯队 · 模板与类型系统 —— 可运行练习

> 已用 g++ 13.2.0（`-std=c++20 -Wall -Wextra`）实测通过，下方「输出」均为真实运行结果。
> 源码在 `exercises/` 目录。concepts 的两个练习需要 `-std=c++20`，其余 C++17 即可。
> 编译运行：`g++ -std=c++20 -Wall -Wextra -O2 -o out 文件名.cpp && ./out`

对应执行表第 5~8 项，按顺序敲。

---

## 第 5 项 · 变参模板 + 折叠表达式

### 练习 5.1 递归变参模板 + sizeof...

**源码** `exercises/ex5_1_variadic_recursion.cpp`：

```cpp
#include <iostream>

int sum() { return 0; }   // 递归基

template <typename T, typename... Rest>
int sum(T first, Rest... rest) {
    return first + sum(rest...);
}

template <typename... Args>
void show_count(Args... args) {
    std::cout << "参数个数: " << sizeof...(args) << "\n";
}

int main() {
    std::cout << "sum(1,2,3,4,5) = " << sum(1, 2, 3, 4, 5) << "\n";
    show_count(1, 2.0, 'a', "hello");
}
```

**输出**：

```
sum(1,2,3,4,5) = 15
参数个数: 4
```

**验收点**：
- [ ] 能写出递归变参模板的「递归基 + 递归步」两段结构
- [ ] 能解释 `sizeof...(args)` 是编译期常量

### 练习 5.2 折叠表达式（C++17）

**源码** `exercises/ex5_2_fold_expression.cpp`：

```cpp
#include <iostream>

template <typename... Args>
auto sum(Args... args) {
    return (args + ...);   // 一元右折叠
}

template <typename... Args>
void print_all(Args... args) {
    ((std::cout << args << " "), ...);   // 逗号折叠
}

int main() {
    std::cout << "sum(1,2,3,4,5) = " << sum(1, 2, 3, 4, 5) << "\n";
    print_all(1, 2.5, 'x', "str");
    std::cout << "\n";
}
```

**输出**：

```
sum(1,2,3,4,5) = 15
1 2.5 x str
```

**验收点**：
- [ ] 能说出 `(args + ...)` 与 `(... + args)` 的区别（右折叠 vs 左折叠）
- [ ] 能写出逗号折叠打印所有参数的写法

---

## 第 6 项 · 模板特化

### 练习 6.1 类模板全特化

**源码** `exercises/ex6_1_full_specialization.cpp`：

```cpp
#include <iostream>

template <typename T>
struct TypeName {
    static const char* get() { return "unknown"; }
};

template <>
struct TypeName<int> {
    static const char* get() { return "int"; }
};

template <>
struct TypeName<double> {
    static const char* get() { return "double"; }
};

int main() {
    std::cout << TypeName<float>::get() << "\n";
    std::cout << TypeName<int>::get() << "\n";
    std::cout << TypeName<double>::get() << "\n";
}
```

**输出**：

```
unknown
int
double
```

**验收点**：
- [ ] 能写出全特化的语法 `template <> struct X<具体类型> {...}`
- [ ] 能说明全特化后模板参数列表是空的

### 练习 6.2 类模板偏特化（无歧义示例）

**源码** `exercises/ex6_2_partial_specialization.cpp`：

```cpp
#include <iostream>

// 主模板
template <typename T>
struct Kind {
    static const char* name() { return "值类型"; }
};

// 偏特化：T 是左值引用
template <typename T>
struct Kind<T&> {
    static const char* name() { return "左值引用"; }
};

// 偏特化：T 是指针
template <typename T>
struct Kind<T*> {
    static const char* name() { return "指针"; }
};

int main() {
    std::cout << Kind<int>::name() << "\n";    // 值类型
    std::cout << Kind<int&>::name() << "\n";   // 左值引用
    std::cout << Kind<int*>::name() << "\n";   // 指针
}
```

**输出**：

```
值类型
左值引用
指针
```

**验收点**：
- [ ] 能写出偏特化语法 `template <typename T> struct X<T&> {...}`（保留部分参数）
- [ ] 能说明「函数模板不能偏特化，只能用重载」的原因
- [ ] 理解一个坑：多个偏特化若同时匹配会造成**歧义**（编译报 ambiguous），所以偏特化要设计成互不重叠

---

## 第 7 项 · type-traits / SFINAE

### 练习 7.1 type traits + if constexpr 编译期分派

**源码** `exercises/ex7_1_type_traits.cpp`：

```cpp
#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
void describe(T) {
    if constexpr (std::is_integral_v<T>)
        std::cout << "整型\n";
    else if constexpr (std::is_floating_point_v<T>)
        std::cout << "浮点型\n";
    else if constexpr (std::is_pointer_v<T>)
        std::cout << "指针\n";
    else
        std::cout << "其他\n";
}

int main() {
    describe(42);
    describe(3.14);
    int x = 0;
    describe(&x);
    describe(std::string("s"));
}
```

**输出**：

```
整型
浮点型
指针
其他
```

**验收点**：
- [ ] 能说出 `if constexpr` 是编译期丢弃未命中分支（不是运行时 if）
- [ ] 能列出 3 个常用 traits：`is_integral_v` / `is_floating_point_v` / `is_pointer_v`

### 练习 7.2 SFINAE：enable_if 约束重载

**源码** `exercises/ex7_2_sfinae.cpp`：

```cpp
#include <iostream>
#include <type_traits>

template <typename T>
std::enable_if_t<std::is_integral_v<T>, void>
print_kind(T) {
    std::cout << "整型重载\n";
}

template <typename T>
std::enable_if_t<std::is_floating_point_v<T>, void>
print_kind(T) {
    std::cout << "浮点重载\n";
}

int main() {
    print_kind(42);
    print_kind(3.14);
    // print_kind("x");  // 取消注释：两个重载都不匹配，编译错误
}
```

**输出**：

```
整型重载
浮点重载
```

**验收点**：
- [ ] 能解释「替换失败不是错误（SFINAE）」：不匹配的重载被静默移除，而不是报错
- [ ] 能说清 `std::enable_if_t<条件, 返回类型>` 两个模板参数的含义

---

## 第 8 项 · concepts (C++20)

### 练习 8.1 定义一个 concept

**源码** `exercises/ex8_1_concept.cpp`：

```cpp
#include <concepts>
#include <cstddef>
#include <iostream>
#include <string>

template <typename T>
concept HasSize = requires(T t) {
    t.size();
    { t.size() } -> std::convertible_to<std::size_t>;
};

template <HasSize T>
void show_size(const T& v) {
    std::cout << "size = " << v.size() << "\n";
}

int main() {
    show_size(std::string("hello"));
    // show_size(42);  // 取消注释：int 不满足 HasSize，编译错误
}
```

**输出**：

```
size = 5
```

**验收点**：
- [ ] 能写出 `concept` 的定义语法和 `requires` 表达式
- [ ] 能解释 `{ t.size() } -> std::convertible_to<std::size_t>` 在约束返回值类型

### 练习 8.2 concepts vs SFINAE（重写 7.2）

**源码** `exercises/ex8_2_concept_vs_sfinae.cpp`：

```cpp
#include <concepts>
#include <iostream>

template <std::integral T>
void print_kind(T) {
    std::cout << "整型（concept 约束）\n";
}

template <std::floating_point T>
void print_kind(T) {
    std::cout << "浮点（concept 约束）\n";
}

int main() {
    print_kind(42);
    print_kind(3.14);
    // print_kind("x");  // 报错信息比 SFINAE 可读得多
}
```

**输出**：

```
整型（concept 约束）
浮点（concept 约束）
```

**验收点**：
- [ ] 能说明 concepts 相对 SFINAE 的两大优势：约束声明位置直观、编译报错清晰
- [ ] 能认出 `<concepts>` 里现成的 `std::integral`、`std::floating_point` 等标准 concept

---

通关后进入第三梯队（工程惯用法 Idiom）。
