# pimpl

## 定义

Pointer to Implementation：把实现细节藏进 `.cpp`，头文件只留接口 + 前向声明。

## 要点

- 两个好处：① 头文件不暴露私有成员 ② 改实现不触发大量重编译。
- 析构必须在 `.cpp` 定义（`unique_ptr<Impl>` 需要完整类型）。
- Qt 的 `Q_DECLARE_PRIVATE` / `Q_D` 就是这套结构。

## 代码示例

```cpp
// widget.h
class Widget {
    struct Impl;                  // 只前向声明
    std::unique_ptr<Impl> pImpl;
public:
    explicit Widget(int v);
    ~Widget();                    // 必须在 .cpp 定义
};
```

## 关联

- [[Rule of Five]] · [[编译依赖]]
- 学习路径：[[tier3-惯用法]]
