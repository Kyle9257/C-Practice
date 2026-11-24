/*
学习目标：
1. 理解多重继承可以让一个类同时实现多个独立接口。
2. 掌握纯虚函数、override 和虚析构的配合。
3. 学会从不同基类接口观察同一个派生对象。

练习方法：
1. 分别通过 Printable& 和 Resettable& 调用 Counter 的功能。
2. 尝试删除 Counter::reset 的实现，阅读编译器对抽象类的报错。
3. 给接口增加一个纯虚函数，并在 Counter 中完成实现。

知识点：
- 多重继承更适合组合职责单一的接口，不适合随意复用带状态的实现类。
- 通过基类指针删除派生对象时，基类析构函数必须是 virtual。
- override 让编译器检查函数是否真正覆盖了基类虚函数。
- 同一个 Counter 对象可以隐式转换为两个不同的基类视图。
*/
#include <iostream>


struct Connect
{
    virtual ~Connect() = default;
    virtual void connectDevice() = 0;
};


struct Printable {
    // 接口类通常提供虚析构，保证通过基类指针销毁派生对象是安全的。
    virtual ~Printable() = default;
    virtual void print() const = 0;
};

struct Resettable {
    virtual ~Resettable() = default;
    virtual void reset() = 0;
};

class Counter final : public Printable, public Resettable,public Connect {
public:
    explicit Counter(int value) : value_(value) {}

    void print() const override { std::cout << "counter = " << value_ << '\n'; }
    void reset() override { value_ = 0; }
    void connectDevice() override { std::cout << "connect device" << "\n";}

private:
    int value_;
};

int main() {
    Counter counter(42);
    // 两个引用指向同一个对象，但只暴露各自接口声明的操作。
    Printable& printable = counter;
    Resettable& resettable = counter;
    Connect &connectAble = counter;
    printable.print();
    resettable.reset();
    printable.print();
    connectAble.connectDevice();
}
