/*
问题：生产者如何告诉消费者“暂时没数据”和“以后永远不会再有数据”的区别？

队列需要明确的 close 协议。pop 返回 false 表示队列已关闭且数据已取完；关闭前的
空队列只会让消费者等待。数据、通知和关闭状态共同组成完整通信协议。

练习：
1. 增加第二个消费者，观察每个任务只会被一个消费者取得。
2. 增加第二个生产者，确保最后一个生产者结束后才 close。
3. 将 int 改为自定义 Task，加入任务编号和文本。
*/
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class BlockingQueue {
public:
    bool push(int value) {
        {
            const std::lock_guard lock(mutex_);
            if (closed_) {
                return false;
            }
            queue_.push(value);
        }
        condition_.notify_one();
        return true;
    }

    bool pop(int& value) {
        std::unique_lock lock(mutex_);
        condition_.wait(lock, [this] { return closed_ || !queue_.empty(); });

        if (queue_.empty()) {
            return false; // closed_ 为 true，且剩余任务已经取完。
        }
        value = queue_.front();
        queue_.pop();
        return true;
    }

    void close() {
        {
            const std::lock_guard lock(mutex_);
            closed_ = true;
        }
        condition_.notify_all();
    }

private:
    std::mutex mutex_;
    std::condition_variable condition_;
    std::queue<int> queue_;
    bool closed_ = false;
};

int main() {
    BlockingQueue queue;

    std::jthread consumer([&] {
        int value = 0;
        while (queue.pop(value)) {
            std::cout << "消费任务 " << value << '\n';
        }
        std::cout << "队列关闭，消费者退出\n";
    });

    std::jthread producer([&] {
        for (int value = 1; value <= 5; ++value) {
            queue.push(value);
        }
        queue.close();
    });
}

