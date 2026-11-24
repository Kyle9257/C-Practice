/*
问题：等待某个状态时，为什么不能不断循环检查或只 sleep？

condition_variable 会让等待线程休眠，通知到来后重新取得 mutex 并检查谓词。
谓词必须存在，因为唤醒可能是虚假的，或者状态已被其他线程先一步改变。

练习：
1. 增加三个等待线程，比较 notify_one 与 notify_all。
2. 去掉谓词版本，解释虚假唤醒可能造成什么错误。
3. 添加 shutdown 状态，使等待者既能因“有工作”也能因“系统关闭”而退出。
*/
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

int main() {
    std::mutex mutex;
    std::condition_variable condition;
    bool ready = false;
    std::string message;

    std::jthread receiver([&] {
        std::unique_lock lock(mutex);
        condition.wait(lock, [&ready] { return ready; });
        // wait 返回时已重新取得锁，可以安全读取 message。
        std::cout << "收到: " << message << '\n';
    });

    {
        const std::lock_guard lock(mutex);
        message = "任务可以开始";
        ready = true;
    } // 先释放锁，使被唤醒线程可以立即取得它。
    condition.notify_one();
}

