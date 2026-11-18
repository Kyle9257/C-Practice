#include <iostream>
#include <memory>
#include <string>

// copy-on-write：多个对象共享同一份底层数据，
// 读操作零拷贝；只有真正要修改时才复制一份出来。
class CowString {
    // 底层数据 + 引用计数（由 shared_ptr 管理）
    struct Impl {
        std::string data;
    };
    std::shared_ptr<Impl> impl_;

public:
    explicit CowString(const std::string& s)
        : impl_(std::make_shared<Impl>(Impl{s})) {}

    // 拷贝：只复制 shared_ptr，共享同一份数据，不复制字符串
    CowString(const CowString&) = default;
    CowString& operator=(const CowString&) = default;

    // 读：const 接口，不触发复制
    const std::string& get() const { return impl_->data; }

    // 写：非 const 接口，写前分离（detach）
    void set(const std::string& s) {
        // 若数据被多人共享，先复制一份独占
        if (impl_.use_count() > 1) {
            impl_ = std::make_shared<Impl>(Impl{impl_->data});
        }
        impl_->data = s;
    }
};


class CopyOnWrite{
    struct pimpl
    {
        std::string name_;
    };
    
    std::shared_ptr<pimpl> m_pimpl;

    CopyOnWrite(const CopyOnWrite& c) = default;
    CopyOnWrite& operator = ( const CopyOnWrite& c) = default;

    std::string& get(){ return m_pimpl->name_; };   //读取不复制

    void set(const std::string str){
        if ( m_pimpl.use_count() > 1){
            m_pimpl = std::make_shared<pimpl>(str); //需要写入，且数据被多人共享，先复制一份，自己独立占有
        }
        m_pimpl->name_ = str;
    }


};


int main() {
    CowString a(std::string("hello"));
    CowString b = a;              // 共享同一份数据

    std::cout << "a=" << a.get() << " b=" << b.get()
              << " (共享读)\n";

    b.set("world");               // 写时分离：只复制 b 的那份
    std::cout << "a=" << a.get() << " b=" << b.get()
              << " (写后分离)\n";
}
