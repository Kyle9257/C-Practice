/*
问题：mutex 保护的不是某个变量名字，而是什么？

mutex 保护的是一组共享状态及其不变量。转账必须同时修改两个账户，任一线程都不能
看到“已扣款但未入账”的中间状态。scoped_lock 一次锁住多个 mutex，避免不同代码
采用相反锁顺序造成死锁。

练习：
1. 增加四个线程，在两个方向反复转账，确认总金额不变。
2. 分别用两个 lock_guard 按相反顺序加锁，理解死锁如何形成（不要保留错误代码）。
3. 给 transfer 增加余额不足检查，保证检查和修改处于同一临界区。
*/
#include <iostream>
#include <mutex>
#include <thread>

struct Account {
    explicit Account(int initial_balance) : balance(initial_balance) {}

    int balance;
    std::mutex mutex;
};

void transfer(Account& from, Account& to, int amount) {
    if (&from == &to) {
        return;
    }

    // 同时取得两个锁；内部使用一致策略避免 AB-BA 锁顺序死锁。
    const std::scoped_lock lock(from.mutex, to.mutex);
    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
    }
}

int main() {
    Account alice{1000};
    Account bob{1000};

    std::jthread first([&] {
        for (int i = 0; i < 1000; ++i) {
            transfer(alice, bob, 1);
        }
    });
    std::jthread second([&] {
        for (int i = 0; i < 1000; ++i) {
            transfer(bob, alice, 1);
        }
    });

    first.join();
    second.join();
    std::cout << "Alice: " << alice.balance << ", Bob: " << bob.balance << '\n';
    std::cout << "总金额: " << alice.balance + bob.balance << '\n';
}

