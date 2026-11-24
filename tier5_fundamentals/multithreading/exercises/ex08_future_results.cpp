/*
问题：工作线程怎样把返回值或异常交给调用线程？

future 表示一个稍后可取得的结果。get 会等待且只能调用一次；工作线程抛出的异常
会被保存，并在 get 所在线程重新抛出。async 适合有返回值的独立异步计算；
promise 适合手动控制结果何时产生。

练习：
1. 让 divide 抛异常，确认异常在 result.get() 处出现。
2. 尝试调用两次 get，观察 future 的一次性语义。
3. 使用 shared_future 让多个读取线程等待同一结果。
*/
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>

double divide(double left, double right) {
    if (right == 0.0) {
        throw std::invalid_argument("除数不能为零");
    }
    return left / right;
}

int main() {
    auto result = std::async(std::launch::async, divide, 84.0, 2.0);
    try {
        std::cout << "async 结果: " << result.get() << '\n';
    } catch (const std::exception& error) {
        std::cout << "async 异常: " << error.what() << '\n';
    }

    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    std::jthread producer([promise = std::move(promise)]() mutable {
        promise.set_value(21 * 2);
        // 也可以使用 set_exception(std::current_exception()) 传递异常。
    });

    std::cout << "promise 结果: " << future.get() << '\n';
}

