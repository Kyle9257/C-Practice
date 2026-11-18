#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <iomanip>
#include <ranges>

// 打印辅助（按值接收，兼容 ranges 视图这类不可 const 访问的类型）
template <typename R>
void print(const char* tag, R r) {
    std::cout << tag;
    for (const auto& x : r) std::cout << ' ' << x;
    std::cout << '\n';
}

// 排序键提取：按「末位数字」排序，而非元素本身
int last_digit(int x) { return x % 10; }

int main() {
    std::cout << std::boolalpha;

    // ===== 一、排序族：稳定 / 部分 / 自定义键 =====
    std::vector<int> v = {5, 2, 8, 1, 9, 3, 6};

    // 1. 默认升序
    std::sort(v.begin(), v.end());
    print("sort 升序:      ", v);

    // 2. 降序（用标准仿函数，而非自写 lambda）
    std::sort(v.begin(), v.end(), std::greater<>{});
    print("sort 降序:      ", v);

    // 3. 稳定排序 vs 普通排序：只在「相等元素」上体现差异
    //    sort 是「不保证」稳定（不一定打乱），stable_sort 是「保证」稳定。
    //    这里用 20 个元素、只有两种 key，让 sort 大概率打乱相等元素，直观看到区别。
    struct Item { int key; int seq; };
    std::vector<Item> raw;
    for (int i = 0; i < 20; ++i)
        raw.push_back({i % 2, i});   // key 交替 0/1，seq 记录原始顺序

    auto print_items = [](const char* tag, const std::vector<Item>& vv) {
        std::cout << tag;
        for (auto& i : vv) std::cout << ' ' << i.key << ':' << i.seq;
        std::cout << '\n';
    };
    auto by_key = [](const Item& a, const Item& b) { return a.key < b.key; };

    auto sorted = raw;
    std::sort(sorted.begin(), sorted.end(), by_key);
    print_items("sort:        ", sorted);

    auto stabled = raw;
    std::stable_sort(stabled.begin(), stabled.end(), by_key);
    print_items("stable_sort: ", stabled);
    std::cout << "   // 看 key=0 那 10 个：stable_sort 的 seq 保持 0,2,4,...；sort 通常已乱序\n";

    // 4. 部分排序：只需最小的 k 个有序（其余不保证）
    std::vector<int> p = {7, 4, 9, 1, 8, 2, 5};
    std::partial_sort(p.begin(), p.begin() + 3, p.end());
    print("partial_sort 前3:", p);

    // 5. 按「键」排序而不排序元素本身（sort 的投影替代）
    std::vector<int> keys = {15, 22, 31, 7, 48};
    std::sort(keys.begin(), keys.end(),
              [](int a, int b) { return last_digit(a) < last_digit(b); });
    print("按末位数字排序:", keys);

    // ===== 二、查找族：线性 / 二分 =====
    // 二分查找要求序列「已排序」；这里故意放重复的 7，观察区间语义
    std::vector<int> s = {1, 3, 5, 7, 7, 7, 9, 11};

    // find：线性查找，无需有序，返回第一个匹配
    auto it = std::find(s.begin(), s.end(), 7);
    std::cout << "find(7):        " << (it != s.end() ? "命中" : "未命中") << '\n';

    // 有序序列用二分：lower_bound / upper_bound / equal_range
    auto lb = std::lower_bound(s.begin(), s.end(), 7);   // 第一个 >= 7
    auto ub = std::upper_bound(s.begin(), s.end(), 7);   // 第一个 > 7
    std::cout << "lower_bound(7) 下标 = " << (lb - s.begin())
              << "   upper_bound(7) 下标 = " << (ub - s.begin())
              << "   区间 [7,7] 元素数 = " << (ub - lb) << '\n';

    auto [lo, hi] = std::equal_range(s.begin(), s.end(), 7);
    std::cout << "equal_range(7) 区间长度 = " << (hi - lo) << '\n';

    // 未命中时 lower_bound 给出「正确插入位置」
    auto ins = std::lower_bound(s.begin(), s.end(), 6);
    std::cout << "6 应插入下标 = " << (ins - s.begin()) << "   // 保持有序\n";

    // ===== 三、修改 / 拷贝族：in-place 与写回 =====
    std::vector<int> a = {1, 2, 3, 4, 5};

    // transform 结果可写回原区间（无重叠时安全）
    std::transform(a.begin(), a.end(), a.begin(),
                   [](int x) { return x * x; });
    print("transform 平方: ", a);

    // copy_if 只拷贝满足条件的元素
    std::vector<int> even;
    std::copy_if(a.begin(), a.end(), std::back_inserter(even),
                 [](int x) { return x % 2 == 0; });
    print("copy_if 偶数:   ", even);

    std::vector<int> oddVec;
    std::copy_if(a.begin(),a.end(),std::back_inserter(oddVec),[](int x) {return x % 2 == 1 ;});

    print("copy_if 奇数：", oddVec);

    // ===== 四、重排 / 划分 =====
    std::vector<int> r = {1, 2, 3, 4, 5, 6, 7, 8};

    // partition 把满足条件的放前面，返回分界点（不保证相对顺序）
    auto mid = std::partition(r.begin(), r.end(),
                              [](int x) { return x % 2 == 1; });
    std::cout << "partition 奇数前置:";
    for (auto it2 = r.begin(); it2 != mid; ++it2) std::cout << ' ' << *it2;
    std::cout << "  |  ";
    for (auto it2 = mid; it2 != r.end(); ++it2) std::cout << ' ' << *it2;
    std::cout << '\n';

    // next_permutation 生成全排列
    std::vector<int> perm = {1, 2, 3};
    std::cout << "next_permutation:";
    do { std::cout << " [" << perm[0] << perm[1] << perm[2] << ']'; }
    while (std::next_permutation(perm.begin(), perm.end()));
    std::cout << '\n';

    // ===== 五、数值算法 <numeric> =====
    std::vector<int> n = {1, 2, 3, 4, 5};

    int sum = std::accumulate(n.begin(), n.end(), 0);           // 求和
    int prod = std::accumulate(n.begin(), n.end(), 1,            // 连乘（自定义运算）
                               std::multiplies<>{});
    std::vector<int> pref(n.size());
    std::partial_sum(n.begin(), n.end(), pref.begin());          // 前缀和
    int lo2 = *std::min_element(n.begin(), n.end());
    int hi2 = *std::max_element(n.begin(), n.end());

    std::cout << "sum = " << sum << "   prod = " << prod
              << "   前缀和:";
    for (int x : pref) std::cout << ' ' << x;
    std::cout << "   min = " << lo2 << "   max = " << hi2 << '\n';

    // ===== 六、C++20 ranges 算法：直接作用容器、返回可链式视图 =====
    namespace rv = std::views;
    auto result = v
                | rv::filter([](int x) { return x > 3; })   // 过滤
                | rv::transform([](int x) { return x * 10; }) // 映射
                | rv::take(3);                                // 取前 3
    print("ranges 管道:    ", result);

    return 0;
}
