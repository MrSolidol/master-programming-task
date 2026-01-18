#ifndef __PROXY_HPP__
#define __PROXY_HPP__

#include <mutex>
#include <utility>

template<class T, class MutexInjection = std::mutex>
class ptr_holder
{
public:
    explicit ptr_holder(T* ptr)
        : ptr_(ptr)
    {}

    // proxy object
    class proxy : private std::lock_guard<MutexInjection>
    {
    public:
        // constructor for holder-based access
        proxy(T* ptr, MutexInjection& mutex)
            : proxy::lock_guard(mutex)
            , ptr_(ptr)
        {}

        // recursive operator->
        T* operator->() const
        {
            return ptr_;
        }

    private:
        T* ptr_;
    };

    proxy operator->() const
    {
        return proxy(ptr_, mutex_);
    }

private:
    T* ptr_;
    mutable MutexInjection mutex_;
};

#endif // __PROXY_HPP__
