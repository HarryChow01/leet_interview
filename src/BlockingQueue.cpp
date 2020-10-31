//
// Created by Chow on 2019/5/29.
//

#include <iostream>
#include "BlockingQueue.h"

template<typename T>
T BlockingQueue<T>::take() {
    std::unique_lock<std::mutex> lock(mutex_);
    cvNotEmpty_.wait(lock, [this] { return !data_.empty(); });
    T front(data_.front());
    data_.pop_front();
    cvNotFull_.notify_one();
    return front;
}

template<typename T>
void BlockingQueue<T>::put(const T &item) {
    std::unique_lock<std::mutex> lock(mutex_);
    cvNotFull_.wait(lock, [this] { return data_.size() < capacity_; });
    data_.push_back(item);
    cvNotEmpty_.notify_one();
}


int main() {
    BlockingQueue<int> queue;
    queue.put(5);
    std::cout << "size: " << queue.size() << std::endl;
    int item = queue.take();
    std::cout << "item: " << item << std::endl;
    std::cout << "size: " << queue.size() << std::endl;
}
