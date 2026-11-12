#include <iostream>

// C++17 折叠表达式：一元右折叠
template <typename... Args>
int sum(Args... args){
    return(args + ... + 0); // 右折叠，0是初始值
}

// 逗号折叠：依次打印每个参数
template <typename... Args>
void print_all(Args... args) {
    // ((std::cout << args << " "), ...);      //放在整个打印后面，表示依次打印
    ((std::cout << args <<" "), ...);
}

int main() {
    std::cout << "sum(1,2,3,4,5) = " << sum(1, 2, 3, 4, 5) << "\n";
    print_all("hello", "你好", "这是", "模板折叠表达式");
    std::cout << "\n";
}
