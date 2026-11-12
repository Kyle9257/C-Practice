#include "WidgetPractice.h"
#include <iostream>


//1、定义impl(头文件里只有前向声明，这里不全定义，头文件里看不到任何私有成员)
class widgetPractice::Impl {
    public:
    int counter = 0;
    std::string name = "name";
};

widgetPractice::widgetPractice(int counter, std::string name) : pImpl(std::make_unique<Impl>()) {
    pImpl->counter = counter;
    pImpl->name = name;
    std::cout << "  widgetPractice 构造\n";
}

//1·构造函数，这里需要初始化pimpl，使用make_unique创建Impl对象
widgetPractice::widgetPractice() : pImpl(std::make_unique<Impl>()) {
    
    std::cout << "  widgetPractice 构造\n";
}

//2.析构函数，必须在Impl完整定义之后才能default
widgetPractice::~widgetPractice() = default;

//3.拷贝构造函数，使用make_unique创建Impl对象，并拷贝wp.pImpl的内容
widgetPractice::widgetPractice(const widgetPractice& wp)
:pImpl(std::make_unique<Impl>(*wp.pImpl)) 
{
    std::cout << "  widgetPractice 拷贝构造\n";
}

//4.移动构造函数，使用默认实现
widgetPractice::widgetPractice(widgetPractice&&) noexcept = default;

//5.拷贝赋值运算符，拷贝wp.pImpl的内容
widgetPractice& widgetPractice::operator=(const widgetPractice& wp){
    if(this != &wp){
        *pImpl = *wp.pImpl;
    };
    std::cout << "widgetPractice 拷贝赋值\n";
    return *this;
}

//6、移动赋值构造函数，使用默认实现
widgetPractice& widgetPractice::operator=(widgetPractice&&) noexcept = default;

int widgetPractice::getCounter() const {
    return pImpl->counter;
}

std::string widgetPractice::getName() const {
    return pImpl->name;
}   