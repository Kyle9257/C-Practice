# ==🔴常见函数==
## 1、排序 std::sort`(vec.begin(), vec.end())`


排序函数支持输入lamda函数，默认是从小到大。
`std::sort(vec.begin(), vec.end(), [](double a, double b){return a >b})`
`std::sort(vec.begin(),vec.end(),std::greater<>{})`,用标准仿函数，而非自写lambda
设置函数，让从大到小·排序。
1、==稳定排序==`std::stable_sort(vec.begin(),vec.end(),[](){})`这里lamdda函数没有写出，需要自己完善
2、==🔴部分排序==，`std::partial_sort(vec.begin(),vec.begin() + 3,[](){})`;只排序数组前面三个
## 2、find，find_if/find_if_not
### 1、`std::find(vec.begin(),vec.end(),value)`;查找数组中是否有value,如果有就返回第一个出现的迭代器。==无需有序==
### 2、`std::find_if(vec.begin(),vec.end(),[](){})`,

## 3、`std::find_if_not(vec.begin(),vec.end(),[](){})`,找到第一个不满足输入规则的值，返回迭代器。==🟢二分查找，必须有序==

### 4`std::lower_bound(),std::upperbound(),std::equal_range()`
查找。
**二分查找**，被查找的容器必须==🔴有序==，对无序容器进行查找，返回结果无法预测
==🔴lower_bound==:第一个>=查找目标的
==🔴upper_bound==: 第一个>查找目标的
==equal_range==: 等于查找目标的区间长度，有多少个项目内容



## 4、修改，拷贝族：in-space与写回
### 1、std::partition()只把满足条件的内容移动到容器前面，不保证顺序。会被打乱

### 1、std::transform()
### 2、std::copy_if()，满足条件的拷贝到目标位置
**std::inserter()**，自动扩展迭代器，要求容器有push_back
### 3、std::next_permutation，生成全排列

## 5、容器扩容/删除元素 会导致，迭代器失效
```cpp
#include <iostream>
#include <vector>
#include <map>

int main(){
	std::vector<int> vec = {1, 2, 3};
	auot it = vec.begin();
	
	vec.push_back(4);
	//之后再用it，是未定义行为
}
```

//增加
push_back()
emplace_back()
insert( v.begin(), 2 )------容器插入单个
insert( v.begin(), { 4, 6 } )--容器插入多个

//取用
[]
at()-------越界抛出异常
front()，back()
//改值
[]_____速度快，不抛出异常，容器确定时候使用
at()——边界检查，调试时候使用

//删除，v.erase()
`v.erase(v.begin())`----------删除单个
`v.erase(v.begin(),v.begin() + 3)`---------删除一个范围
v.pop_back()，删除最后一个
## 整体变换`std::transform(vec.begin(),vec.end(),[](int x){return x * 2})`
整体变换


## 累加 `std::accumulate(vec.begin(),vec.end(),0)`
最后一个值是初始化值
