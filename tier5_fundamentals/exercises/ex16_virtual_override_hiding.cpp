/*
学习目标：
1. 理解虚函数通过基类引用/指针实现运行时多态。
2. 区分 override（覆盖）与同名函数隐藏。
3. 使用 override 让编译器检查函数签名，使用 final 阻止继续覆盖。

练习方法：
1. 把 Dog::speak 后的 const 删除，观察 override 如何发现签名不匹配。
2. 注释 using Animal::feed，观察 dog.feed(2) 为什么无法通过编译。
3. 尝试从 Dog 继续派生并覆盖 speak，观察 final 的诊断。
*/
#include <iostream>
#include <string_view>

class Animal {
public:
    virtual ~Animal() = default;

    virtual void speak() const {
        std::cout << "Animal 发出声音\n";
    }

    void feed(int portions) const {
        std::cout << "喂食 " << portions << " 份\n";
    }
};

class Dog final : public Animal {
public:
    void speak() const override {
        std::cout << "Dog: 汪\n";
    }

    // 派生类声明同名函数后，会隐藏基类中的所有同名重载。
    // using 将 Animal::feed(int) 重新引入 Dog 的重载集合。
    using Animal::feed;

    void feed(std::string_view food) const {
        std::cout << "喂 Dog 吃 " << food << '\n';
    }
};

void make_sound(const Animal& animal) {
    animal.speak(); // 根据对象的实际类型选择最终覆盖函数。
}

int main() {
    Animal animal;
    Dog dog;

    make_sound(animal);
    make_sound(dog);

    dog.feed(2);
    dog.feed("牛肉");
}
