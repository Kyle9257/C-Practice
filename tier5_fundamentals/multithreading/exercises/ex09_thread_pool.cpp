/*
问题：为什么不为每个很小的任务都创建一个新线程？

创建和销毁系统线程有成本。线程池预先建立固定数量的工作线程，让它们从共享队列
不断领取任务。submit 用 packaged_task 把“可调用对象”和 future 结果连接起来。

本例是教学版：只接受无参数、返回 int 的任务。生产代码通常会做成泛型模板，并明确
拒绝关闭后的提交、任务取消、容量限制和异常策略。

练习：
1. 增加任务数量并记录执行任务的线程 id。
2. 将 tasks_ 改成有界队列，为 submit 增加背压等待。
3. 尝试把 submit 泛化为任意返回类型，理解类型擦除和 packaged_task 的关系。
*/
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

class ThreadPool {
public:
    explicit ThreadPool(std::size_t worker_count) {
        if (worker_count == 0) {
            throw std::invalid_argument("线程数必须大于零");
        }
        for (std::size_t i = 0; i < worker_count; ++i) {
            workers_.emplace_back([this] { worker_loop(); });
        }
    }

    ~ThreadPool() {
        {
            const std::lock_guard lock(mutex_);
            stopping_ = true;
        }
        condition_.notify_all();
        // jthread 成员随后逆序析构并 join。worker_loop 会先处理完队列中的任务。
    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    std::future<int> submit(std::function<int()> function) {
        auto task = std::make_shared<std::packaged_task<int()>>(std::move(function));
        std::future<int> result = task->get_future();
        {
            const std::lock_guard lock(mutex_);
            if (stopping_) {
                throw std::runtime_error("线程池已经停止");
            }
            tasks_.push([task] { (*task)(); });
        }
        condition_.notify_one();
        return result;
    }

private:
    void worker_loop() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock lock(mutex_);
                condition_.wait(lock, [this] { return stopping_ || !tasks_.empty(); });
                if (stopping_ && tasks_.empty()) {
                    return;
                }
                task = std::move(tasks_.front());
                tasks_.pop();
            }
            task(); // 不持锁执行任务，否则所有 worker 会被串行化。
        }
    }

    std::mutex mutex_;
    std::condition_variable condition_;
    std::queue<std::function<void()>> tasks_;
    std::vector<std::jthread> workers_;
    bool stopping_ = false;
};

int main() {
    ThreadPool pool(3);
    std::vector<std::future<int>> results;

    for (int value = 1; value <= 6; ++value) {
        results.push_back(pool.submit([value] { return value * value; }));
    }

    for (auto& result : results) {
        std::cout << result.get() << ' ';
    }
    std::cout << '\n';
}

