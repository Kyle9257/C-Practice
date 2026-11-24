/*
学习目标：
1. 区分 public、protected、private 成员在派生类中的可见性。
2. 理解 public/protected/private 继承改变的是“基类接口如何继续对外暴露”。
3. 认识 public 继承表达 is-a（“是一种”）关系。

练习方法：
1. 取消 main 中标记为错误的代码，观察编译器诊断。
2. 把 Manager 的 public 继承改为 protected 或 private，观察 Employee& 转换是否仍可在外部进行。
3. 给 Employee 增加只读工号，并让 Manager 输出它。
*/
#include <iostream>
#include <string>
#include <utility>

class Employee {
public:
    Employee(std::string name, int salary)
        : name_(std::move(name)), salary_(salary) {}

    const std::string& name() const { return name_; }
    void print_public_info() const {
        std::cout << "姓名: " << name_ << '\n';
    }

protected:
    // 派生类可以访问，类外代码不能访问。
    int salary() const { return salary_; }

private:
    // 派生类也不能直接访问，只能通过 Employee 提供的接口使用。
    std::string name_;
    int salary_;
};

class Manager : public Employee {
public:
    Manager(std::string name, int salary, int team_size)
        : Employee(std::move(name), salary), team_size_(team_size) {}

    void print_report() const {
        std::cout << name() << " 管理 " << team_size_
                  << " 人，薪资 " << salary() << '\n';
        // std::cout << name_; // 错误：name_ 是 Employee 的 private 成员。
    }

private:
    int team_size_;
};

void print_employee(const Employee& employee) {
    employee.print_public_info();
}

int main() {
    Manager manager("林青", 18000, 6);
    manager.print_report();

    // public 继承保留 is-a 关系：Manager 可以被当作 Employee 使用。
    print_employee(manager);

    // std::cout << manager.salary(); // 错误：protected 成员不能从类外访问。
}
