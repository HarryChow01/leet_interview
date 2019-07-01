//
// Created by Chow on 2019/5/16.
//

#ifndef LEET_INTERVIEW_SINGLETON_H
#define LEET_INTERVIEW_SINGLETON_H

#include <mutex>

// C++单例用懒汉模式的参考资料较多
// 重要参考：https://blog.csdn.net/janeqi1987/article/details/76147312
// 需求：1、懒汉模式 2、线程安全 3、高效（加锁的高效） 4、通用（排除平台相关的系统调用）

// 看似线程安全的双检锁版本，但是有问题（多核的乱序执行问题）

class Singleton1 {
public:
    static Singleton1 *getInstance() {
        if (nullptr == instance_) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (nullptr == instance_) {
                instance_ = new Singleton1;
            }
        }
        return instance_;
    }
private:
    static std::mutex mutex_;
    static Singleton1 *instance_;
    Singleton1() = default; // Singleton1() {};
    Singleton1(const Singleton1& singleton1) = delete;      // 或者只声明不实现
    Singleton1& operator=(const Singleton1& singleton1) = delete;   // 或者只声明不实现
};
Singleton1* Singleton1::instance_ = nullptr;

// Gcc 4.0以上推荐的做法
class Singleton2 {
public:
    static Singleton2 & getInstance() {
        static Singleton2 instance;
        return instance;
    }
private:
    Singleton2() = default; // Singleton2() {};
    Singleton2(const Singleton2& singleton2) = delete;
    Singleton2& operator=(const Singleton2& singleton2) = delete;
};




#endif //LEET_INTERVIEW_SINGLETON_H
