# 第一梯队 · 移动语义链 —— 可运行练习

> 已用 g++ 13.2.0（`-std=c++17 -Wall -Wextra`）实测通过，下方「输出」均为真实运行结果。
> 源码在 `exercises/` 目录，每个练习是一个独立 `.cpp`，可直接编译。
> 编译运行：`g++ -std=c++17 -Wall -Wextra -O2 -o out 文件名.cpp && ./out`

对应执行表第 1~4 项，每项拆成 2~3 个练习，按顺序敲。验收点必须全部达成才进入下一项。

---

## 第 1 项 · 值类别（lvalue / rvalue / xvalue）

### 练习 1.1 用 decltype 判断值类别

**目标**：掌握判断值类别的工具——`decltype` + `<type_traits>`，并理解 decltype 的「加括号」特例。

**源码** `exercises/ex1_1_value_category.cpp`：

```cpp
#include <iostream>
#include <type_traits>
#include <utility>

int main() {
    int x = 0;

    // (x) 加括号后按「表达式」处理，x 是左值 → int&
    static_assert(std::is_lvalue_reference_v<decltype((x))>, "(x) 应是左值");

    // 未加括号的 x 走特例，返回声明类型 int（非引用）
    static_assert(!std::is_reference_v<decltype(x)>, "x 不加括号返回声明类型 int");

    // 42 是纯右值 → int（非引用）
    static_assert(!std::is_reference_v<decltype(42)>, "42 是纯右值");

    // std::move(x) 是 xvalue → int&&
    static_assert(std::is_rvalue_reference_v<decltype(std::move(x))>, "std::move(x) 是 xvalue");

    std::cout << "1.1 全部断言通过\n";
}
```

**输出**：

```
1.1 全部断言通过
```

**验收点**：
- [ ] 能说出 decltype 的 4 条规则（未加括号变量名 / xvalue / lvalue / prvalue 各返回什么）
- [ ] 能解释为什么必须写 `(x)` 而不是 `x`

### 练习 1.2 右值引用变量本身是左值

**目标**：击破最大的反直觉点——「有名字的东西是左值」，右值引用变量也不例外。

**源码** `exercises/ex1_2_rvalue_ref_is_lvalue.cpp`：

```cpp
#include <iostream>
#include <utility>

void f(int&)  { std::cout << "  匹配 int&  （左值）\n"; }
void f(int&&) { std::cout << "  匹配 int&& （右值）\n"; }

int main() {
    int x = 0;

    std::cout << "f(x):\n";            f(x);
    std::cout << "f(5):\n";            f(5);
    std::cout << "f(std::move(x)):\n"; f(std::move(x));

    std::cout << "--- 关键反直觉点 ---\n";
    int&& r = 5;          // r 是右值引用，但 r 本身有名字
    std::cout << "f(r):\n";            f(r);
    std::cout << "f(std::move(r)):\n"; f(std::move(r));
}
```

**输出**：

```
f(x):
  匹配 int&  （左值）
f(5):
  匹配 int&& （右值）
f(std::move(x)):
  匹配 int&& （右值）
--- 关键反直觉点 ---
f(r):
  匹配 int&  （左值）     ← 重点：r 是右值引用，却匹配左值重载
f(std::move(r)):
  匹配 int&& （右值）
```

**验收点**：
- [ ] 能解释为什么 `f(r)` 匹配 `int&` 而不是 `int&&`
- [ ] 能说出「把 r 重新变回右值」的唯一正确手段是 `std::move(r)`

### 练习 1.3 xvalue 的三个来源

**目标**：记住 xvalue 由哪三类表达式产生，并再踩一次 decltype「加括号」特例（成员访问也要加括号）。

**源码** `exercises/ex1_3_xvalue_sources.cpp`：

```cpp
#include <iostream>
#include <type_traits>
#include <utility>

int&& foo() { static int x = 0; return std::move(x); }

struct S { int m; };

int main() {
    int a = 0;

    // 1. std::move(x)
    static_assert(std::is_rvalue_reference_v<decltype(std::move(a))>);

    // 2. 返回 T&& 的函数调用
    static_assert(std::is_rvalue_reference_v<decltype(foo())>);

    // 3. 访问右值对象的成员 S{}.m 是 xvalue
    //    注意：decltype 对「未加括号的成员访问」也有特例，返回成员声明类型 int；
    //    所以要加括号 (S{}.m) 才能拿到值类别 int&&
    static_assert(std::is_rvalue_reference_v<decltype((S{}.m))>);

    std::cout << "1.3 全部断言通过：xvalue 的三类来源已确认\n";
}
```

**输出**：

```
1.3 全部断言通过：xvalue 的三类来源已确认
```

**验收点**：
- [ ] 能背出 xvalue 的三类来源：`std::move(x)`、返回 `T&&` 的函数调用、右值对象的成员访问
- [ ] 能解释为什么 `decltype(S{}.m)` 是 `int`，而 `decltype((S{}.m))` 才是 `int&&`

---

## 第 2 项 · 移动语义

### 练习 2.1 移动 vs 拷贝（观察 vector 里何时触发哪个）

**目标**：直观看到「临时对象→move、左值→copy、std::move(左值)→move」。

**源码** `exercises/ex2_1_move_vs_copy.cpp`：

```cpp
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Widget {
    std::string data;
    Widget(const std::string& s) : data(s) {}

    Widget(const Widget& o) : data(o.data) { std::cout << "  copy ctor\n"; }
    Widget(Widget&& o) noexcept : data(std::move(o.data)) { std::cout << "  move ctor\n"; }
};

int main() {
    std::vector<Widget> v;
    v.reserve(4);

    std::cout << "push 临时对象（右值）:\n";
    v.push_back(Widget("hello"));

    std::cout << "push 左值:\n";
    Widget w("world");
    v.push_back(w);

    std::cout << "push std::move(左值):\n";
    v.push_back(std::move(w));
}
```

**输出**：

```
push 临时对象（右值）:
  move ctor
push 左值:
  copy ctor
push std::move(左值):
  move ctor
```

**验收点**：
- [ ] 能说明三种 push_back 分别为什么触发 move / copy
- [ ] 能指出 `reserve(4)` 的作用（避免扩容干扰，聚焦拷贝/移动本身的触发）

### 练习 2.2 std::move 不移动任何东西

**目标**：把「移动 = std::move」这个误解彻底掰正——std::move 只是 cast，真正移动的是「移动构造函数被调用」。

**源码** `exercises/ex2_2_move_is_cast.cpp`：

```cpp
#include <iostream>
#include <string>
#include <utility>

// std::move 的实现本质：
// template<class T> remove_reference_t<T>&& move(T&& t) {
//     return static_cast<remove_reference_t<T>&&>(t);
// }

int main() {
    // 证明 1：std::move 单独出现，什么都不发生
    std::string c = "xyz";
    (void)std::move(c);                 // 这一行没有效果
    std::cout << "单独 std::move(c) 后 c = \"" << c << "\"\n"; // 仍是 "xyz"

    // 证明 2：真正移动的是「移动构造函数被调用」
    std::string src = "old value";
    std::string dst = std::move(src);   // 这里调用移动构造，src 被搬空
    std::cout << "移动构造后 src = \"" << src << "\"\n";
    std::cout << "移动构造后 dst = \"" << dst << "\"\n";

    // 证明 3：移动后的对象「合法但未指定」，可继续赋值
    src = "reassigned";
    std::cout << "移动后重新赋值 src = \"" << src << "\"\n";
}
```

**输出**：

```
单独 std::move(c) 后 c = "xyz"
移动构造后 src = ""
移动构造后 dst = "old value"
移动后重新赋值 src = "reassigned"
```

**验收点**：
- [ ] 能默写 std::move 的实现（就一行 `static_cast<remove_reference_t<T>&&>`）
- [ ] 能说出「移动后对象状态」的准确描述是「合法但未指定（valid but unspecified）」

---

## 第 3 项 · std::move / std::forward · 完美转发

### 练习 3.1 写一个完美转发工厂

**目标**：手写 `make_unique` 式工厂，理解 `Args&&...` + `std::forward<Args>(args)...` 这个固定组合。

**源码** `exercises/ex3_1_perfect_forward.cpp`：

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct MyClass {
    int a;
    std::string b;
    MyClass(int a_, std::string b_) : a(a_), b(std::move(b_)) {}
};

template <typename T, typename... Args>
std::unique_ptr<T> make(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {
    std::string s = "world";

    auto p1 = make<MyClass>(42, "hello");   // 转发右值
    auto p2 = make<MyClass>(7, s);          // 转发左值，s 不会被搬空

    std::cout << "p1: " << p1->a << ", " << p1->b << "\n";
    std::cout << "p2: " << p2->a << ", " << p2->b << "\n";
    std::cout << "左值 s 仍为: \"" << s << "\"\n";
}
```

**输出**：

```
p1: 42, hello
p2: 7, world
左值 s 仍为: "world"
```

**验收点**：
- [ ] 能解释 `Args&&` 为什么是万能引用，以及 `std::forward<Args>(args)...` 的展开形式
- [ ] 能说明转发左值 `s` 时为什么 `s` 不会被搬空（这证明转发「保留了值类别」）

### 练习 3.2 std::forward 为什么必须带模板参数

**目标**：对比 `std::move`（无条件转右值）和 `std::forward`（条件转，取决于 T），看错误版本把左值破坏掉。

**源码** `exercises/ex3_2_forward_needs_T.cpp`：

```cpp
#include <iostream>
#include <utility>

void g(int&)  { std::cout << "  g(int&)\n"; }
void g(int&&) { std::cout << "  g(int&&)\n"; }

// 正确：用 std::forward<T> 保留原始值类别
template <typename T>
void relay(T&& t) {
    g(std::forward<T>(t));
}

// 错误示范：用 std::move 会把左值也强制变右值
template <typename T>
void relay_wrong(T&& t) {
    g(std::move(t));
}

int main() {
    int x = 0;

    std::cout << "relay(x)   [左值]:\n";  relay(x);
    std::cout << "relay(5)   [右值]:\n";  relay(5);

    std::cout << "--- 用 move 的错误版本 ---\n";
    std::cout << "relay_wrong(x) [左值被破坏]:\n"; relay_wrong(x);
    std::cout << "relay_wrong(5) [右值]:\n";       relay_wrong(5);
}
```

**输出**：

```
relay(x)   [左值]:
  g(int&)
relay(5)   [右值]:
  g(int&&)
--- 用 move 的错误版本 ---
relay_wrong(x) [左值被破坏]:
  g(int&&)        ← 左值 x 被 move 成了右值，重载选错
relay_wrong(5) [右值]:
  g(int&&)
```

**验收点**：
- [ ] 能说出 `std::forward<T>(t)` 的语义：`T` 是 `int&` 时转成 `int&`，`T` 是 `int` 时转成 `int&&`（引用折叠 + static_cast 的魔法）
- [ ] 能解释为什么 `std::forward` 必须显式给 `T`，而 `std::move` 不需要

### 练习 3.3 万能引用的前提（显式指定 T 会失效）

**目标**：明确「万能引用」成立的条件——T 必须由实参**推导**出来，手动指定就退化成普通右值引用。

**源码** `exercises/ex3_3_universal_ref.cpp`：

```cpp
#include <iostream>
#include <type_traits>

template <typename T>
void f(T&&) {
    if constexpr (std::is_lvalue_reference_v<T>)
        std::cout << "  T 推导为左值引用，T&& 折叠成 T&\n";
    else
        std::cout << "  T 推导为值类型，T&& 是右值引用\n";
}

int main() {
    int x = 0;

    std::cout << "f(x):\n"; f(x);
    std::cout << "f(5):\n"; f(5);

    std::cout << "--- 显式指定 T，万能引用失效 ---\n";
    // f<int>(x);  // 取消注释会编译错误：T 被指定为 int，T&& 就是 int&&，不能绑左值 x
    std::cout << "f<int>(5):\n"; f<int>(5);

    std::cout << "结论：万能引用的前提是「T 由实参推导」。\n";
}
```

**输出**：

```
f(x):
  T 推导为左值引用，T&& 折叠成 T&
f(5):
  T 推导为值类型，T&& 是右值引用
--- 显式指定 T，万能引用失效 ---
f<int>(5):
  T 推导为值类型，T&& 是右值引用
结论：万能引用的前提是「T 由实参推导」。
```

**验收点**：
- [ ] 能背出万能引用的判定口诀：「`T&&` + T 被推导 = 万能引用；其余（`const T&&`、`vector<T>&&`、显式指定 T）都不是」
- [ ] 亲自取消注释 `f<int>(x)`，看编译报错，理解报错原因

---

## 第 4 项 · noexcept

### 练习 4.1 noexcept 是函数类型的一部分（C++17）

**目标**：理解 C++17 起 noexcept 进入类型系统，`void() noexcept` 与 `void()` 是不同类型。

**源码** `exercises/ex4_1_noexcept_signature.cpp`：

```cpp
#include <iostream>

void f1() noexcept { std::cout << "f1 (noexcept)\n"; }
void f2() { std::cout << "f2 (可能抛异常)\n"; }

int main() {
    void (*p1)() noexcept = f1;   // OK：类型匹配
    void (*p2)()          = f2;   // OK：类型匹配

    // 赋值只能"丢弃承诺"，不能"增加承诺"：
    // void (*p3)()          = f1;   // OK：noexcept 可隐式转成普通函数指针（C++17 允许）
    // void (*p4)() noexcept = f2;   // 错误：非 noexcept 函数不能赋给 noexcept 指针

    std::cout << std::boolalpha;
    std::cout << "noexcept(f1()) = " << noexcept(f1()) << "\n"; // true
    std::cout << "noexcept(f2()) = " << noexcept(f2()) << "\n"; // false

    p1();
    p2();
}
```

**输出**：

```
noexcept(f1()) = true
noexcept(f2()) = false
f1 (noexcept)
f2 (可能抛异常)
```

**验收点**：
- [ ] 能区分两个 `noexcept`：说明符（`noexcept` 修饰函数声明）和运算符（`noexcept(expr)` 编译期求值）
- [ ] 能说出 C++17 之前和之后，`void(*)()` 与 `void(*)() noexcept` 的关系变化

### 练习 4.2 移动构造标不标 noexcept，决定 vector 扩容走 move 还是 copy

**目标**：这是 noexcept 在工程上最关键的意义——`std::vector` 的强异常安全保证。

**源码** `exercises/ex4_2_noexcept_vector.cpp`：

```cpp
#include <iostream>
#include <vector>

struct Safe {
    Safe() { std::cout << "  Safe()\n"; }
    Safe(const Safe&) { std::cout << "  Safe(copy)\n"; }
    Safe(Safe&&) noexcept { std::cout << "  Safe(move)\n"; }   // 移动构造标了 noexcept
};

struct Unsafe {
    Unsafe() { std::cout << "  Unsafe()\n"; }
    Unsafe(const Unsafe&) { std::cout << "  Unsafe(copy)\n"; }
    Unsafe(Unsafe&&) { std::cout << "  Unsafe(move)\n"; }       // 移动构造没标 noexcept
};

int main() {
    std::cout << "== vector<Safe> 扩容：搬旧元素应走 move ==\n";
    std::vector<Safe> a;
    a.push_back(Safe());
    a.push_back(Safe());
    a.push_back(Safe());   // 触发扩容

    std::cout << "\n== vector<Unsafe> 扩容：搬旧元素应走 copy ==\n";
    std::vector<Unsafe> b;
    b.push_back(Unsafe());
    b.push_back(Unsafe());
    b.push_back(Unsafe()); // 触发扩容
}
```

**输出**：

```
== vector<Safe> 扩容：搬旧元素应走 move ==
  Safe()
  Safe(move)
  Safe()
  Safe(move)
  Safe(move)
  Safe()
  Safe(move)
  Safe(move)
  Safe(move)

== vector<Unsafe> 扩容：搬旧元素应走 copy ==
  Unsafe()
  Unsafe(move)
  Unsafe()
  Unsafe(move)
  Unsafe(copy)     ← 关键：扩容搬旧元素用了 copy 而非 move
  Unsafe()
  Unsafe(move)
  Unsafe(copy)
  Unsafe(copy)
```

**验收点**：
- [ ] 能指出 Safe 与 Unsafe 输出的差异点：扩容「搬旧元素」时 Safe 走 move、Unsafe 走 copy
- [ ] 能解释原因：vector 扩容要保持「强异常安全」，若移动构造可能抛异常，就必须用拷贝（拷贝抛异常不影响原数据）
- [ ] 能说明为什么 push_back 临时对象那一下两者都用 move（那是 push_back 的 `T&&` 重载，与 noexcept 无关）

### 练习 4.3 条件 noexcept + noexcept 运算符

**目标**：掌握 `noexcept(条件)` 的写法，以及 `std::is_nothrow_*` 与 noexcept 的配合（这是标准库 `std::swap` 的做法）。

**源码** `exercises/ex4_3_conditional_noexcept.cpp`：

```cpp
#include <iostream>
#include <type_traits>
#include <utility>

template <typename T>
void my_swap(T& a, T& b)
    noexcept(std::is_nothrow_move_constructible_v<T> &&
             std::is_nothrow_move_assignable_v<T>) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

struct NoThrow {};
struct Throw { Throw(Throw&&) {} };  // 移动构造没标 noexcept

int main() {
    std::cout << std::boolalpha;
    std::cout << "my_swap<NoThrow> noexcept = "
              << noexcept(my_swap(std::declval<NoThrow&>(), std::declval<NoThrow&>()))
              << "\n";   // true

    std::cout << "my_swap<Throw> noexcept = "
              << noexcept(my_swap(std::declval<Throw&>(), std::declval<Throw&>()))
              << "\n";   // false
}
```

**输出**：

```
my_swap<NoThrow> noexcept = true
my_swap<Throw> noexcept = false
```

**验收点**：
- [ ] 能写出条件 noexcept 的语法：`noexcept(bool 常量表达式)`
- [ ] 能解释 `std::declval<T&>()` 的作用（在不求值上下文中「假装」制造一个 T 的引用）
- [ ] 能说出这 4 项全部打通后，移动语义链的完整图景：值类别 → move/forward → 转发引用 → noexcept

---

## 通关检查

第一梯队 4 项做完后，回填执行表，逐项勾掉。判断标准只有一条：

> **能脱离 IDE 补全、一次性写对，并能给别人讲清原理，才算「会」。**

全部通过后，进入第二梯队（模板特化 / type-traits / SFINAE / concepts）。
