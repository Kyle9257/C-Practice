/*
学习目标：
1. 认识 std::format（C++20）和 std::print/std::println（C++23）的格式化方式。
2. 理解语言标准版本与标准库实现版本是两个不同条件。
3. 学会用特性测试宏编写可在不同工具链构建的示例。

练习方法：
1. 运行程序，确认当前标准库进入 print、format 还是 iostream 分支。
2. 把精度从 {:.1f} 改成 {:.2f}，观察浮点输出变化。
3. 使用另一套编译器或标准库构建，比较启用的分支。

知识点：
- __has_include 只说明头文件存在，不保证某个库特性完整可用。
- __cpp_lib_print 和 __cpp_lib_format 是标准库特性测试宏。
- format 返回 string；print/println 直接写入输出流，println 还会追加换行。
- iomanip 是旧工具链的兼容方法，但格式状态会保留在流对象中。
*/
#include <iomanip>
#include <iostream>
#include <string>

#if __has_include(<format>)
#include <format>
#endif

#if __has_include(<print>)
#include <print>
#endif

int main() {
    const std::string name = "C++";
    const double score = 95.5;

// 优先使用更新的 print，其次 format，最后退回传统流输出。
#if defined(__cpp_lib_print) && __cpp_lib_print >= 202207L
    std::println("{} score = {:.1f}", name, score);
#elif defined(__cpp_lib_format) && __cpp_lib_format >= 201907L
    std::cout << std::format("{} score = {:.1f}\n", name, score);
#else
    std::cout << name << " score = " << std::fixed << std::setprecision(1) << score << '\n';
    std::cout << "当前标准库未提供 format/print，以上为 iostream 兼容输出。\n";
#endif
}
