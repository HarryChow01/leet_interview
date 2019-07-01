//
// Created by Chow on 2019/5/29.
//

#include <iostream>
#include "BlockingQueue.h"

template <typename T>
void BlockingQueue<T>::pop_front() {
    std::unique_lock<std::mutex> lock(mutex_);
    cvNotEmpty_.wait(lock, [this] { return !data_.empty(); });
    data_.pop_front();
    cvNotFull_.notify_one();
}

template <typename T>
void BlockingQueue<T>::push_back(const T& item) {
    std::unique_lock<std::mutex> lock(mutex_);
    cvNotFull_.wait(lock, [this] { return data_.size() < capacity_; });
    data_.push_back(item);
    cvNotEmpty_.notify_one();
}

template <typename T>
T& BlockingQueue<T>::front() {
    std::unique_lock<std::mutex> lock(mutex_);
    cvNotEmpty_.wait(lock, [this] { return !data_.empty(); });
    return data_.front();
}

int main() {
    BlockingQueue<int> queue;
    queue.push_back(5);
    int item = queue.front();
    std::cout << "size: " << queue.size() << std::endl;
    std::cout << "item: " << item << std::endl;
    queue.pop_front();
    std::cout << "size: " << queue.size() << std::endl;
}
