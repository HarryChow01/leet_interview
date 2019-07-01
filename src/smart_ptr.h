//
// Created by Chow on 2019/5/26.
//

#ifndef CPP11_SMART_PTR_H
#define CPP11_SMART_PTR_H

#include <memory>
#include <iostream>



template<typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
    explicit unique_ptr(T *ptr = nullptr) noexcept :ptr_(ptr)  { }

    ~unique_ptr() {
        del(ptr_);
    }
    /* 不支持拷贝与赋值   */
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    /*可以拷贝或者赋值一个将要被销毁的 unique_ptr（右值引用）*/
    unique_ptr(unique_ptr&& rhs) noexcept:
            ptr_(rhs.ptr_),del(std::move(rhs.del)) {
        rhs.ptr_ = nullptr ;
    }
    unique_ptr& operator=(unique_ptr&& rhs) noexcept {
        if (this != &rhs ) {
            //std::cout << "operator && rhs " << std::endl ;
            del(ptr_);
            ptr_ = rhs.ptr_;
            del = std::move(rhs.del);
            rhs.ptr_ =  nullptr ;
        }
        return *this ;
    }
    //u.release()   u 放弃对指针的控制权，返回指针，并将 u 置为空
    T* release() {
        T *tmp = ptr_;
        ptr_ = nullptr;
        return  tmp;
    }
    /*
    u.reset()   释放u指向的对象
    u.reset(q)  如果提供了内置指针q，就令u指向这个对象
    u.reset(nullptr) 将 u 置为空
    */

    void reset (T* q = nullptr) {
        if (ptr_) {
            del(ptr_);
        }
        ptr_ = q;
    }
    void swap(unique_ptr &rhs) noexcept {
        using std::swap;
        swap(ptr_,rhs.ptr_);
        swap(del,rhs.del);
    }
    T* get() { return ptr_; }
    Deleter& get_deleter(){ return  del; }
    T& operator*()  { return *ptr_; }
    T* operator->() { return  ptr_; }
private:
    T *ptr_ = nullptr ;
    Deleter del ;

};


class Counter {
public:
    Counter():ref_count(0),weak_ref(0){};
    uint32_t ref_count;
    uint32_t weak_ref;
};

template<class T> class weak_ptr;//为了用weak_ptr的lock()，来生成share_ptr用，需要拷贝构造用
template <typename T>
class shared_ptr {
public:
    shared_ptr(T* p = nullptr): ptr_(p){
        counter_ = new Counter();
        if (p)
            counter_->ref_count = 1;
    }
    ~shared_ptr() {
        release();
    }

    shared_ptr(const shared_ptr<T> &rhs) {
        ptr_ = rhs.ptr_;
        (rhs.counter_)->ref_count++;
        counter_ = rhs.counter_;
    }
    shared_ptr(const weak_ptr<T> &weakPtr) {
        // 为了用weak_ptr的lock()，来生成share_ptr用，需要拷贝构造用
        ptr_ = weakPtr.ptr_;
        (weakPtr.counter_)->count++;
        counter_ = weakPtr.counter_;
    }
    shared_ptr<T>& operator=(const shared_ptr<T> &rhs) {
        if (this != &rhs) {
            release();
            (rhs.counter_)->ref_count++;
            counter_ = rhs.counter_;
            ptr_ = rhs.ptr_;
        }
        return *this;
    }

    shared_ptr(shared_ptr<T> &&rhs) {
        *this = std::move(rhs);
    }
    shared_ptr<T>& operator=(shared_ptr<T> &&rhs) {
        if (this != &rhs) {
            release();
            *this = std::move(rhs);
            //(rhs.counter_)->ref_count++;
            //rhs.counter_ = nullptr;
            //rhs.ptr_ = nullptr;
        }
        return *this;
    }
    
    T& operator*() {
        return *ptr_;
    }
    T* operator->() {
        return ptr_;
    }
    
    friend class weak_ptr<T>; //方便weak_ptr与share_ptr设置引用计数和赋值。
private:
    void release() {
        counter_->ref_count--;
        if (counter_->ref_count <1) {
            delete ptr_;
            ptr_ = nullptr;
            if(counter_->weak_ref <1) {
                delete counter_;
                counter_ = nullptr;
            }
        }
    }
    
private:
    T* ptr_ = nullptr;
    Counter* counter_ = nullptr;
};

template<class T>
class weak_ptr {
public://给出默认构造和拷贝构造，其中拷贝构造不能有从原始指针进行构造
    weak_ptr() {}

    weak_ptr(const shared_ptr<T> &sp) :
            ptr_(sp.ptr_), counter_(sp.counter_) {
        counter_->weak_ref++;
    }
    weak_ptr(const weak_ptr<T> &wp) :
            ptr_(wp.ptr_), counter_(wp.counter_) {
        counter_->weak_ref++;
    }
    weak_ptr(weak_ptr<T> &&wp) {
        *this = std::move(wp);
    }
    ~weak_ptr() {
        release();
    }

    weak_ptr<T>& operator=(const weak_ptr<T> &rhs) {
        if (this != &rhs) {
            release();
            counter_ = rhs.counter_;
            counter_->weak_ref++;
            ptr_ = rhs.ptr_;
        }
        return *this;
    }
    weak_ptr<T>& operator=(weak_ptr<T> &&rhs) {
        if (this != &rhs) {
            release();
            *this = std::move(rhs);
        }
        return *this;
    }

    weak_ptr<T>& operator=(const shared_ptr<T> &sp) {
        release();
        counter_ = sp.counter_;
        counter_->weak_ref++;
        ptr_ = sp.ptr_;
        return *this;
    }

    shared_ptr<T> lock() {
        return shared_ptr<T>(*this);
    }

    bool expired() {
        if (counter_ && counter_->ref_count) {

            return false;
        }
        return true;
    }

    friend class shared_ptr<T>;//方便weak_ptr与share_ptr设置引用计数和赋值。
private:
    void release() {
        if (counter_) {
            counter_->weak_ref--;
            if (counter_->ref_count < 1 && counter_->weak_ref < 1) {
                delete counter_;
                counter_ = nullptr;
            }
        }
    }

    T *ptr_ = nullptr;
    Counter *counter_ = nullptr;
};


#endif //CPP11_SMART_PTR_H
