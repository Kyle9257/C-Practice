/*
学习目标：
1. 认识菱形继承中重复基类子对象的问题。
2. 理解 virtual 继承如何让两条路径共享同一个基类子对象。
3. 掌握“最派生类负责初始化虚基类”的规则。

练习方法：
1. 运行程序，确认两条继承路径最终指向同一个 Device。
2. 去掉 Scanner 和 Printer 继承列表中的 virtual，观察 device.id 的二义性报错。
3. 保留虚继承，修改 MultiFunctionDevice 传给 Device 的 id。

知识点：
- 普通菱形继承会包含两份 Device，访问 Device 成员时会产生二义性。
- virtual Device 表示共享虚基类，最终对象中只保留一份 Device。
- 虚基类由最派生类 MultiFunctionDevice 直接初始化，中间类的初始化只在其单独构造时生效。
- 虚继承会增加对象布局和访问复杂度，应只在确实需要共享基类状态时使用。
*/
#include <iostream>
#include <string>

struct Device {
    explicit Device(std::string id_value) : id(std::move(id_value)) {}
    std::string id;
};

// virtual 写在继承关系上，表示 Device 是共享的虚基类。
struct Scanner : virtual Device {
    Scanner() : Device("scanner") {
        
    }
};

struct Printer : virtual Device {
    Printer() : Device("printer") {

    }
};

struct MultiFunctionDevice : Scanner, Printer {
    // 最派生类负责初始化唯一的 Device 虚基类子对象。
    MultiFunctionDevice() : Device("MFD-002") {}
};

int main() {
    MultiFunctionDevice device;
    std::cout << "共享的 Device 子对象 id: " << device.id << '\n';
    std::cout << std::boolalpha
              << "两条继承路径指向同一基类: "
              << (static_cast<Device*>(static_cast<Scanner*>(&device)) ==
                  static_cast<Device*>(static_cast<Printer*>(&device)))
              << '\n';
}
