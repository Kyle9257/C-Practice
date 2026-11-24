/*
问题：函数中途 return 或抛异常时，如何保证线程一定被等待？

std::jthread 的析构函数会请求停止并 join，因此适合用 RAII 管理线程。
本例没有读取 stop_token，停止请求不会打断工作，但析构仍会等待线程完成。

练习：
1. 删除显式 join，确认离开作用域时仍会等待两个线程。
2. 将 jthread 换成 thread，思考异常路径需要怎样手工清理。
3. 打印主线程与工作线程的 get_id()。
*/
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;

int main() {
    std::mutex output_mutex;

    {
        std::jthread first([&output_mutex] {
            std::this_thread::sleep_for(30ms);
            const std::lock_guard lock(output_mutex);
            std::cout << "first 完成\n";
        });

        std::jthread second([&output_mutex] {
            std::this_thread::sleep_for(10ms);
            const std::lock_guard lock(output_mutex);
            std::cout << "second 完成\n";
        });

        std::cout << "main 即将离开局部作用域\n";
    } // second、first 逆序析构，各自请求停止并 join。

    std::cout << "两个 jthread 都已结束\n";
}

