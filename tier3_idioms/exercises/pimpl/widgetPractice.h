#pragma once
#include <memory>
#include <string>

class widgetPractice {

    private:
    class Impl;                     //前向申明，头文件中看不出任何私有成员
    std::unique_ptr<Impl> pImpl;

public:
    explicit widgetPractice(int counter, std::string name = "name");

    widgetPractice();       //构造函数                                      1
    ~widgetPractice();      //析构函数必须在Impl完整定义之后才能default       2
    widgetPractice(const widgetPractice&);                  //拷贝          3
    widgetPractice(widgetPractice&&) noexcept;              //移动          4

    widgetPractice& operator=(const widgetPractice&);       //拷贝赋值      5
    widgetPractice& operator=(widgetPractice&&) noexcept;   //移动赋值      6

    void doSomething();

    int getCounter() const;
    std::string getName() const;
};