/*
学习目标：
1. 掌握派生对象的构造顺序：基类 -> 成员 -> 派生类构造函数体。
2. 掌握析构顺序与构造顺序相反。
3. 理解多态基类为什么通常必须拥有 virtual 析构函数。

练习方法：
1. 先预测全部输出，再运行验证。
2. 在 Server 中再增加一个 Trace 成员，观察成员按“声明顺序”而非初始化列表顺序构造。
3. 去掉 Service 析构函数的 virtual，开启警告并解释风险。
*/
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Trace {
public:
    explicit Trace(std::string label) : label_(std::move(label)) {
        std::cout << "构造 " << label_ << '\n';
    }

    ~Trace() { std::cout << "析构 " << label_ << '\n'; }

private:
    std::string label_;
};

class Service {
public:
    Service() : base_trace_("Service 的成员") {
        std::cout << "进入 Service 构造函数体\n";
    }

    virtual ~Service() {
        std::cout << "进入 Service 析构函数体\n";
    }

    virtual void run() const = 0;

private:
    Trace base_trace_;
};

class Server final : public Service {
public:
    Server() : server_trace_("Server 的成员") {
        std::cout << "进入 Server 构造函数体\n";
    }

    ~Server() override {
        std::cout << "进入 Server 析构函数体\n";
    }

    void run() const override { std::cout << "Server 正在运行\n"; }

private:
    Trace server_trace_;
};

int main() {
    // 基类指针拥有派生对象；virtual 析构保证 delete 时完整析构 Server。
    std::unique_ptr<Service> service = std::make_unique<Server>();
    service->run();
    std::cout << "即将离开 main\n";
}
