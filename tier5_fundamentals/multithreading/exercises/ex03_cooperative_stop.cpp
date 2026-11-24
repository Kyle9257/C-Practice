/*
问题：C++ 为什么没有安全的“强制杀死线程”？

线程可能正持有锁或正在修改对象，强杀会破坏程序不变量。正确做法是请求停止，
由工作线程在安全位置检查 stop_token 并自行退出，这称为协作停止。

练习：
1. 调整 request_stop 前的等待时间，观察处理次数变化。
2. 删除 stop_requested 检查，解释请求停止为什么失效。
3. 把轮询改为 stop_callback，观察停止请求到来时的回调线程。
*/
#include <chrono>
#include <iostream>
#include <mutex>
#include <stop_token>
#include <thread>

using namespace std::chrono_literals;

int main() {
    std::mutex output_mutex;

    std::jthread worker([&output_mutex](std::stop_token token) {
        int completed = 0;
        while (!token.stop_requested()) {
            std::this_thread::sleep_for(20ms);
            ++completed;
            const std::lock_guard lock(output_mutex);
            std::cout << "完成批次 " << completed << '\n';
        }

        const std::lock_guard lock(output_mutex);
        std::cout << "在安全点响应停止请求\n";
    });

    std::this_thread::sleep_for(75ms);
    std::cout << "main 请求停止\n";
    worker.request_stop();
    worker.join();
}

