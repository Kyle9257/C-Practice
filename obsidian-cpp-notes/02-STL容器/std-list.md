# std::list
## 定义



双向链表，任意位置插入/删除O(1)，无随机访问，遍历只能顺序。
## 要点
- 双向链表，任意位置插入/删除O(1),2无随机访问，遍历只能顺序。不能随意取中间值
- ==🔴构造==。assign
- 双向插入。push_front，push_back,
- insert(std::next(vec.begin()), 3).指定位置插入，不能用vec.begin() + n，用next
- 删除。pop_front(), pop_back(), erase();
- 遍历`for(auto it = vec.begin(); it != vec.end(); ++it) std::cout << ' ' << *it`;