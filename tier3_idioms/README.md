# 第三梯队 · 工程惯用法 Idiom —— 可运行练习

> 已用 g++ 13.2.0（`-std=c++17 -Wall -Wextra`）实测通过，下方「输出」均为真实运行结果。
> 源码在 `exercises/` 目录。pimpl 是多文件示例（`pimpl/` 子目录），其余单文件。
> 编译：单文件 `g++ -std=c++17 -Wall -Wextra -O2 -o out 文件名.cpp && ./out`；pimpl 见下文。

对应执行表第 9~13 项。

---

## 第 9 项 · pimpl（最优先，多文件示例）

**目标**：把实现细节藏进 `.cpp`，头文件只留接口 + 前向声明，减少编译依赖。这是 Qt `Q_DECLARE_PRIVATE` 的原型。

**目录** `exercises/pimpl/`，三个文件：

`widget.h`：

```cpp
#pragma once
#include <memory>

class Widget {
public:
    explicit Widget(int value);
    ~Widget();                    // 析构必须在 .cpp 定义
    Widget(const Widget&);
    Widget(Widget&&) noexcept;
    Widget& operator=(const Widget&);
    Widget& operator=(Widget&&) noexcept;

    int value() const;
    void set_value(int v);

private:
    struct Impl;                  // 只前向声明，不暴露成员
    std::unique_ptr<Impl> pImpl;
};
```

`widget.cpp`：

```cpp
#include "widget.h"
#include <iostream>

struct Widget::Impl {
    int value;
    explicit Impl(int v) : value(v) { std::cout << "  Impl 构造\n"; }
};

Widget::Widget(int value) : pImpl(std::make_unique<Impl>(value)) {}
Widget::~Widget() = default;   // 必须在 Impl 完整定义之后

Widget::Widget(const Widget& o) : pImpl(std::make_unique<Impl>(o.pImpl->value)) {
    std::cout << "  copy ctor\n";
}
Widget::Widget(Widget&&) noexcept = default;

Widget& Widget::operator=(const Widget& o) {
    if (this != &o) pImpl->value = o.pImpl->value;
    std::cout << "  copy assign\n";
    return *this;
}
Widget& Widget::operator=(Widget&&) noexcept = default;

int Widget::value() const { return pImpl->value; }
void Widget::set_value(int v) { pImpl->value = v; }
```

`main.cpp`：

```cpp
#include "widget.h"
#include <iostream>

int main() {
    Widget w(10);
    std::cout << "w.value = " << w.value() << "\n";
    w.set_value(20);

    Widget w2 = w;
    std::cout << "w2.value = " << w2.value() << "\n";

    Widget w3 = std::move(w);
    std::cout << "w3.value = " << w3.value() << "\n";
}
```

**编译运行**：

```bash
g++ -std=c++17 -Wall -Wextra -O2 -o pimpl pimpl/widget.cpp pimpl/main.cpp && ./pimpl
```

**输出**：

```
  Impl 构造
w.value = 10
  Impl 构造
  copy ctor
w2.value = 20
w3.value = 20
```

**验收点**：
- [ ] 能说出 pimpl 的两个好处：① 头文件不暴露私有成员 ② 改实现不触发大量重编译
- [ ] 能解释为什么析构函数必须移到 `.cpp` 里定义（`unique_ptr<Impl>` 需要完整类型）
- [ ] 能看懂 Qt 里 `Q_DECLARE_PRIVATE` / `Q_D` 宏就是这套结构

---

## 第 10 项 · Rule of Three / Five / Zero

**源码** `exercises/ex10_1_rule_of_five.cpp`（管理裸资源必须写全五个）：

```cpp
#include <iostream>
#include <cstring>

class Buffer {
    char* data_;
    std::size_t size_;

public:
    explicit Buffer(std::size_t n) : data_(new char[n]), size_(n) {}
    ~Buffer() { delete[] data_; }                            // 1 析构

    Buffer(const Buffer& o)                                  // 2 拷贝构造
        : data_(new char[o.size_]), size_(o.size_) {
        std::memcpy(data_, o.data_, size_);
        std::cout << "copy ctor\n";
    }

    Buffer(Buffer&& o) noexcept : data_(o.data_), size_(o.size_) {  // 3 移动构造
        o.data_ = nullptr;
        o.size_ = 0;
        std::cout << "move ctor\n";
    }

    Buffer& operator=(const Buffer& o) {                     // 4 拷贝赋值
        if (this != &o) {
            delete[] data_;
            data_ = new char[o.size_];
            size_ = o.size_;
            std::memcpy(data_, o.data_, size_);
        }
        std::cout << "copy assign\n";
        return *this;
    }

    Buffer& operator=(Buffer&& o) noexcept {                 // 5 移动赋值
        if (this != &o) {
            delete[] data_;
            data_ = o.data_;
            size_ = o.size_;
            o.data_ = nullptr;
            o.size_ = 0;
        }
        std::cout << "move assign\n";
        return *this;
    }

    std::size_t size() const { return size_; }
};

int main() {
    Buffer a(10);
    Buffer b = a;              // copy ctor
    Buffer c = std::move(a);   // move ctor
    c = b;                     // copy assign
    c = std::move(b);          // move assign
}
```

**输出**：

```
copy ctor
move ctor
copy assign
move assign
```

**验收点**：
- [ ] 能背出 Rule of Five 是哪五个成员函数
- [ ] 能说明 Rule of Zero：成员全是值语义（string/vector/智能指针）时，五个都不用写
- [ ] 能说出「Rule of Three」是 C++11 之前的旧版本（只有拷贝构造/赋值/析构）

---

## 第 11 项 · copy-and-swap

**源码** `exercises/ex11_1_copy_and_swap.cpp`：

```cpp
#include <iostream>
#include <utility>
#include <vector>

class Vec {
    std::vector<int> data_;

public:
    explicit Vec(std::vector<int> d) : data_(std::move(d)) {}

    Vec(const Vec&) = default;   // copy-and-swap 需要显式保留拷贝构造
    Vec(Vec&&) = default;        // 以及移动构造

    Vec& operator=(Vec other) {  // 按值传参：实参处已发生拷贝或移动
        data_.swap(other.data_);
        std::cout << "copy-and-swap assign\n";
        return *this;
    }

    void show() const {
        for (int x : data_) std::cout << x << " ";
        std::cout << "\n";
    }
};

int main() {
    Vec a(std::vector<int>{1, 2, 3});
    Vec b(std::vector<int>{4, 5});

    b = a;                 // 拷贝：other 是 a 的副本
    b.show();

    b = Vec({9, 9});       // 移动：other 是临时对象
    b.show();
}
```

**输出**：

```
copy-and-swap assign
1 2 3
copy-and-swap assign
9 9
```

**验收点**：
- [ ] 能说清 copy-and-swap 的核心：`operator=` 按值传参，让编译器自动选择拷贝/移动，再 swap
- [ ] 能说明它如何保证**强异常安全**（swap 不抛异常）
- [ ] 能说出注意点：写了 `operator=` 要显式 `= default` 拷贝/移动构造（否则触发 `-Wdeprecated-copy`）

---

## 第 12 项 · non-copyable / erase-remove

### 12.1 non-copyable（= delete）

**源码** `exercises/ex12_1_noncopyable.cpp`：

```cpp
#include <iostream>
#include <utility>

class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;

    NonCopyable(NonCopyable&&) = default;
    NonCopyable& operator=(NonCopyable&&) = default;
};

int main() {
    NonCopyable a;
    NonCopyable b = std::move(a);   // 移动 OK
    (void)b;
    // NonCopyable c = a;           // 拷贝被删除，编译错误
    std::cout << "non-copyable 但可移动\n";
}
```

**输出**：

```
non-copyable 但可移动
```

**验收点**：
- [ ] 能用 `= delete` 禁拷贝、`= default` 留移动
- [ ] 能说出哪些资源类应该 non-copyable（如线程、锁、套接字句柄）

### 12.2 erase-remove

**源码** `exercises/ex12_2_erase_remove.cpp`：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 3, 2, 4, 2, 5};

    std::cout << "原始: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    // 只写 remove 不写 erase 是经典错误：remove 只前移元素，不缩小容器
    v.erase(std::remove(v.begin(), v.end(), 2), v.end());

    std::cout << "删除所有 2 后: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
}
```

**输出**：

```
原始: 1 2 3 2 4 2 5
删除所有 2 后: 1 3 4 5
```

**验收点**：
- [ ] 能说出为什么「只有 remove 没有 erase」是错的（容器 size 不变，末尾留脏数据）
- [ ] C++20 起可用 `std::erase(v, 2)` 一行替代（`<vector>` 已提供）

---

## 第 13 项 · CRTP / copy-on-write

### 13.1 CRTP（静态多态）

**源码** `exercises/ex13_1_crtp.cpp`：

```cpp
#include <iostream>

template <typename T>
struct Base {
    void interface() {
        static_cast<T*>(this)->implementation();
    }
};

struct DerivedA : Base<DerivedA> {
    void implementation() { std::cout << "DerivedA 实现\n"; }
};

struct DerivedB : Base<DerivedB> {
    void implementation() { std::cout << "DerivedB 实现\n"; }
};

template <typename T>
void use(Base<T>& b) {
    b.interface();
}

int main() {
    DerivedA a;
    DerivedB b;
    use(a);
    use(b);
}
```

**输出**：

```
DerivedA 实现
DerivedB 实现
```

**验收点**：
- [ ] 能解释 CRTP 的核心：基类模板参数是派生类自身，`static_cast<T*>(this)` 做静态分发
- [ ] 能说出它相对虚函数的取舍：无虚函数表开销，但**类型在编译期固定**，不能放进同质容器多态

### 13.2 copy-on-write（原理，不写代码）

**概念**：多个对象共享同一份底层数据，只有某个对象要「写」时才真正拷贝一份。C++ 里经典实现用 `shared_ptr` + 写时复制检测（`std::string` 早期实现、`QString` 都曾用过）。

**验收点**：
- [ ] 能一句话说清 copy-on-write 的「读共享、写才复制」
- [ ] 知道它和多线程的冲突：写时检测需要原子/加锁，现代实现常因线程安全开销而放弃

---

通关后进入第四梯队（工具链）。
