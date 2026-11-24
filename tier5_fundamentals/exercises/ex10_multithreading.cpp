/*
学习目标：
1. 掌握 thread 的创建、保存和 join。
2. 区分 mutex 保护复合操作与 atomic 保护简单原子操作的用途。
3. 理解并发程序的执行顺序通常不确定。

练习方法：
1. 多运行几次，观察 worker 输出顺序可能不同。
2. 修改线程数量，确认 completed 最终等于线程数量。
3. 去掉输出处的 mutex，观察多线程输出可能交错；练习后恢复它。

知识点：
- 每个可连接线程在析构前必须 join 或 detach，否则程序会 terminate。
- lock_guard 使用 RAII：构造时加锁，离开作用域时自动解锁。
- atomic 保证单次原子操作不会产生数据竞争，但不能自动保护一组复合操作。
- memory_order_relaxed 只保证计数读写的原子性，不建立额外的跨线程同步顺序。
- join 不只是等待线程结束，也让主线程看到该线程完成前的效果。
*/
#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

int main() {
    std::atomic<int> completed{0};
    std::mutex output_mutex;
    std::vector<std::thread> workers;

    for (int id = 1; id <= 4; ++id) {
        // id 按值捕获；共享变量按引用捕获，并保证它们活到所有线程 join 完成。
        workers.emplace_back([id, &completed, &output_mutex] {
            {
                // 把一整次输出作为临界区，避免多个线程的文本互相穿插。
                const std::lock_guard<std::mutex> lock(output_mutex);
                std::cout << "worker " << id << " 完成\n";
            }
            completed.fetch_add(1, std::memory_order_relaxed);
        });
    }

    for (auto& worker : workers) {
        // join 等待线程完成，使 thread 对象变为不可连接状态。
        worker.join();
    }
    std::cout << "完成线程数: " << completed.load(std::memory_order_relaxed) << '\n';
}
