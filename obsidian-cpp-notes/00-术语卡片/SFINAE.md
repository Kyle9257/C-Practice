# SFINAE

## 定义

Substitution Failure Is Not An Error：模板替换失败不是错误，不匹配的重载被静默移除而非报错。

## 要点

- 依赖重载解析，用 `std::enable_if_t<条件, 返回类型>` 约束候选重载。
- 条件不满足时该重载被排除，若所有重载都不匹配才编译报错。
- C++20 的 [[concept]] 是其更直观的替代，报错信息更清晰。

## 代码示例

```cpp
template <typename T>
std::enable_if_t<std::is_integral_v<T>, void> f(T) { /* 整型版本 */ }
```

## 关联

- [[concept]] · [[模板特化]] · [[type-traits]]
- 学习路径：[[tier2-模板]]
