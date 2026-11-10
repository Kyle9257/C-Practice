#include <iostream>
#include <type_traits>
#include <utility>

// 条件 noexcept：swap 是否 noexcept 取决于 T 的移动操作是否 noexcept
template <typename T>
void my_swap(T& a, T& b)
    noexcept(std::is_nothrow_move_constructible_v<T> &&
             std::is_nothrow_move_assignable_v<T>) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

struct NoThrow {};
struct Throw { Throw(Throw&&) {} };  // 移动构造没标 noexcept

int main() {
    std::cout << std::boolalpha;
    std::cout << "my_swap<NoThrow> noexcept = "
              << noexcept(my_swap(std::declval<NoThrow&>(), std::declval<NoThrow&>()))
              << "\n";   // true

    std::cout << "my_swap<Throw> noexcept = "
              << noexcept(my_swap(std::declval<Throw&>(), std::declval<Throw&>()))
              << "\n";   // false

    std::cout << "标准库约定：std::swap 的 noexcept 也是这样根据 T 的条件推导的\n";
}
