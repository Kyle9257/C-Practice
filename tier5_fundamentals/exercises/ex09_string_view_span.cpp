/*
学习目标：
1. 理解 string_view 是字符序列的非拥有只读视图。
2. 理解 span 是连续对象序列的非拥有视图。
3. 学会用视图统一接收 string、数组、vector 等不同所有者的数据。

练习方法：
1. 给 file_extension 传入有扩展名和无扩展名的路径。
2. 用 C 风格数组调用 double_values，验证 span 的统一接口。
3. 尝试从临时 string 保存 string_view，并分析临时对象销毁后的风险。

知识点：
- 视图不分配、不复制，也不负责释放底层数据。
- string_view 通常只读；span<int> 可修改它所观察的整数。
- 底层容器扩容、销毁或字符串离开作用域后，已有视图可能悬空。
- string_view 不保证以 '\0' 结尾，不能无条件把 data() 当 C 字符串使用。
- span 只能表示连续内存，不能直接接收 list。
*/
#include <array>
#include <iostream>
#include <span>
#include <string>
#include <string_view>
#include <vector>
// std::string_view::substr(pos,count),0拷贝切片


std::string_view file_extension(std::string_view path) {
    // substr 返回的新 string_view 仍然指向原始字符串，不发生字符复制。
    const auto dot = path.rfind('.');
    //npos是否为空的判断
    return dot == std::string_view::npos ? std::string_view{} : path.substr(dot + 1);
}

void double_values(std::span<int> values) {
    // span 保存地址和长度；修改元素就是修改底层容器中的元素。
    for (int& value : values) {
        value *= 2;
    }
}

int main() {
    const std::string path = "notes/readme.md";
    std::cout << "扩展名: " << file_extension(path) << '\n';

    auto dot = path.rfind(".");
    auto sss = path.substr(dot + 1) ;
    std::cout << "扩展名："  << sss << "\n";

    std::vector<int> vector{1, 2, 3};
    std::array<int, 3> array{4, 5, 6};
    double_values(vector);
    double_values(array);

    std::cout << "vector:";
    for (const int value : vector) std::cout << ' ' << value;
    std::cout << "\narray:";
    for (const int value : array) std::cout << ' ' << value;
    std::cout << '\n';
}
