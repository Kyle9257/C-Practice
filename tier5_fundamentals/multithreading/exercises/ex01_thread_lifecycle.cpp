/*
问题：线程何时开始？何时结束？thread 对象和执行线程是不是同一事物？

结论：
- 构造 std::thread 后，新线程可以立刻并发执行，先后顺序不能由源码位置推断。
- thread 对象是线程的管理句柄，不是线程函数本身。
- join() 等待执行线程结束；成功后 thread 变为不可连接状态。
- 可连接的 std::thread 直接析构会调用 std::terminate。
- detach() 放弃管理权，通常难以保证参数和共享对象的生命周期，业务代码应慎用。

练习：
1. 多运行几次，观察三个 worker 的开始/结束顺序。
2. 把 worker 的 int& 改成 int，并解释为什么 total 不再变化。
3. 删除 join 循环，观察程序为何异常终止，然后恢复。
*/
#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

void worker(int id, int amount, int& total, std::mutex& mutex) {
    std::this_thread::sleep_for(10ms * id);
    {
        const std::lock_guard lock(mutex);
        total += amount;
        std::cout << "worker " << id << " 更新 total = " << total << '\n';
    }
}

int main() {
    int total = 0;
    std::mutex mutex;
    std::vector<std::thread> threads;

    for (int id = 1; id <= 3; ++id) {
        // 普通参数会复制进线程内部；引用参数必须显式使用 std::ref。
        threads.emplace_back(worker, id, id * 10, std::ref(total), std::ref(mutex));
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    std::cout << "全部线程已结束，total = " << total << '\n';
}

