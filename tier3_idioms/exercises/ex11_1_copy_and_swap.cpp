#include <iostream>
#include <utility>
#include <vector>

class Vec {
    std::vector<int> data_;

public:
    explicit Vec(std::vector<int> d) : data_(std::move(d)) {}

    Vec(const Vec&) = default;   // copy-and-swap 需要显式保留拷贝构造
    Vec(Vec&&) = default;        // 以及移动构造

    // copy-and-swap：一个 operator= 同时处理拷贝和移动
    Vec& operator=(Vec other) {          // 按值传参：实参处已发生拷贝或移动
        data_.swap(other.data_);          // 交换，other 析构时释放旧资源
        std::cout << "copy-and-swap assign\n";
        return *this;
    }

    void show() const {
        for (int x : data_) std::cout << x << " ";
        std::cout << "\n";
    }
};

int main() {
    Vec a(std::vector<int>{1, 2, 3});
    Vec b(std::vector<int>{4, 5});

    b = a;                 // 拷贝：other 是 a 的副本
    b.show();

    b = Vec({9, 9});       // 移动：other 是临时对象
    b.show();
}
