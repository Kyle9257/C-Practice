## double和float类型控制输出
- [x]  输出格式控制，输出小数点是std::fixed << std::setprecision(2) << " "
- [x] 知道该方法在`#include <iomanip>`头文件中
代码示例
```cpp
#include <iostream>
#include  <iomanip> //这里包含了std::setprecisioin(2)
std::cout << std::fixed << std::setprecisioin(2) << value << " ";
```

## 不一致输出



## 关联
各种输出控制，STL容器输出[[tier0-STL应用|STL学习]]