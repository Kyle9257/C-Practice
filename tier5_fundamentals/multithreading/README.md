# C++ 多线程专题

本目录把线程从“能创建”逐步展开到“能安全停止、同步和通信”。每个 `.cpp` 都有独立的 `main`，可以单独运行。

## 编译运行

```powershell
./build_all.ps1
./build/ex01_thread_lifecycle.exe
```

单独编译：

```powershell
g++ -std=c++23 -Wall -Wextra -Wpedantic -O2 -pthread -static exercises/ex01_thread_lifecycle.cpp -o ex01.exe
```

## 学习顺序

| 编号 | 文件 | 重点 |
|---|---|---|
| 01 | `ex01_thread_lifecycle.cpp` | 创建线程、传参、`join`、`joinable`、`detach` 风险 |
| 02 | `ex02_jthread_raii.cpp` | `jthread` 自动等待、RAII 管理线程生命周期 |
| 03 | `ex03_cooperative_stop.cpp` | `stop_token`、请求停止、可中断等待 |
| 04 | `ex04_mutex_and_deadlock.cpp` | 数据竞争、`lock_guard`、`scoped_lock`、避免死锁 |
| 05 | `ex05_atomic_state.cpp` | 原子计数、状态发布、`memory_order` 基础 |
| 06 | `ex06_condition_variable.cpp` | 开始信号、谓词等待、虚假唤醒、停止标志 |
| 07 | `ex07_producer_consumer.cpp` | 线程安全队列、生产者消费者通信、关闭协议 |
| 08 | `ex08_future_results.cpp` | `async`、`promise/future`、返回值和异常跨线程传递 |
| 09 | `ex09_thread_pool.cpp` | 固定工作线程、任务队列、`packaged_task`、结果回收 |

## 建议学习方式

1. 先读文件顶部的问题，预测输出和线程结束顺序。
2. 编译并连续运行三次，观察哪些顺序稳定、哪些不稳定。
3. 完成文件顶部的修改练习，尤其关注错误版本为什么不安全。
4. 不要用 `sleep_for` 代替正确同步；示例中的短暂休眠只用于模拟工作。

## 核心原则

- 一个 `std::thread` 销毁前必须变成不可连接状态，通常调用 `join()`。
- 优先使用 `std::jthread` 管理生命周期，停止采用协作协议，不能强制杀死线程。
- 多个线程访问同一对象且至少一个线程写入时，必须建立同步，否则是数据竞争。
- 互斥量保护“一组不变量”；原子变量适合独立、简单的共享状态。
- 条件变量必须带谓词等待，谓词所依赖的状态应由同一互斥量保护。
- 线程间通信要定义正常数据、停止/关闭和异常这三条路径。

