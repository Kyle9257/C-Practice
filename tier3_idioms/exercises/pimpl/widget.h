#pragma once
#include <memory>

// Pimpl：头文件只暴露接口 + 前向声明，隐藏实现细节
class Widget {
public:
    explicit Widget(int value);
    ~Widget();                    // 析构必须在 .cpp 定义（Impl 在 .cpp 才是完整类型）
    Widget(const Widget&);        // 拷贝
    Widget(Widget&&) noexcept;    // 移动
    Widget& operator=(const Widget&);
    Widget& operator=(Widget&&) noexcept;

    int value() const;
    void set_value(int v);

private:
    struct Impl;                  // 只前向声明，不暴露任何成员
    std::unique_ptr<Impl> pImpl;
};
