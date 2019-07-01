//
// Created by Chow on 2019/5/15.
//

#ifndef LEET_INTERVIEW_THREADSAFE_QUEUE_H
#define LEET_INTERVIEW_THREADSAFE_QUEUE_H

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

template<typename T>
class threadsafe_queue {    // 队列大小没有限制，只使用一个条件变量；

public:
    threadsafe_queue() {}

    threadsafe_queue(const threadsafe_queue &rhs) {
        std::lock_guard<std::mutex> lock(rhs.mutex_);
        data_queue_ = rhs.data_queue_;
    }

    void push(const T& new_value) { //入队操作
        std::lock_guard<std::mutex> lock(mutex_);
        data_queue_.push(new_value);
        data_cond_.notify_one();
    }

    void wait_and_pop(T &value) { //直到有元素可以删除为止
        std::unique_lock<mutex> lock(mutex_);
        data_cond_.wait(lock, [this] { return !data_queue_.empty(); });
        value = data_queue_.front();
        data_queue_.pop();
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<mutex> lock(mutex_);
        data_cond_.wait(lock, [this] { return !data_queue_.empty(); });
        std::shared_ptr<T> res(std::make_shared<T>(data_queue_.front()));
        data_queue_.pop();
        return res;
    }

    bool try_pop(T &value) {//不管有没有队首元素直接返回
        std::lock_guard<std::mutex> lock(mutex_);
        if (data_queue_.empty())
            return false;
        value = data_queue_.front();
        data_queue_.pop();
        return true;
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (data_queue_.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(data_queue_.front()));
        data_queue_.pop();
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return data_queue_.empty();
    }

    using size_type = typename std::queue<T>::size_type;
    size_type size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return data_queue_.size();
    }

private:
    std::mutex mutex_;
    std::queue<T> data_queue_;
    std::condition_variable data_cond_;
};


#endif //LEET_INTERVIEW_THREADSAFE_QUEUE_H
