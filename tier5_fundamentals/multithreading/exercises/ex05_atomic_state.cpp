/*
问题：atomic 是否可以代替 mutex？

atomic 适合一个独立值的简单读改写。本例 completed 是计数器，ready 是发布标志。
release/acquire 建立同步：观察到 ready=true 的线程也能看到发布前写入的 result。
涉及多个字段共同保持约束时，仍应使用 mutex。

练习：
1. 将 fetch_add 改为 ++completed，验证它仍是原子操作。
2. 增加多个结果字段，思考为何只靠分别 atomic 不能轻易得到一致快照。
3. 查阅 relaxed、acquire、release 与 seq_cst 的保证，避免仅凭性能猜测选择。
*/
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

int main() {
    std::atomic<int> completed{0};
    std::vector<std::jthread> workers;

    for (int i = 0; i < 4; ++i) {
        workers.emplace_back([&completed] {
            completed.fetch_add(1, std::memory_order_relaxed);
        });
    }
    for (auto& worker : workers) {
        worker.join();
    }
    std::cout << "完成数: " << completed.load(std::memory_order_relaxed) << '\n';

    int result = 0; // 只有发布线程写，读取线程在 acquire 后读。
    std::atomic<bool> ready{false};

    std::jthread producer([&] {
        result = 42;
        ready.store(true, std::memory_order_release);
    });
    std::jthread consumer([&] {
        while (!ready.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
        std::cout << "发布的结果: " << result << '\n';
    });
}

