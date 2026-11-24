/*
学习目标：
1. 理解 shared_ptr 表示共享所有权，weak_ptr 只负责观察对象。
2. 掌握 weak_ptr::lock 的安全访问方式。
3. 理解 weak_ptr 不延长对象生命周期，常用于打破 shared_ptr 循环引用。

练习方法：
1. 观察 owner 离开作用域前后 show_user 的不同输出。
2. 在 owner 存活时再创建一个 shared_ptr 副本，观察 use_count 的变化。
3. 尝试调用 observer.expired()，比较它和 lock() 的用途。

知识点：
- shared_ptr 的强引用计数降为 0 时，对象被销毁。
- weak_ptr 不增加强引用计数，所以不能直接使用 operator->。
- lock() 会尝试取得一个 shared_ptr；对象已销毁时得到空 shared_ptr。
- 不要先调用 expired() 再假设对象仍存在，多线程下应直接以 lock() 的结果为准。
*/
#include <iostream>
#include <memory>
#include <string>

struct User {
    explicit User(std::string name_value) : name(std::move(name_value)) {}
    std::string name;
};

void show_user(const std::weak_ptr<User> &observer) {
    // lock 同时完成“检查对象是否存在”和“临时延长生命周期”。
    if (const auto user = observer.lock()) {
        std::cout << "用户仍存在: " << user->name << '\n';
        
        
    } else {
        std::cout << "用户已经释放\n";
    }
}

int main() {
    std::weak_ptr<User> observer;
    {
        const auto owner = std::make_shared<User>("Alice");
        // 赋值给 weak_ptr 不会增加 owner 的强引用计数。
        observer = owner;
        std::cout << "所有者数量: " << owner.use_count() << '\n';
       // auto owner1 = std::make_shared<User>("Bob");
        auto owner1 = owner;
        std::cout <<" 所有者数量2：" << owner.use_count() << "\n";

        show_user(observer);
    }
    //出作用域之后，owner释放，observer也同时被释放
    show_user(observer);
}
