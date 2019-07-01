//
// Created by Chow on 2019/5/29.
//

#ifndef LEET_INTERVIEW_BLOCKINGQUEUE_H
#define LEET_INTERVIEW_BLOCKINGQUEUE_H

#include <mutex>
#include <condition_variable>
#include <deque>

template <typename T>
class BlockingQueue {
public:
    explicit BlockingQueue(size_t capacity = kCapacitySize) : capacity_(capacity) {}
    void pop_front();
    void push_back(const T& item);
    T& front();

    size_t size() {
        std::unique_lock<std::mutex> lock(mutex_);
        return data_.size();
    }

    bool empty() {
        std::unique_lock<std::mutex> lock(mutex_);
        return data_.empty();
    }

private:
    static const size_t kCapacitySize = 1024;
    size_t capacity_;
    std::deque<T> data_;
    std::mutex mutex_;
    std::condition_variable cvNotFull_;
    std::condition_variable cvNotEmpty_;
};



#endif //LEET_INTERVIEW_BLOCKINGQUEUE_H
