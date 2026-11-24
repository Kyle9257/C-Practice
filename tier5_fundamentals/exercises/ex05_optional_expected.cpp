/*
学习目标：
1. 用 optional<T> 表示“可能有一个 T，也可能没有值”。
2. 用 expected<T, E> 表示“成功值 T 或错误信息 E”。
3. 学会根据失败是否需要携带原因来选择返回类型。

练习方法：
1. 修改 find_even 的输入，观察 value_or 的兜底行为。
2. 给 parse_int 传入负数、空字符串和带尾随字符的文本。
3. 尝试用 if (result) 分支处理 expected，而不是直接调用 value()。

知识点：
- optional 适合“没有值是正常情况”，例如查找未命中。
- expected 适合调用者需要知道失败原因的操作，例如解析、文件读取和网络请求。
- value_or 只返回值或默认值，不会告诉调用者为何无值。
- from_chars 不抛异常且不自动忽略尾随字符，必须同时检查 error 和 ptr。
- expected 是 C++23 组件，可用性还取决于标准库实现。
*/
#include <charconv>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>

#if __has_include(<expected>)
#include <expected>
#endif

std::optional<int> find_even(int value) {
    // 条件运算符的两条路径分别表示“有值”和“无值”。
    return value % 2 == 0 ? std::optional<int>{value} : std::nullopt;
}

#if defined(__cpp_lib_expected) && __cpp_lib_expected >= 202202L
std::expected<int, std::string> parse_int(std::string_view text) {
    int value = 0;
    // from_chars 返回停止位置和错误码，不通过异常报告错误。
    const auto [ptr, error] = std::from_chars(text.data(), text.data() + text.size(), value);
    if (error != std::errc{} || ptr != text.data() + text.size()) {
        return std::unexpected("不是完整整数: " + std::string(text));
    }
    return value;
}
#endif

int main() {
    std::cout << "optional: " << find_even(8).value_or(-1) << '\n';
    std::cout << "optional 无值: " << find_even(7).value_or(-1) << '\n';

#if defined(__cpp_lib_expected) && __cpp_lib_expected >= 202202L
    for (const std::string_view text : {"42", "4x"}) {
        const auto result = parse_int(text);
        if (result) {
            std::cout << "expected 成功: " << *result << '\n';
        } else {
            std::cout << "expected 失败: " << result.error() << '\n';
        }
    }
#else
    std::cout << "当前标准库未提供 std::expected；请使用 C++23 标准库重试。\n";
#endif
}
