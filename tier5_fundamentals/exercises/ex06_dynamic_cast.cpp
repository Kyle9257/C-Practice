/*
学习目标：
1. 理解 dynamic_cast 用于多态继承体系中的运行期类型检查。
2. 掌握指针形式转换失败返回 nullptr 的处理方式。
3. 明确向下转型应是例外手段，优先考虑虚函数接口。

练习方法：
1. 分别把 Cat 和 Dog 传给 try_meow，观察成功和失败分支。
2. 去掉 Animal 中的虚析构，阅读 dynamic_cast 对非多态类型的编译错误。
3. 尝试引用形式 dynamic_cast<const Cat&>，了解失败时的 bad_cast 异常。

知识点：
- 含有至少一个虚函数的类是多态类型，编译器会保留运行期类型信息。
- dynamic_cast<T*>(p) 失败返回 nullptr；dynamic_cast<T&>(r) 失败抛 std::bad_cast。
- 从派生类向基类的向上转换通常不需要 dynamic_cast，可直接隐式转换。
- 如果代码频繁判断实际派生类型，通常说明基类接口设计还可以改进。
*/
#include <iostream>

struct Animal {
    // 虚析构既让基类成为多态类型，也保证通过基类指针安全析构。
    virtual ~Animal() = default;
    std::string type_;
};

struct Cat final : Animal {
    Cat(std::string type) { type_ = type ; }
    void meow() const { std::cout << "Cat::meow\n"; }
};

struct Dog final : Animal {
    Dog(std::string type){ type_ = type; }
    void bark()const { std::cout << "Dot::bark\n"; }
};

void try_meow(Animal& animal) {
    // 转成指针形式便于用空指针表达“类型不匹配”。
    if (const auto* cat = dynamic_cast<const Cat*>(&animal)) {
        cat->meow();
    } else if (const auto* dog = dynamic_cast<const Dog*>(&animal)) {

        dog->bark();
    }
}

int main() {
    Cat cat("cat");
    Dog dog("dog");
    try_meow(cat);
    try_meow(dog);
}
