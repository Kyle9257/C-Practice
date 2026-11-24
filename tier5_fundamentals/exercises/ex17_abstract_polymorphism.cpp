/*
学习目标：
1. 用纯虚函数定义抽象接口，理解抽象类不能直接实例化。
2. 用 unique_ptr<Base> 统一管理不同派生类型。
3. 认识“面向接口编程”：调用方只依赖 Shape 的契约。

练习方法：
1. 新增 Rectangle，并实现 area() 与 name()。
2. 删除任意一个 override，观察该派生类为何仍是抽象类。
3. 为 Shape 增加 perimeter() 纯虚函数，并补齐所有实现。
*/
#include <cmath>
#include <iostream>
#include <memory>
#include <numbers>
#include <string_view>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual std::string_view name() const = 0;
};

class Circle final : public Shape {
public:
    explicit Circle(double radius) : radius_(radius) {}

    double area() const override {
        return std::numbers::pi * radius_ * radius_;
    }

    std::string_view name() const override { return "圆"; }

private:
    double radius_;
};

class Triangle final : public Shape {
public:
    Triangle(double base, double height) : base_(base), height_(height) {}

    double area() const override { return base_ * height_ / 2.0; }
    std::string_view name() const override { return "三角形"; }

private:
    double base_;
    double height_;
};

void print_shape(const Shape& shape) {
    std::cout << shape.name() << "面积: " << shape.area() << '\n';
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0));

    for (const auto& shape : shapes) {
        print_shape(*shape);
    }
}
