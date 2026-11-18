#include <iostream>
#include <cstring>

// 管理裸资源的类，必须实现 Rule of Five（五个特殊成员函数）
class Buffer {
    char* data_;
    std::size_t size_;

public:
    explicit Buffer(std::size_t n) : data_(new char[n]), size_(n) {}

    ~Buffer() { delete[] data_; }                            // 1 析构

    Buffer(const Buffer& o)                                  // 2 拷贝构造
        : data_(new char[o.size_]), size_(o.size_) {
        std::memcpy(data_, o.data_, size_);
        std::cout << "copy ctor\n";
    }

    Buffer(Buffer&& o) noexcept : data_(o.data_), size_(o.size_) {  // 3 移动构造
        o.data_ = nullptr;
        o.size_ = 0;
        std::cout << "move ctor\n";
    }

    Buffer& operator=(const Buffer& o) {                     // 4 拷贝赋值
        if (this != &o) {
            delete[] data_;
            data_ = new char[o.size_];
            size_ = o.size_;
            std::memcpy(data_, o.data_, size_);
        }
        std::cout << "copy assign\n";
        return *this;
    }

    Buffer& operator=(Buffer&& o) noexcept {                 // 5 移动赋值
        if (this != &o) {
            delete[] data_;
            data_ = o.data_;
            size_ = o.size_;
            o.data_ = nullptr;
            o.size_ = 0;
        }
        std::cout << "move assign\n";
        return *this;
    }

    std::size_t size() const { return size_; }
};

// Rule of Zero 的对照：如果成员都是值语义（如 std::string / std::vector），
// 五个成员函数都可以不写，编译器自动生成且行为正确。

class BuferZero{
    char* data_;
    std::size_t size_;
public:
    explicit BuferZero(std::size_t n)       //0构造函数
    : data_(new char[n]),size_(n) {
        std::cout << "BuferZero 构造函数\n";
    }
    ~BuferZero(){
        delete[] data_;
    };                //1析构函数

    BuferZero(const BuferZero& inData)              //2拷贝构造
    : data_(new char[inData.size_]), size_(inData.size_) {
        std::memcpy(data_, inData.data_, size_);
        std::cout << "BuferZero 拷贝构造\n";
    }

    BuferZero(BuferZero&& inData) noexcept      //3移动构造
    : data_(inData.data_), size_(inData.size_) {
        inData.data_ = nullptr;
        inData.size_ = 0;
        std::cout << "BuferZero 移动构造\n";
    };

    BuferZero& operator=(const BuferZero& inData) {          //4拷贝赋值，新建一个控件，拷贝数据
        if (this != &inData) {
            delete[] data_;
            data_ = new char[inData.size_];
            size_ = inData.size_;
            std::memcpy(data_, inData.data_, size_);
        }
        std::cout << "BuferZero 拷贝赋值\n";
        return *this;
    }

    BuferZero& operator=(BuferZero&& inData) noexcept {      //5移动赋值，数据移动，没有新建控件，直接移动数据
        if (this != &inData) {
            delete[] data_;
            data_ = inData.data_;
            size_ = inData.size_;
            inData.data_ = nullptr;
            inData.size_ = 0;
        }
        std::cout << "BuferZero 移动赋值\n";
        return *this;
    }

};

int main() {
    Buffer a(10);
    Buffer b = a;              // copy ctor
    Buffer c = std::move(a);   // move ctor
    c = b;                     // copy assign
    c = std::move(b);          // move assign

    BuferZero buffer1(10);
    BuferZero buffer2 = buffer1;              // 拷贝构造
    BuferZero buffer3 = std::move(buffer1);   // 移动构造
    buffer3 = buffer2;                        // 拷贝赋值       
    buffer3 = std::move(buffer2);             // 移动赋值
}
