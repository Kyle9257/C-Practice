/*
学习目标：
1. 理解派生对象按值赋给基类对象时会发生对象切片。
2. 知道多态参数应使用基类引用或指针，而不是基类值。
3. 区分 is-a（继承）与 has-a（组合）关系。

练习方法：
1. 比较 print_by_value 与 print_by_reference 的输出。
2. 尝试创建 vector<Notification> 保存 EmailNotification，解释信息丢失的原因。
3. 给 SmsNotification 增加 PhoneSender 成员，继续使用组合实现发送细节。
*/
#include <iostream>
#include <string>
#include <utility>

class Notification {
public:
    virtual ~Notification() = default;
    virtual void send() const {
        std::cout << "发送普通通知\n";
    }
};

class EmailSender {
public:
    void send_to(const std::string& address, const std::string& text) const {
        std::cout << "邮件 -> " << address << ": " << text << '\n';
    }
};

class EmailNotification final : public Notification {
public:
    EmailNotification(std::string address, std::string text)
        : address_(std::move(address)), text_(std::move(text)) {}

    void send() const override {
        sender_.send_to(address_, text_);
    }

private:
    // EmailNotification 是一种 Notification，但它“拥有一个”EmailSender。
    EmailSender sender_;
    std::string address_;
    std::string text_;
};

void print_by_value(Notification notification) {
    notification.send();
}

void print_by_reference(const Notification& notification) {
    notification.send();
}

int main() {
    EmailNotification email("student@example.com", "继承练习已更新");

    std::cout << "按值传递（发生切片）: ";
    print_by_value(email);

    std::cout << "按引用传递（保留多态）: ";
    print_by_reference(email);
}
